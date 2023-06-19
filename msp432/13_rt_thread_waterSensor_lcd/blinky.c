#include <ti/devices/msp432e4/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "pinout.h"
#include "msp432e401y.h"
#include <rthw.h>
#include <rtthread.h>
#include "ti/devices/msp432e4/driverlib/driverlib.h"
#include "uartstdio.h"
//#include "driverlib.h"
uint32_t getSystemClock;
uint32_t duty_cycle = 0;
uint32_t increment = 100;
void PWM_configure();
static int uart_init(uint32_t sysclockVal);
void LED0_Blinky();

static rt_thread_t led1_thread = RT_NULL;
static rt_thread_t led2_thread = RT_NULL;
static void led1_thread_entry(void* parameter);
static void led2_thread_entry(void* parameter);






int main(void)
{
  getSystemClock = MAP_SysCtlClockFreqSet((SYSCTL_OSC_INT | SYSCTL_USE_OSC), 16000000);
      //getSystemClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
       //                                   SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
       //                                   120000000);


  led1_thread = rt_thread_create( "led1",
                                  led1_thread_entry,
                                  RT_NULL,
                                  512,
                                  3,
                                  20);
  if (led1_thread != RT_NULL)
    rt_thread_startup(led1_thread);
  else
    return -1;
  led2_thread = rt_thread_create( "led2",
                                  led2_thread_entry,
                                  RT_NULL,
                                  512,
                                  4,
                                  20);

  if (led2_thread != RT_NULL)
    rt_thread_startup(led2_thread);
  else
    return -1;
}

static void led1_thread_entry(void* parameter)
{  
	  uint32_t getADCValue[1];
    uint32_t systemClock;
	 uart_init(getSystemClock);
	 /* Enable the clock to GPIO Port E and wait for it to be ready */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)))
    {
    }

    /* Configure PE3 as ADC input channel */
    MAP_GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);

    /* Enable the clock to ADC-0 and wait for it to be ready */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)))
    {
    }

    /* Configure Sequencer 3 to sample a single analog channel : AIN0 with
     * sample and hold for 32 clock cycles */
    MAP_ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 |
                                 ADC_CTL_SHOLD_32 | ADC_CTL_IE | ADC_CTL_END);

    /* Enable sample sequence 3 with a processor signal trigger.  Sequence 3
     * will do a single sample when the processor sends a signal to start the
     * conversion */
    MAP_ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);

    /* Since sample sequence 3 is now configured, it must be enabled. */
    MAP_ADCSequenceEnable(ADC0_BASE, 3);

    /* Clear the interrupt status flag.  This is done to make sure the
     * interrupt flag is cleared before we sample. */
    MAP_ADCIntClear(ADC0_BASE, 3);

  for(;;)
    {
      LED0_Blinky();
      //rt_thread_delay(300); /* ?? 500 ? tick */
			        /* Trigger the ADC conversion. */
        MAP_ADCProcessorTrigger(ADC0_BASE, 3);

        /* Wait for conversion to be completed. */
        while(!MAP_ADCIntStatus(ADC0_BASE, 3, false))
        {
        }

        /* Clear the ADC interrupt flag. */
        MAP_ADCIntClear(ADC0_BASE, 3);

        /* Read ADC Value. */
        MAP_ADCSequenceDataGet(ADC0_BASE, 3, getADCValue);

        /* Display the AIN0 (PE3) digital value on the console. */
        //UARTprintf();
        rt_kprintf("AIN0 = %4d\r\n", getADCValue[0]);
        /* Delay the next sampling */
        //MAP_SysCtlDelay(getSystemClock / 30);
				rt_thread_delay(300);
    }
}


static void led2_thread_entry(void* parameter)
{
   uart_init(getSystemClock);
	 PWM_configure();
  for(;;)
    {
      //LED1_Blinky();
      duty_cycle += increment;
      if (duty_cycle >= 12000)
        {
          duty_cycle = 12000;
          increment = -2000;
        }
      else if (duty_cycle <= 0)
        {
          duty_cycle = 0;
          increment = 2000;
        }
      MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, duty_cycle);
      MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, duty_cycle);
      rt_kprintf("123\n");
      //MAP_SysCtlDelay(getSystemClock / 30);
				rt_thread_delay(100);
    }
}


void PWM_configure()
{
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
}


void PWM0_0_IRQHandler(void)
{
  uint32_t getIntStatus;
  getIntStatus = MAP_PWMGenIntStatus(PWM0_BASE, PWM_GEN_0, true);
  MAP_PWMGenIntClear(PWM0_BASE, PWM_GEN_0, getIntStatus);
}

static int uart_init(uint32_t sysclockVal)
{
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

  MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
  MAP_GPIOPinConfigure(GPIO_PA1_U0TX);

  MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
  MAP_UARTConfigSetExpClk(UART0_BASE, sysclockVal, 115200,
                          (UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |
                           UART_CONFIG_WLEN_8));
  MAP_IntEnable(INT_UART0);
  MAP_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
  //UARTStdioConfig(0, 115200, g_ui32SysClock);
  return 0;
}

void LED0_Blinky()
{
  uint32_t gpioState0;
  gpioState0 = MAP_GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_0);

  gpioState0 ^= GPIO_PIN_0;

  MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, gpioState0);

}