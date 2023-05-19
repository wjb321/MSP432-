
/* Standard Includes */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "pinout.h"
#include "msp432e401y.h"
#include <rthw.h>
#include <rtthread.h>
#include "uartstdio.h"
#include <ti/devices/msp432e4/driverlib/driverlib.h>
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



static rt_thread_t father_thread = RT_NULL;
static rt_thread_t mother_thread = RT_NULL;
static rt_thread_t son_thread = RT_NULL;
static rt_thread_t daugher_thread = RT_NULL;
/* ???? */
static void father_thread_entry(void* parameter); 
static void mother_thread_entry(void* parameter); 
static void son_thread_entry(void* parameter);
static void daugher_thread_entry(void* parameter); 
/*????*/
static short apple_cnt=0,banana_cnt=0;
static rt_sem_t plate = RT_NULL,apple = RT_NULL,banana = RT_NULL;
int main(void)
{
  /* create semaphore */
  plate = rt_sem_create("plate",
                        1,
                        RT_IPC_FLAG_FIFO);
  if (plate != RT_NULL) rt_kprintf("\n semaphore plate works \n");
  apple = rt_sem_create("apple",
                        0, 
                        RT_IPC_FLAG_FIFO);
  if (apple != RT_NULL) rt_kprintf("semaphore apple ok \n");
  banana = rt_sem_create("banana",
                         0, 
                         RT_IPC_FLAG_FIFO); 
  if (banana != RT_NULL) rt_kprintf("semaphore banana success \n\n");
  /* ???? father */
  father_thread = rt_thread_create( "father",
                                    father_thread_entry, /* entry function of thead  */
                                    RT_NULL, /* thread parameters */
                                    512, /* thread stack */
                                    3, /* priority of thread */
                                    20); /* time slice for */
  /* start semaphore */
  if (father_thread != RT_NULL)
    rt_thread_startup(father_thread);
  else
    return -1;
  /* create thread mother */
  mother_thread = rt_thread_create( "mother",
                                    mother_thread_entry, 
                                    RT_NULL, 
                                    512,
                                    5, 
                                    20); 

  if (mother_thread != RT_NULL)
    rt_thread_startup(mother_thread);
  else
    return -1;

  son_thread = rt_thread_create( "son", 
                                 son_thread_entry,
                                 RT_NULL, 
                                 512, 
                                 6, 
                                 20); 

  if (son_thread != RT_NULL)
    rt_thread_startup(son_thread);
  else
    return -1;
  /* ???? daugher */
  daugher_thread = rt_thread_create( "daugher",
                                     daugher_thread_entry,
                                     RT_NULL,
                                     512, 
                                     4, 
                                     20);
  if (daugher_thread != RT_NULL)
    rt_thread_startup(daugher_thread);
  else
    return -1;
}

static void father_thread_entry(void* parameter)
{

  for(;;)
    {
      rt_sem_take(plate, /* get the semaphore */
                  RT_WAITING_FOREVER); /* block forever */
      apple_cnt++;
      rt_sem_release(apple); //release the binary semaphore
      rt_kprintf("father thread apple_cnt=%d\n",apple_cnt);
      rt_thread_delay (1000 ); // 1000ms delay
    }
}

static void mother_thread_entry(void* parameter)
{
  for(;;)
    {
      rt_sem_take(plate,
                  RT_WAITING_FOREVER); 
      banana_cnt++;
      rt_sem_release(banana);
      rt_kprintf("mother thread banana_cnt=%d\n",banana_cnt);
      rt_thread_delay (1000 ); // 1000ms 
    }
}
/*father*/
static void son_thread_entry(void* parameter)
{
  for(;;)
    {
      rt_sem_take(banana, 
                  RT_WAITING_FOREVER); 
      banana_cnt--;
      rt_sem_release(plate);
      rt_kprintf("son thread banana_cnt=%d\n",banana_cnt);
      rt_thread_delay (1000 ); 
    }
}
/*?? father*/
static void daugher_thread_entry(void* parameter)
{
  for(;;)
    {
      rt_sem_take(apple,
                  RT_WAITING_FOREVER); 
      apple_cnt--;

      rt_sem_release(plate); 
      rt_kprintf("daugher thread apple_cnt=%d\n",apple_cnt);
      rt_thread_delay (1000); 
    }
}


