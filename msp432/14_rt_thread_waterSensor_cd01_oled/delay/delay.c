#include "delay.h"


uint32_t g_ui32SysClock;// System clock rate in Hz.
uint32_t g_ui32Clk_us,g_ui32Clk_ms;//System clock rate in us & ms.

void delay_init(void)
{
	g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
				SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
				SYSCTL_CFG_VCO_480), 120000000);
	
	g_ui32Clk_us = g_ui32SysClock/3/1000/1000;
	g_ui32Clk_ms = g_ui32SysClock/3/1000;
}

//SysCtlDelay(g_ui32SysClock);//3 Sec
//SysCtlDelay(g_ui32SysClock/3);//3 Sec
void delay_us(uint32_t us)
{
	SysCtlDelay(us * g_ui32Clk_us);// Delay for a bit.
}

void delay_ms(uint32_t ms)
{
	SysCtlDelay(ms * g_ui32Clk_ms);
}
