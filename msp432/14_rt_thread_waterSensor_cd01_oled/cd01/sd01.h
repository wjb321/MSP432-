#ifndef __SD01_H__
#define __SD01_H__

#include "ti/devices/msp432e4/driverlib/driverlib.h"

extern uint32_t time_drop;//ˮ��,ʱ����,ms
extern uint32_t count_drop;//ˮ����
extern double speed_drop;//ˮ���ٶ�,ml/min
extern uint8_t warn_status;//�����־,1����,0����

void sd01_init(void);
void calculate_drop(uint32_t time);
#endif
