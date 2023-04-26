
#include <stdint.h>
#include <stdbool.h>
//#include <gpio.h>
#include "ti/devices/msp432e4/driverlib/driverlib.h"

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Blinky (blinky)</h1>
//!
//! A very simple example that blinks the on-board LED using direct register
//! access.
//
//*****************************************************************************

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

//*****************************************************************************
//
// Blink the on-board LED.
//
//*****************************************************************************
int
main(void)
{
    volatile uint32_t ui32Loop;
    void delay_ms(uint16_t nms);
	(void)SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                          SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                                          120000000);

    // Enable the GPIO port that is used for the on-board LED.
    //
     SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
     SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)){}

		

    //
    // Enable the GPIO pin for the LED (PN0).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
     GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, (GPIO_PIN_0 | GPIO_PIN_1));
		 GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, (GPIO_PIN_0 | GPIO_PIN_4));
    // Loop forever.

    while(1)
    {

	GPIOPinWrite(GPIO_PORTN_BASE,  GPIO_PIN_0, GPIO_PIN_0);
	GPIOPinWrite(GPIO_PORTN_BASE,  GPIO_PIN_1, 0);
	GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_0, 0);
	GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_4, 0);
			
	delay_ms(500);
			
	GPIOPinWrite(GPIO_PORTN_BASE,  GPIO_PIN_0, 0);
	GPIOPinWrite(GPIO_PORTN_BASE,  GPIO_PIN_1, GPIO_PIN_1);
	GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_0, 0);
	GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_4, 0);
			
	delay_ms(500);
			
	GPIOPinWrite(GPIO_PORTN_BASE,  GPIO_PIN_0, 0);
	GPIOPinWrite(GPIO_PORTN_BASE,  GPIO_PIN_1, 0);
	GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_0, GPIO_PIN_0);
	GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_4, 0);
			
	delay_ms(500);
			
	GPIOPinWrite(GPIO_PORTN_BASE,  GPIO_PIN_0, 0);
	GPIOPinWrite(GPIO_PORTN_BASE,  GPIO_PIN_1, 0);
	GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_0, 0);
	GPIOPinWrite(GPIO_PORTF_BASE,  GPIO_PIN_4, GPIO_PIN_4);
			
	delay_ms(500);

    }
}

void delay_us(uint16_t nus)
{
	SysCtlDelay(40* nus);//1ms
}

void delay_ms(uint16_t nms)
{
	SysCtlDelay(40000* nms);
}