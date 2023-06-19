#include <ti/devices/msp432e4/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "pinout.h"
#include "msp432e401y.h"
#include <rthw.h>
#include <rtthread.h>
//#include <board.h>
#include "uartstdio.h"
//#include "driverlib.h"

//两个事件都完成后，第三个事件才可以发生，换言之就是
//事件组的概念
static rt_thread_t led1_thread = RT_NULL;
static rt_thread_t led2_thread = RT_NULL;
static rt_thread_t led3_thread = RT_NULL;
/* ???? */
static void led1_thread_entry(void* parameter); 
static void led2_thread_entry(void* parameter); 
static void led3_thread_entry(void* parameter); 

static rt_event_t test_event = RT_NULL;

uint8_t ucValue [ 2 ] = { 0x00, 0x00 };
int main(void)
{

  test_event = rt_event_create("test_event",
                               RT_IPC_FLAG_PRIO);
  if (test_event != RT_NULL)
    rt_kprintf("event created success\n\n");

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

  led3_thread =
    rt_thread_create( "led3", 
                      led3_thread_entry,
                      RT_NULL, 
                      512, 
                      3, 
                      20); 

  if (led3_thread != RT_NULL)
    rt_thread_startup(led3_thread);
  else
    return -1;
}
  /*********?? 1**********/
  static void led1_thread_entry(void* parameter)
  {
    for(;;)
      {
        rt_event_send(test_event, (1 << 3));
        rt_kprintf("send event 3\n");
        rt_thread_delay(1000);
      }
  }

  static void led2_thread_entry(void* parameter)
  {
    for(;;)
      {
        rt_event_send(test_event, (1 << 5));
        rt_kprintf("send event 5\n");
        rt_thread_delay(1000);
      }
  }

  static void led3_thread_entry(void* parameter)
  {
    rt_uint32_t e;
    for(;;)
      {
        /* receive event with logic and*/
        if ( rt_event_recv(test_event, ((1 << 6) | (1 << 5)), //选择与，那这时候，必须两件事都发生才可以进行，但是前面的部分不能发生，所以这个事件不能进行
                           RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,
                           RT_WAITING_FOREVER, &e) == RT_EOK)
          {
            rt_kprintf("thread1: AND recv event 0x%x\n", e);
          }
        rt_thread_delay(100);
      }
  }