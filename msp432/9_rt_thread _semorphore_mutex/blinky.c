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

uint32_t getSystemClock;
uint32_t duty_cycle = 0;
uint32_t increment = 100;


static rt_thread_t led1_thread = RT_NULL;
static rt_thread_t led2_thread = RT_NULL;
static void led1_thread_entry(void* parameter); 
static void led2_thread_entry(void* parameter); 
static rt_mutex_t mutex = RT_NULL;
int a=-10,b=-10;
/**********main ??**********/
//here are some infomations:
//the time slice allocated for each thread, and the delay time
//mutex, the task 2 takes another's value and use
int main(void)
{
	
  mutex = rt_mutex_create("mutex",RT_IPC_FLAG_PRIO);
  if (mutex != RT_NULL) rt_kprintf("mutex created\n\n");
  led1_thread = 
    rt_thread_create( "led1",
                      led1_thread_entry, 
                      RT_NULL, 
                      512,
                      3, 
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
                      4, 
                      5); 
 
  if (led2_thread != RT_NULL)
    rt_thread_startup(led2_thread);
  else
    return -1;
}

static void led1_thread_entry(void* parameter)
{
  for(;;)
    {
      rt_mutex_take(mutex,
                    RT_WAITING_FOREVER);
      a+=1;
      rt_thread_delay ( 20 );
      b+=10;
      rt_mutex_release(mutex);
      rt_thread_yield();
    }
}

//mutex part take values from led1 thread
static void led2_thread_entry(void* parameter)
{
  for(;;)
    {
      rt_mutex_take(mutex, 
                    RT_WAITING_FOREVER);
      rt_kprintf ( "a=%d,b=%d\n",a,b );
      rt_mutex_release(mutex); 
      rt_thread_delay ( 10 ); 
    }
}