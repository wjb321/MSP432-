#ifndef __DELAY_H
#define __DELAY_H
#include <stdint.h>
#include <stdbool.h>
#include "ti/devices/msp432e4/driverlib/driverlib.h"

void delay_us(uint16_t nus);
void delay_ms(uint16_t nms);

#endif
