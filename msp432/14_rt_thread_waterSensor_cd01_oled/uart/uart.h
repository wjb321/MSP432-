#ifndef __UART_H__
#define __UART_H__

#include "ti/devices/msp432e4/driverlib/driverlib.h"
#include "uartstdio.h"

#define USART2_MAX_SEND_LEN		512					//最大发送缓存字节数
#define USART0_MAX_SEND_LEN		512					//最大发送缓存字节数


void uart0_init(uint32_t band);
void uart2_init(uint32_t band);


void uart0_send(char data);
void uart0_send_string(char *str);
void u0_printf(char* fmt,...);


void uart2_send(char data);
void uart2_send_string(char *str);
void u2_printf(char* fmt,...);
#endif
