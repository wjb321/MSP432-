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

//消息1 在task1 中经过邮箱的形式发送到 task2 中
static rt_thread_t led1_thread = RT_NULL;
static rt_thread_t led2_thread = RT_NULL;


static void led1_thread_entry(void* parameter); 
static void led2_thread_entry(void* parameter);

static rt_mailbox_t test_mail = RT_NULL;

char test_str1[] = "mail message 1";
char test_str2[] = "mail message 2";
int main(void)
{

  test_mail = rt_mb_create("test_mail",
                           10, 
                           RT_IPC_FLAG_FIFO);
  if (test_mail != RT_NULL) rt_kprintf("mail success \n\n");

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
    rt_uint8_t count;
    for(;;)
    {
      count++;
      if(count&1)
          {
            uwRet = rt_mb_send(test_mail,(rt_uint32_t)&test_str1);
            if (RT_EOK == uwRet)
              rt_kprintf ( "\n msg1:send success\n" );
            else
              rt_kprintf ( "msg1:send fail\n" );
          }
        else
          {
          
            uwRet = rt_mb_send(test_mail,(rt_uint32_t)&test_str2);
            if (RT_EOK == uwRet)
              rt_kprintf ("msg2:send success\n\n");
            else
              rt_kprintf ("msg2:send fail\n" );
            rt_thread_delay(1000);
          }
      }
  }

  static void led2_thread_entry(void* parameter)
  {
    rt_err_t uwRet = RT_EOK;
    char *r_str;
    for(;;)
      {
        uwRet = rt_mb_recv(test_mail, 
                           (rt_uint32_t*)&r_str, 
                           RT_WAITING_FOREVER );
        if (RT_EOK == uwRet)   
          {
            rt_kprintf ( "recv:%s\n",r_str);
          }
        else
          rt_kprintf ( "receive fail? the error code? 0x%x\n",uwRet);
        rt_thread_delay(100);
      }
  }