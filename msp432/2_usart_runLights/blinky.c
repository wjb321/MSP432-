
#include <stdint.h>
#include <stdbool.h>
#include "usart.h"
#include "delay.h"
//#include <gpio.h>
#include "ti/devices/msp432e4/driverlib/driverlib.h"
#include <ti/devices/msp432e4/inc/msp.h>
#include "uartstdio.h"
#include "pinout.h"

#define LEDOnOFFOrigin  0
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
  while(1);
}
#endif

extern uint32_t g_ui32SysClock;
#include <ti/devices/msp432e4/inc/msp.h>

void configure_GPIOE4_input(void)
{
    // 设置引脚方向为输入模式
    GPIOE->DIR &= ~GPIO_PIN_4;

    // 禁用引脚上的上拉和下拉电阻
    GPIOE->PUR &= ~GPIO_PIN_4;
    GPIOE->PDR &= ~GPIO_PIN_4;

    // 配置引脚的输入输出类型为 GPIO
    GPIOE->ODR &= ~GPIO_PIN_4;

    // 选择引脚的功能为普通 GPIO
    GPIOE->AFSEL &= ~GPIO_PIN_4;
}



bool read_GPIOE4(void)
{
    // 读取 GPIOE4 引脚状态
    uint32_t pinState = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_4);

    // 检查引脚状态是否为高电平
    if (pinState & GPIO_PIN_4)
    {
        return true; // 高电平
    }
    else
    {
        return false; // 低电平
    }
}


int main(void)
{
  g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                          SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
                                           SYSCTL_CFG_VCO_480), 120000000);
	
	//read_GPIOE4();
	//ROM_GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_4);
// pinoutset()contains all the configuration of MAP_GPIOPinTypeGPIOOutput() for N and F pins.
// need more time for the configurations
		//	ROM_GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_4);
    //ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0);
  PinoutSet(false, false);
	configure_GPIOE4_input();
//  MAP_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
//  MAP_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
  ConfigureUART();
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
      UARTprintf("again yest\n");
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
//	    if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_4)== 1)
//			{
//				UARTprintf( "there is no water\n");
//			}
//			else
//			{
//				UARTprintf( "there is water\n");
//			}

    UARTprintf("state is %d",read_GPIOE4());

    }
#endif
}

