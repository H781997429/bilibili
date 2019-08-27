#ifndef __BSP_KEY_H_
#define __BSP_KEY_H_


#include <stm32f4xx.h>
#include <tim.h>
#include <bsp_usart.h>


// ÁÐColumn1, Column2, Column3, Column4
#define C1_PIN             GPIO_Pin_2
#define C1_GPIO_PORT       GPIOE
#define C1_GPIO_CLK        RCC_AHB1Periph_GPIOE

#define C2_PIN             GPIO_Pin_3
#define C2_GPIO_PORT       GPIOE
#define C2_GPIO_CLK        RCC_AHB1Periph_GPIOE

#define C3_PIN             GPIO_Pin_4
#define C3_GPIO_PORT       GPIOE
#define C3_GPIO_CLK        RCC_AHB1Periph_GPIOE

#define C4_PIN             GPIO_Pin_5
#define C4_GPIO_PORT       GPIOE
#define C4_GPIO_CLK        RCC_AHB1Periph_GPIOE


// Row1, Row2, Row3, Row4
#define R1_PIN             GPIO_Pin_12
#define R1_GPIO_PORT       GPIOB
#define R1_GPIO_CLK        RCC_AHB1Periph_GPIOB

#define R2_PIN             GPIO_Pin_13
#define R2_GPIO_PORT       GPIOB
#define R2_GPIO_CLK        RCC_AHB1Periph_GPIOB

#define R3_PIN             GPIO_Pin_14
#define R3_GPIO_PORT       GPIOB
#define R3_GPIO_CLK        RCC_AHB1Periph_GPIOB

#define R4_PIN             GPIO_Pin_15
#define R4_GPIO_PORT       GPIOB
#define R4_GPIO_CLK        RCC_AHB1Periph_GPIOB


// detect and output
#define DETECT_C1          GPIO_ReadInputDataBit(C1_GPIO_PORT, C1_PIN)
#define DETECT_C2          GPIO_ReadInputDataBit(C2_GPIO_PORT, C2_PIN)
#define DETECT_C3          GPIO_ReadInputDataBit(C3_GPIO_PORT, C3_PIN)
#define DETECT_C4          GPIO_ReadInputDataBit(C4_GPIO_PORT, C4_PIN)

#define DETECT_R1          GPIO_ReadInputDataBit(R1_GPIO_PORT, R1_PIN)
#define DETECT_R2          GPIO_ReadInputDataBit(R2_GPIO_PORT, R2_PIN)
#define DETECT_R3          GPIO_ReadInputDataBit(R3_GPIO_PORT, R3_PIN)
#define DETECT_R4          GPIO_ReadInputDataBit(R4_GPIO_PORT, R4_PIN)

// Keys
#define S1                 0x77
#define S2                 0x7B
#define S3                 0x7D
#define S4                 0x7E
#define S5                 0xB7
#define S6                 0xBB
#define S7                 0xBD
#define S8                 0xBE
#define S9                 0xD7
#define S10                0xDB
#define S11                0xDD
#define S12                0xDE
#define S13                0xE7
#define S14                0xEB
#define S15                0xED
#define S16                0xEE


void GPIO_RCC_Config(void);
void ROCI_GPIO_Config(void);
void RICO_GPIO_Config(void);
void KEY_GPIO_ConfigAndDetect(void);
void scan_key(void);

#endif

