/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rthw.h>
#include <rtconfig.h>
#include "uartstdio.h"
#include <ti/devices/msp432e4/driverlib/driverlib.h>
#ifndef RT_USING_FINSH
#error Please uncomment the line <#include "finsh_config.h"> in the rtconfig.h 
#endif

#ifdef RT_USING_FINSH

RT_WEAK char rt_hw_console_getchar(void)
{
    /* Note: the initial value of ch must < 0 */
    int ch = -1;

     uint32_t ui32Status;
	  
     ui32Status = MAP_UARTIntStatus(UART0_BASE, true);
	if(MAP_UARTCharsAvail(UART0_BASE))
	{
		ch = MAP_UARTCharGetNonBlocking(UART0_BASE);
		MAP_UARTIntClear(UART0_BASE, ui32Status);
	}
	   
    return ch;
}

#endif /* RT_USING_FINSH */

