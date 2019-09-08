#ifndef __RELAY_H
#define	__RELAY_H

#include "stm32f4xx.h"

//���Ŷ���
/*******************************************************/
#define RELAY_IN_PIN                  GPIO_Pin_11                 
#define RELAY_IN_GPIO_PORT            GPIOH
#define RELAY_IN_GPIO_CLK             RCC_AHB1Periph_GPIOH

#define RELAY_OUT_PIN                  GPIO_Pin_10                 
#define RELAY_OUT_GPIO_PORT            GPIOH                      
#define RELAY_OUT_GPIO_CLK             RCC_AHB1Periph_GPIOH




/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)			 {p->BSRRL=i;}		//����Ϊ�ߵ�ƽ
#define digitalLo(p,i)			 {p->BSRRH=i;}		//����͵�ƽ
#define digitalToggle(p,i)	     {p->ODR ^=i;}		//�����ת״̬

/* �������IO�ĺ� */
#define RELAY_IN_TOGGLE			digitalToggle(RELAY_IN_GPIO_PORT,RELAY_IN_PIN)
#define RELAY_IN_ON				digitalHi(RELAY_IN_GPIO_PORT,RELAY_IN_PIN)
#define RELAY_IN_OFF			digitalLo(RELAY_IN_GPIO_PORT,RELAY_IN_PIN)

#define RELAY_OUT_TOGGLE		digitalToggle(RELAY_OUT_GPIO_PORT,RELAY_OUT_PIN)
#define RELAY_OUT_ON			digitalHi(RELAY_OUT_GPIO_PORT,RELAY_OUT_PIN)
#define RELAY_OUT_OFF			digitalLo(RELAY_OUT_GPIO_PORT,RELAY_OUT_PIN)


void RELAY_GPIO_Config(void);

#endif 
