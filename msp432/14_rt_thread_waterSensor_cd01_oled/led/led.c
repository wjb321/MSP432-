#include "led.h"

void led_init(void)
{
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	
  MAP_GPIOPadConfigSet(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1,
                             GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
	MAP_GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4,
                             GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);
	// 配置LED GPIO为输出模式
	MAP_GPIOPinTypeGPIOOutput(LED1_GPIO_PORT, LED1_GPIO_PIN);
	MAP_GPIOPinTypeGPIOOutput(LED2_GPIO_PORT, LED2_GPIO_PIN);
	MAP_GPIOPinTypeGPIOOutput(LED3_GPIO_PORT, LED3_GPIO_PIN);
	MAP_GPIOPinTypeGPIOOutput(LED4_GPIO_PORT, LED4_GPIO_PIN);
}

void led_toggle(uint32_t ui32Port, uint8_t ui8Pins)
{
	int32_t led_status = GPIOPinRead(ui32Port, ui8Pins);
	led_status = led_status ^ ui8Pins;
	GPIOPinWrite(ui32Port, ui8Pins, led_status);
}

