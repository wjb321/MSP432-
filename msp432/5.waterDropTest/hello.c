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

char str[200];                          //�ַ�������
int main(void)
{
	delay_init();													//ϵͳ��ʼ��
	PinoutSet(false, false);
	uart0_init(115200);										//����0��ʼ��
	uart2_init(115200);										//����2��ʼ��
	OLED_Init();		                			//��ʼ��OLED  
  OLED_Clear();                         //OLED����
  OLED_ShowENCN(0, 0, "��ӭʹ��");      //��ʾ��ӭ����
	
	led_init();                         	//LED��ʼ��
	key_init();                         	//������ʼ��
	timer_init();                         //��ʱ����ʼ��
	sd01_init();                         	//SD01���ų�ʼ��
	
	delay_ms(2000);												//��ʱ2000ms
	OLED_Clear();                         //OLED����
	
	while(1)
	{
		LED1_TOGGLE;												//LED1��˸,ָʾ������������
		delay_ms(500);											//��ʱ500ms

		OLED_printf(0, 2, "t= %5d ms", time_drop);//��ʾʱ����
		OLED_printf(0, 4, "s=%6.3f ml/min", speed_drop);//��ʾ�ٶ�
		OLED_printf(0, 6, "c = %4d", count_drop);//��ʾˮ�μ���
		u2_printf("hello this is uart2\n");//���ʹ����������
		u0_printf("hello this is uart0\n");//���ʹ����������
		
		if(warn_status==1)									//����״̬
		{
			LED4_ON;													//LED4����,��ʾ�쳣
			u2_printf("t=%dms,s=%fml/min,c=%d,warning\r\n", time_drop, speed_drop, count_drop);//���ʹ����������
		}
		else
		{
			LED4_OFF;													//LED4�ر�,��ʾ����
			u2_printf("t=%dms,s=%fml/min,c=%d\r\n", time_drop, speed_drop, count_drop);//��������
		}
	}
}
