
#include <stdint.h>
#include <stdbool.h>
#include "usart.h"
#include "delay.h"
//#include <gpio.h>
#include "ti/devices/msp432e4/driverlib/driverlib.h"
#include "uartstdio.h"
#include "pinout.h"
#include "timer.h"
#include "timers_config.h"

#define LEDOnOFFOrigin  0
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
  while(1);
}
#endif

extern uint32_t g_ui32SysClock;
int main(void)
{
  g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                          SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
                                           SYSCTL_CFG_VCO_480), 120000000);
	
  PinoutSet(false, false);
  TIMER0A_config();	
	TIMER1A_config();
  ConfigureUART(115200);
  void delay_ms(uint16_t nms);
#if LEDOnOFFOrigin
  while(1)
    {

      LEDWrite(CLP_D1, 1);
      LEDWrite(CLP_D3, 1); // does not work
      SysCtlDelay(g_ui32SysClock / 10 / 3);
      LEDWrite(CLP_D1, 0);
      LEDWrite(CLP_D3, 0);// does not work
      SysCtlDelay(g_ui32SysClock / 10 / 3);
    }



//    // Enable the GPIO port that is used for the on-board LED.
//    //
//     SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
//     SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//    //
//    // Check if the peripheral access is enabled.
//    //
//    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}
//    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)){}

//

//    //
//    // Enable the GPIO pin for the LED (PN0).  Set the direction as output, and
//    // enable the GPIO pin for digital function.
//    //
//     GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, (GPIO_PIN_0 | GPIO_PIN_1));
//		 GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, (GPIO_PIN_0 | GPIO_PIN_4));
#else

  while(1)
    {
//      UARTprintf("again yest\n");
//      GPIOPinWrite(GPIO_PORTN_BASE,  GPIO_PIN_0, GPIO_PIN_0);
//      GPIOPinWrite(GPIO_PORTN_BASE,  GPIO_PIN_1, 0);
//      GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_0, 0);
//      GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_4, 0);

////      delay_ms(500);

////      GPIOPinWrite(GPIO_PORTN_BASE,  GPIO_PIN_0, 0);
////      GPIOPinWrite(GPIO_PORTN_BASE,  GPIO_PIN_1, GPIO_PIN_1);
////      GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_0, 0);
////      GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_4, 0);

//      delay_ms(500);

//      GPIOPinWrite(GPIO_PORTN_BASE,  GPIO_PIN_0, 0);
//      GPIOPinWrite(GPIO_PORTN_BASE,  GPIO_PIN_1, 0);
//      GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_0, GPIO_PIN_0);
//      GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_4, 0);

//      delay_ms(500);

//      GPIOPinWrite(GPIO_PORTN_BASE,  GPIO_PIN_0, 0);
//      GPIOPinWrite(GPIO_PORTN_BASE,  GPIO_PIN_1, 0);
//      GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_0, 0);
//      GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_4, GPIO_PIN_4);

//      delay_ms(500);

    }
#endif
}

