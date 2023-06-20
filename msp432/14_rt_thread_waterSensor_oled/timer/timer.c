#include "timer.h"
#include "uart.h"
#include "sd01.h"

extern uint32_t g_ui32SysClock;// System clock rate in Hz.

uint32_t timer_sd01_ms = 0;
void timer_init(void)
{
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);// Enable the peripherals used by this example.
	
	MAP_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);// Configure the two 32-bit periodic timers.
	MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, g_ui32SysClock/1000);
	
	MAP_IntEnable(INT_TIMER0A);// Setup the interrupts for the timer timeouts.
	MAP_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	
	MAP_TimerEnable(TIMER0_BASE, TIMER_A);// Enable the timers.
}

void TIMER0A_IRQHandler(void)
{
	MAP_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);// Clear the timer interrupt.
	timer_sd01_ms++;
	if(timer_sd01_ms > 20000)
	{
		timer_sd01_ms = 0;
		time_drop = 0;
		speed_drop = 0.0;
		warn_status = 1;
		UARTprintf("timer0\n");
	}
}

