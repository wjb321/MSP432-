#include "uart.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>	

__align(8) char USART2_TX_BUF[USART2_MAX_SEND_LEN]; 	//发送缓冲,最大USART2_MAX_SEND_LEN字节
__align(8) char USART0_TX_BUF[USART0_MAX_SEND_LEN]; 	//发送缓冲,最大USART2_MAX_SEND_LEN字节

extern uint32_t g_ui32SysClock;// System clock rate in Hz.
void uart0_init(uint32_t band)// Configure the UART and its pins.  This must be called before UARTprintf().
{
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);// Enable the GPIO Peripheral used by the UART.
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);// Enable UART0
	
	MAP_GPIOPinConfigure(GPIO_PA0_U0RX);// Configure GPIO Pins for UART mode.
	MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
	MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	UARTStdioConfig(0, band, g_ui32SysClock);// Initialize the UART for console I/O.
}

void uart2_init(uint32_t band)
{
	// 配置GPIO
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
	
	MAP_GPIOPinConfigure(GPIO_PD4_U2RX);
	MAP_GPIOPinConfigure(GPIO_PD5_U2TX);
	MAP_GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_4 | GPIO_PIN_5);

	// 配置UART
	
	while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_UART2));
	MAP_UARTConfigSetExpClk(UART2_BASE, g_ui32SysClock, band,
													UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
													UART_CONFIG_PAR_NONE);
	MAP_UARTFIFOEnable(UART2_BASE);
	MAP_UARTEnable(UART2_BASE);
	UARTStdioConfig(2, band, g_ui32SysClock);
}

void uart2_send(char data)
{
	while(!MAP_UARTSpaceAvail(UART2_BASE));
	MAP_UARTCharPutNonBlocking(UART2_BASE, data);
}

void uart0_send(char data)
{
	while(!MAP_UARTSpaceAvail(UART0_BASE));
	MAP_UARTCharPutNonBlocking(UART0_BASE, data);
}

void uart0_send_string(char *str)
{
	while(*str != '\0')
		uart0_send(*str++);
}
void uart2_send_string(char *str)
{
	while(*str != '\0')
		uart2_send(*str++);
}


//串口2,printf 函数
//确保一次发送数据不超过USART2_MAX_SEND_LEN字节
void u0_printf(char* fmt,...)  
{  
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART0_TX_BUF,fmt,ap);
	va_end(ap);
	uart2_send_string(USART0_TX_BUF);
}



//串口2,printf 函数
//确保一次发送数据不超过USART2_MAX_SEND_LEN字节
void u2_printf(char* fmt,...)  
{  
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART2_TX_BUF,fmt,ap);
	va_end(ap);
	uart2_send_string(USART2_TX_BUF);
}

