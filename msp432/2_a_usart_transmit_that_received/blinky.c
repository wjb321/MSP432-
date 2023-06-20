
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

void ESP8266_Init()
{
  UARTprintf("AT+RST\r\n");		//��һ��		��λ		ֻ��һ��
	delay_ms(2000);					//�ӳ�			
	UARTprintf("AT+CWMODE=1\r\n");		//�ڶ���		ģʽ  ֻ��һ��
	delay_ms(2000);					//�ӳ�
  UARTprintf("AT+CIPSNTPCFG=1,8,\"ntp1.aliyun.com\"\r\n");		//������
	delay_ms(3000);					//�ӳ�

	UARTprintf("AT+CWJAP=\"whatever\",\"youlike!!\"\r\n");		//���Ĳ� wifi�ȵ�
	delay_ms(5000);					//�ӳ�
	delay_ms(5000);					//�ӳ�
	delay_ms(5000);					//�ӳ�	
	delay_ms(5000);					//�ӳ�
	UARTprintf("AT+MQTTUSERCFG=0,1,\"NULL\",\"ttcan&a5ZLiiHWg1j\",\"0ff52717e4fe45d92a9c6f11234d1d123a574e50f9b2e84642c1a0e7d415522b\",0,0,\"\"\r\n");		//���岽
	delay_ms(3000);					//�ӳ�			

	UARTprintf("AT+MQTTCLIENTID=0,\"a5ZLiiHWg1j.ttcan|securemode=2\\,signmethod=hmacsha256\\,timestamp=1676687037657|\"\r\n");		//������ \\timestamp=1676687037657|
	delay_ms(3000);					//�ӳ�	
	 delay_ms(3000);			   
	UARTprintf("AT+MQTTCONN=0,\"a5ZLiiHWg1j.iot-as-mqtt.eu-central-1.aliyuncs.com\",1883,1\r\n");		//���߲�
	delay_ms(3000);					//�ӳ�
}

void UART0_IRQHandler(void)
{
    uint32_t getIntStatus;

    /* Read the interrupt status from the UART */
    getIntStatus = MAP_UARTIntStatus(UART0_BASE, true);
    
    /* If the UARTRX DMA Done interrupt is asserted then re-enable the DMA
     * control structure and clear the interrupt condition */
    if((getIntStatus & UART_INT_DMARX) == UART_INT_DMARX)
    {
        MAP_UARTIntClear(UART0_BASE, getIntStatus);

        MAP_uDMAChannelTransferSet(UDMA_CH8_UART0RX | UDMA_PRI_SELECT,
                                   UDMA_MODE_BASIC,
                                   (void *)&UART0->DR, (void *)&UART0->DR,
                                   100);
        MAP_uDMAChannelEnable(UDMA_CH8_UART0RX);
    }
		
		while(MAP_UARTCharsAvail(UART0_BASE))
		{
			MAP_UARTCharPutNonBlocking(UART0_BASE, MAP_UARTCharGetNonBlocking(UART0_BASE));
		}
}


void configure_GPIOE4_input(void)
{
    // �������ŷ���Ϊ����ģʽ
    GPIOE->DIR &= ~GPIO_PIN_4;

    // ���������ϵ���������������
    GPIOE->PUR &= ~GPIO_PIN_4;
    GPIOE->PDR &= ~GPIO_PIN_4;

    // �������ŵ������������Ϊ GPIO
    GPIOE->ODR &= ~GPIO_PIN_4;

    // ѡ�����ŵĹ���Ϊ��ͨ GPIO
    GPIOE->AFSEL &= ~GPIO_PIN_4;
}



bool read_GPIOE4(void)
{
    // ��ȡ GPIOE4 ����״̬
    uint32_t pinState = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_4);

    // �������״̬�Ƿ�Ϊ�ߵ�ƽ
    if (pinState & GPIO_PIN_4)
    {
        return true; // �ߵ�ƽ
    }
    else
    {
        return false; // �͵�ƽ
    }
}

//interrupt for uart

int main(void)
{
  g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                          SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
                                           SYSCTL_CFG_VCO_480), 120000000);
  PinoutSet(false, false);
	//ESP8266_Init();
	configure_GPIOE4_input();
  ConfigureUART();
	MAP_IntMasterEnable();
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

