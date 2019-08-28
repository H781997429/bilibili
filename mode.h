#ifndef __MODE_H_
#define __MODE_H_

#include "stm32f4xx.h"
#include "pwmout.h"
#include "delay.h"
#include "mode.h"
#include "lcd_driver.h"
#include "lcd_display.h"
#define fire_delay  20

void mode1(void);
void mode2(void);
void mode3(void);
void mode4(void);
void mode_value(void);
void fire_mode(void);
#endif

