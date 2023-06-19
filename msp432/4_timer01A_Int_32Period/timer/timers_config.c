#include "timers_config.h"
#include <driverlib.h>
extern uint32_t g_ui32SysClock;
void TIMER0A_config()
{
   MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
   while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)));
   //MAP_TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC); //for 16bit configuration
	 MAP_TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC);
   MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, g_ui32SysClock);
	 MAP_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	 MAP_IntEnable(INT_TIMER0A);  /* Enable Timer Interrupt */
   MAP_TimerEnable(TIMER0_BASE, TIMER_A); /* Enable the timer count */
}



void TIMER1A_config()
{
   MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
   while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1)));
   //MAP_TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC); //for 16bit configuration
	 MAP_TimerConfigure(TIMER1_BASE, TIMER_CFG_A_PERIODIC);
   MAP_TimerLoadSet(TIMER1_BASE, TIMER_A, g_ui32SysClock);
	 MAP_TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
	 MAP_IntEnable(INT_TIMER1A);  /* Enable Timer Interrupt */
   MAP_TimerEnable(TIMER1_BASE, TIMER_A); /* Enable the timer count */
}


void TIMER0A_IRQHandler(void)
{
   uint32_t getTimerInterrupt;

    /* Get timer interrupt status  and clear the same */
   getTimerInterrupt = MAP_TimerIntStatus(TIMER0_BASE, true);
    MAP_TimerIntClear(TIMER0_BASE, getTimerInterrupt);

    /* Toggle the LED */
	MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1,~(MAP_GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_1)));

}


void TIMER1A_IRQHandler(void)
{
   uint32_t getTimerInterrupt;

    /* Get timer interrupt status  and clear the same */
   getTimerInterrupt = MAP_TimerIntStatus(TIMER1_BASE, true);
    MAP_TimerIntClear(TIMER1_BASE, getTimerInterrupt);

    /* Toggle the LED */
	MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0,~(MAP_GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_0)));

}