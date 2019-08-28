#ifndef __TIM_H
#define	__TIM_H

#include "stm32f4xx.h"

#define GENERAL_TIM           		TIM3
#define GENERAL_TIM_CLK       		RCC_APB1Periph_TIM3

#define GENERAL_TIM_IRQn			TIM3_IRQn
#define GENERAL_TIM_IRQHandler      TIM3_IRQHandler

#define FIRE_TIM           		TIM4
#define FIRE_TIM_CLK       		RCC_APB1Periph_TIM4

#define FIRE_TIM_IRQn			TIM4_IRQn
#define FIRE_TIM_IRQHandler      TIM4_IRQHandler
void TIMx_Configuration(void);

#endif 

