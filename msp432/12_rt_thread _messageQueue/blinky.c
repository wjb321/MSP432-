

/* Standard Includes */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "pinout.h"
#include "msp432e401y.h"
#include <rthw.h>
#include <rtthread.h>
#include <ti/devices/msp432e4/driverlib/driverlib.h>
//#include <board.h>
#include "uartstdio.h"
//#include "driverlib.h"


static rt_thread_t led1_thread = RT_NULL;
static rt_thread_t led2_thread = RT_NULL;
static void led1_thread_entry(void* parameter); 
static void led2_thread_entry(void* parameter);
static rt_mq_t test_mq = RT_NULL;

int main(void)
{
  test_mq = rt_mq_create("test_mq",
                         40, 
                         20, 
                         RT_IPC_FLAG_FIFO);

  if (test_mq != RT_NULL)
    rt_kprintf("message queue creates successfuly \n\n");
  led1_thread = 
    rt_thread_create( "led1", 
                      led1_thread_entry, 
                      RT_NULL,
                      512, 
                      4, 
                      20);

  if (led1_thread != RT_NULL)
    rt_thread_startup(led1_thread);
  else
    return -1;

  led2_thread = 
    rt_thread_create( "led2",
                      led2_thread_entry, 
                      RT_NULL, 
                      512, 
                      5, 
                      20);

  if (led2_thread != RT_NULL)
    rt_thread_startup(led2_thread);
  else
    return -1;
}

static void led1_thread_entry(void* parameter)
{
  rt_err_t uwRet = RT_EOK;
  uint32_t msg1 = 0x1234;
  uint32_t msg2 = 0x5678;
  rt_uint8_t count;
  for(;;)
    {
      count++;
      if(count&1)
        {

          uwRet = rt_mq_send(test_mq,
                             &msg1,
                             sizeof(msg1)); 
          if (RT_EOK != uwRet)
            {
              rt_kprintf("msg1 send fail,the error code: %lx\n",uwRet);
            }
        }
      else
        {
          uwRet = rt_mq_send(test_mq,
                             &msg2,
                             sizeof(msg2));
          if (RT_EOK != uwRet)
            {
              rt_kprintf("msg2 send fail,the error code: %lx\n",uwRet);
            }
        }
      rt_thread_delay(1000);
    }
}

static void led2_thread_entry(void* parameter)
{
  rt_err_t uwRet = RT_EOK;
  uint32_t r_queue;
  for(;;)
    {
     
      uwRet = rt_mq_recv(test_mq, 
                         &r_queue, 
                         sizeof(r_queue),
                         RT_WAITING_FOREVER); 
												 
      if (RT_EOK == uwRet)
        {
          rt_kprintf("the recv success? 0x%x\n\n",r_queue);
        }
      else
        {
          rt_kprintf("the recv fail,teh error code? 0x%lx\n",uwRet);
        }
      rt_thread_delay(100);
    }
}