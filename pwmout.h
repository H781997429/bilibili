#ifndef __PWMOUT_H_
#define __PWMOUT_H_

#include "stm32f4xx.h"

/**********************X×ø±ê********************/
#define OCPWMX_PIN             GPIO_Pin_1       //ch2       
#define OCPWMX_GPIO_PORT       GPIOA                      
#define OCPWMX_GPIO_CLK        RCC_AHB1Periph_GPIOA
#define OCPWMX_PINSOURCE	   GPIO_PinSource1
#define OCPWMX_AF			   GPIO_AF_TIM5

#define TIMX           		   TIM5
#define TIMX_CLK       		   RCC_APB1Periph_TIM5

#define TIMX_IRQn			   TIM5_IRQn
#define TIMX_IRQHandler        TIM5_IRQHandler

/********************y×ø±ê*********************/
#define OCPWMY_PIN             GPIO_Pin_2         //ch3     
#define OCPWMY_GPIO_PORT       GPIOA                      
#define OCPWMY_GPIO_CLK        RCC_AHB1Periph_GPIOA
#define OCPWMY_PINSOURCE	   GPIO_PinSource2
#define OCPWMY_AF			   GPIO_AF_TIM2

#define TIMY           		   TIM2
#define TIMY_CLK       		   RCC_APB1Periph_TIM2

#define TIMY_IRQn			   TIM2_IRQn
#define TIMY_IRQHandler        TIM2_IRQHandler

#define Init_angle             50

/*****************************************************/
void PWM_Configuration(void);
void Xout(float angle);
void Yout(float angle);
#endif /*__PWMOUT_H_*/
