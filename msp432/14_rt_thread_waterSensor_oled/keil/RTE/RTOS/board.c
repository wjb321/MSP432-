/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-24                  the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <ti/devices/msp432e4/driverlib/driverlib.h>
#include "uartstdio.h"
#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
/*
 * Please modify RT_HEAP_SIZE if you enable RT_USING_HEAP
 * the RT_HEAP_SIZE max value = (sram size - ZI size), 1024 means 1024 bytes
 */
#define RT_HEAP_SIZE (15*1024)
static rt_uint8_t rt_heap[RT_HEAP_SIZE];

RT_WEAK void *rt_heap_begin_get(void)
{
  return rt_heap;
}





RT_WEAK void *rt_heap_end_get(void)
{
  return rt_heap + RT_HEAP_SIZE;
}
#endif


uint32_t systemClock;
void SystemClock_Config(void)
{

  systemClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                        SYSCTL_USE_PLL|SYSCTL_CFG_VCO_480),
                                       25000000);
  MAP_SysTickPeriodSet(systemClock/RT_TICK_PER_SECOND);
  MAP_SysTickIntEnable();
  MAP_SysTickEnable();
}

void rt_os_tick_callback(void)
{
  rt_interrupt_enter();

  rt_tick_increase();

  rt_interrupt_leave();
}

//add the systick call 
void SysTick_Handler(void)
{
	rt_os_tick_callback();
}

void LED_GPIO_Config()
{
	  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
  while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));
	MAP_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0|GPIO_PIN_1);
	MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0|GPIO_PIN_1,0);
}
/**
 * This function will initial your board.
 */
void rt_hw_board_init(void)
{
  SystemClock_Config();
	LED_GPIO_Config();

  /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
  rt_components_board_init();
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
  rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
}

#ifdef RT_USING_CONSOLE
extern uint32_t g_ui32SysClock;
static int uart_init(void)
{
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	
	MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
  MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
	
	MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	MAP_UARTConfigSetExpClk(UART0_BASE, systemClock, 115200,
                            (UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_WLEN_8));
	
	
  MAP_IntEnable(INT_UART0);
	MAP_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
	//UARTStdioConfig(0, 115200, g_ui32SysClock);
  return 0;
}
INIT_BOARD_EXPORT(uart_init);

void rt_hw_console_output(const char *str)
{
  rt_enter_critical();
	while(*str !='\0' )
	{
		if(*str =='\n' )
		{
			MAP_UARTCharPut(UART0_BASE, '\r');
		}
		MAP_UARTCharPut(UART0_BASE, *str++);
	}
	
	rt_exit_critical();
}

#endif

