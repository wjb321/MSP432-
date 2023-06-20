#include "key.h"
#include "uart.h"


void key_init(void)
{
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
	ROM_GPIODirModeSet(GPIO_PORTJ_BASE, GPIO_PIN_0|GPIO_PIN_1, GPIO_DIR_MODE_IN);
	MAP_GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0|GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	MAP_GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_INT_PIN_0|GPIO_INT_PIN_1);
	MAP_IntEnable(INT_GPIOJ);
}

void GPIOJ_IRQHandler(void)
{
	unsigned long ulPinState = MAP_GPIOIntStatus(GPIO_PORTJ_BASE, 1);
	if (ulPinState & GPIO_INT_PIN_0)
	{
		UARTprintf("KEY0\n");
		MAP_GPIOIntClear(GPIO_PORTJ_BASE, GPIO_INT_PIN_0);
	}
	else if(ulPinState & GPIO_INT_PIN_1)
	{
		UARTprintf("KEY1\n");
		MAP_GPIOIntClear(GPIO_PORTJ_BASE, GPIO_INT_PIN_1);
	}
}
