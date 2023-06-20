#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ti/devices/msp432e4/driverlib/driverlib.h"
#include "pinout.h"
#include "uartstdio.h"
#include "delay.h"
#include "led.h"
#include "oled.h"
#include "uart.h"
#include "key.h"
#include "timer.h"
#include "sd01.h"

char str[200];                          //字符串缓存
int main(void)
{
	delay_init();													//系统初始化
	PinoutSet(false, false);
	uart0_init(115200);										//串口0初始化
	uart2_init(115200);										//串口2初始化
	OLED_Init();		                			//初始化OLED  
  OLED_Clear();                         //OLED清屏
  OLED_ShowENCN(0, 0, "欢迎使用");      //显示欢迎界面
	
	led_init();                         	//LED初始化
	key_init();                         	//按键初始化
	timer_init();                         //定时器初始化
	sd01_init();                         	//SD01引脚初始化
	
	delay_ms(2000);												//延时2000ms
	OLED_Clear();                         //OLED清屏
	
	while(1)
	{
		LED1_TOGGLE;												//LED1闪烁,指示程序正在运行
		delay_ms(500);											//延时500ms

		OLED_printf(0, 2, "t= %5d ms", time_drop);//显示时间间隔
		OLED_printf(0, 4, "s=%6.3f ml/min", speed_drop);//显示速度
		OLED_printf(0, 6, "c = %4d", count_drop);//显示水滴计数
		u2_printf("hello this is uart2\n");//发送带警告的数据
		u0_printf("hello this is uart0\n");//发送带警告的数据
		
		if(warn_status==1)									//警告状态
		{
			LED4_ON;													//LED4点亮,表示异常
			u2_printf("t=%dms,s=%fml/min,c=%d,warning\r\n", time_drop, speed_drop, count_drop);//发送带警告的数据
		}
		else
		{
			LED4_OFF;													//LED4关闭,表示正常
			u2_printf("t=%dms,s=%fml/min,c=%d\r\n", time_drop, speed_drop, count_drop);//发送数据
		}
	}
}
