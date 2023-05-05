#include <ti/devices/msp432e4/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include "pinout.h"
#include "msp432e401y.h"
//#include "driverlib.h"
#include <ti/devices/msp432e4/driverlib/driverlib.h>
uint32_t getSystemClock;
void PWM0_0_IRQHandler(void)
{
  uint32_t getIntStatus;
  getIntStatus = MAP_PWMGenIntStatus(PWM0_BASE, PWM_GEN_0, true);
  MAP_PWMGenIntClear(PWM0_BASE, PWM_GEN_0, getIntStatus);
}
int main(void)
{
  uint32_t duty_cycle = 0;
  uint32_t increment = 100;
  getSystemClock = MAP_SysCtlClockFreqSet((SYSCTL_OSC_INT | SYSCTL_USE_OSC), 16000000);
	
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
  while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)));
	
  MAP_PWMClockSet(PWM0_BASE,PWM_SYSCLK_DIV_1);
	
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
	
  MAP_GPIOPinConfigure(GPIO_PF0_M0PWM0);
  MAP_GPIOPinConfigure(GPIO_PF1_M0PWM1);
	
  MAP_GPIOPinTypePWM(GPIO_PORTF_BASE, (GPIO_PIN_0 | GPIO_PIN_1)); //make sure which pin has pwm mode
  MAP_PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN |PWM_GEN_MODE_NO_SYNC);
	
  MAP_PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, 64000); // set the upbound of the pwm value
  MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) / 4);
  MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) / 4);
	
  MAP_IntMasterEnable();
	
  MAP_PWMGenIntTrigEnable(PWM0_BASE, PWM_GEN_0, PWM_INT_CNT_ZERO | PWM_INT_CNT_LOAD |PWM_INT_CNT_AU | PWM_INT_CNT_AD);
  MAP_IntEnable(INT_PWM0_0);
	
  MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, duty_cycle);
  MAP_PWMIntEnable(PWM0_BASE, PWM_INT_GEN_0);
	
  MAP_PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT | PWM_OUT_1_BIT, true);
  MAP_PWMGenEnable(PWM0_BASE, PWM_GEN_0);
  while(1)
    {
      //        /* ÐÞ¸ÄÕ¼¿Õ±È */
      duty_cycle += increment;
      if (duty_cycle >= 52000)
        {
          duty_cycle = 12000;
          increment = -100;
        }
      else if (duty_cycle <= 0)
        {
          duty_cycle = 0;
          increment = 100;
        }
      MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, duty_cycle);
      MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, duty_cycle);
      MAP_SysCtlDelay(10000);
    }
}
