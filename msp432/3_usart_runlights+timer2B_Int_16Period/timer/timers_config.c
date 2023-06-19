#include "timers_config.h"
#include <driverlib.h>
extern uint32_t g_ui32SysClock;
void timer2B_config()
{
   MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
   while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER2)));
   MAP_TimerConfigure(TIMER2_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC);
   MAP_TimerIntEnable(TIMER2_BASE, TIMER_TIMB_TIMEOUT);

	
	
    /* Since the 16-bit timer can count only 65536 value, we use the pre
     * scaler of 256 to divide down the count rate by 256. Thus the actual
     * count load is 120e6/256 = 468750. Now when to count at 0.1 sec the
     * load value in the timer would be 468750 * 0.1 = 46875 = 0xB71B. */
    MAP_TimerPrescaleSet(TIMER2_BASE, TIMER_B, 255);
    MAP_TimerLoadSet(TIMER2_BASE, TIMER_B, (g_ui32SysClock/(2)));
	
	  MAP_IntEnable(INT_TIMER2B);  /* Enable Timer Interrupt */
   MAP_TimerEnable(TIMER2_BASE, TIMER_B); /* Enable the timer count */
}


void TIMER2B_IRQHandler(void)
{
    uint32_t getTimerInterrupt;

    /* Get timer interrupt status  and clear the same */
    getTimerInterrupt = MAP_TimerIntStatus(TIMER2_BASE, true);
    MAP_TimerIntClear(TIMER2_BASE, getTimerInterrupt);

    /* Toggle the LED */
	MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1,~(MAP_GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_1)));

}
