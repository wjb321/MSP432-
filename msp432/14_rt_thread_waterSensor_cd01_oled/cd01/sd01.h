#ifndef __SD01_H__
#define __SD01_H__

#include "ti/devices/msp432e4/driverlib/driverlib.h"

extern uint32_t time_drop;//水滴,时间间隔,ms
extern uint32_t count_drop;//水滴数
extern double speed_drop;//水滴速度,ml/min
extern uint8_t warn_status;//警告标志,1警告,0正常

void sd01_init(void);
void calculate_drop(uint32_t time);
#endif