//int main(void)
//{

//  getSystemClock = MAP_SysCtlClockFreqSet((SYSCTL_OSC_INT | SYSCTL_USE_OSC), 16000000);


//  led1_thread = rt_thread_create( "led1",
//                                  led1_thread_entry,
//                                  RT_NULL,
//                                  512,
//                                  3,
//                                  20);
//  if (led1_thread != RT_NULL)
//    rt_thread_startup(led1_thread);
//  else
//    return -1;
//  led2_thread = rt_thread_create( "led2",
//                                  led2_thread_entry,
//                                  RT_NULL,
//                                  512,
//                                  4,
//                                  20);

//  if (led2_thread != RT_NULL)
//    rt_thread_startup(led2_thread);
//  else
//    return -1;
//}

//static void led1_thread_entry(void* parameter)
//{
//  for(;;)
//    {
//      LED0_Blinky();
//      rt_thread_delay(300); /* ?? 500 ? tick */
//    }
//}


//static void led2_thread_entry(void* parameter)
//{
//  uart_init(getSystemClock);
//	 PWM_configure();
//  for(;;)
//    {
//      //LED1_Blinky();
//      duty_cycle += increment;
//      if (duty_cycle >= 12000)
//        {
//          duty_cycle = 12000;
//          increment = -2000;
//        }
//      else if (duty_cycle <= 0)
//        {
//          duty_cycle = 0;
//          increment = 2000;
//        }
//      MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, duty_cycle);
//      MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, duty_cycle);
//      rt_kprintf("123\n");
//      rt_thread_delay(100); /* ?? 300 ? tick */
//    }
//}


//void PWM_configure()
//{
//  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
//  while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)));

//  MAP_PWMClockSet(PWM0_BASE,PWM_SYSCLK_DIV_1);

//  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//  while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

//  MAP_GPIOPinConfigure(GPIO_PF0_M0PWM0);
//  MAP_GPIOPinConfigure(GPIO_PF1_M0PWM1);

//  MAP_GPIOPinTypePWM(GPIO_PORTF_BASE, (GPIO_PIN_0 | GPIO_PIN_1)); //make sure which pin has pwm mode
//  MAP_PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN |PWM_GEN_MODE_NO_SYNC);

//  MAP_PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, 64000); // set the upbound of the pwm value
//  MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) / 4);
//  MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) / 4);

//  MAP_IntMasterEnable();

//  MAP_PWMGenIntTrigEnable(PWM0_BASE, PWM_GEN_0, PWM_INT_CNT_ZERO | PWM_INT_CNT_LOAD |PWM_INT_CNT_AU | PWM_INT_CNT_AD);
//  MAP_IntEnable(INT_PWM0_0);

//  MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, duty_cycle);
//  MAP_PWMIntEnable(PWM0_BASE, PWM_INT_GEN_0);

//  MAP_PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT | PWM_OUT_1_BIT, true);
//  MAP_PWMGenEnable(PWM0_BASE, PWM_GEN_0);
//}


//void PWM0_0_IRQHandler(void)
//{
//  uint32_t getIntStatus;
//  getIntStatus = MAP_PWMGenIntStatus(PWM0_BASE, PWM_GEN_0, true);
//  MAP_PWMGenIntClear(PWM0_BASE, PWM_GEN_0, getIntStatus);
//}

//static int uart_init(uint32_t sysclockVal)
//{
//  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
//  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

//  MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
//  MAP_GPIOPinConfigure(GPIO_PA1_U0TX);

//  MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
//  MAP_UARTConfigSetExpClk(UART0_BASE, sysclockVal, 115200,
//                          (UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |
//                           UART_CONFIG_WLEN_8));
//  MAP_IntEnable(INT_UART0);
//  MAP_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
//  //UARTStdioConfig(0, 115200, g_ui32SysClock);
//  return 0;
//}

//void LED0_Blinky()
//{
//  uint32_t gpioState0;
//  gpioState0 = MAP_GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_0);

//  gpioState0 ^= GPIO_PIN_0;

//  MAP_GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, gpioState0);

//}