#include "sd01.h"
#include "uart.h"
#include "delay.h"
#include "timer.h"

//PM5 <--> SD01


uint32_t time_drop = 0;//ˮ��,ʱ����,ms
uint32_t count_drop = 0;//ˮ����
const float volume_drop = 0.045;//ÿ��ˮ�����,ml
double speed_drop = 0.0;//ˮ���ٶ�,ml/min
uint8_t warn_status = 0;//�����־,1����,0����

void calculate_drop(uint32_t time);//����ʱ��������ˮ���ٶ�
void sd01_init(void)
{
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
	ROM_GPIODirModeSet(GPIO_PORTM_BASE, GPIO_INT_PIN_5, GPIO_DIR_MODE_IN);
	MAP_GPIOPadConfigSet(GPIO_PORTM_BASE, GPIO_INT_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
	MAP_GPIOIntEnable(GPIO_PORTM_BASE, GPIO_INT_PIN_5);
	MAP_IntEnable(INT_GPIOM);
}

void GPIOM_IRQHandler(void)
{
	uint32_t temp_time=0;
	unsigned long ulPinState = MAP_GPIOIntStatus(GPIO_PORTM_BASE, GPIO_INT_PIN_5);
	
	if (ulPinState & GPIO_INT_PIN_5)
	{
		MAP_GPIOIntClear(GPIO_PORTM_BASE, GPIO_INT_PIN_5);
		temp_time = timer_sd01_ms;
		
		if(temp_time > 500)
		{
			timer_sd01_ms = 0;
//			UARTprintf("SD01:%d\n",temp_time);
			calculate_drop(temp_time);
		}
	}
}

void calculate_drop(uint32_t time)
{
	static uint8_t flag=0; 
	static uint32_t time_last=0;
	double temp = 60000.0;
	if(flag == 0)
	{
		flag = 1;
		time_last = time;
	}
	else
	{
		flag = 0;
		warn_status = 0;
//		UARTprintf("SD01 cal:%d,%d\n",time,time_last);
		time += time_last;//�ۻ��ϴε�ʱ��
		if(time<50000&time>500)
		{
			temp = temp*volume_drop/time;
			speed_drop = temp;//60*1000.0*volume_drop/time;//�����ٶ�
			time_drop = time;//����ʱ����
			count_drop++;//ˮ�μ���
		}
	}
}
