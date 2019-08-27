/******************************************************************************
//              GND   ��Դ��
//              VCC   ��5V��3.3v��Դ
//              SCL   ��PA5��SCL��
//              SDA   ��PA7��SDA��
//              RES   ��PB11
//              DC    ��PB5
//              CS    ��PA4 
//				BL	  ��PB10
*******************************************************************************/
#ifndef __LCD_DRIVER_H
#define __LCD_DRIVER_H

#include "stm32f4xx.h"
#include "delay.h"
//����ֱ���
#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        160

//������ɫ
#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//��ɫ0 3165 00110 001011 00101
#define GRAY1   0x8410      	//��ɫ1      00000 000000 00000
#define GRAY2   0x4208      	//��ɫ2  1111111111011111

#define LCD_SCL        	GPIO_Pin_5	//PA5--->>TFT --SCL/SCK
#define LCD_SDA        	GPIO_Pin_7	//PA7 MOSI--->>TFT --SDA/DIN
#define LCD_CS        	GPIO_Pin_4  //MCU_PA4--->>TFT --CS/CE

#define LCD_LED        	GPIO_Pin_10  //MCU_PB10--->>TFT --BL
#define LCD_RS         	GPIO_Pin_5	//PB5--->>TFT --RS/DC
#define LCD_RST     	GPIO_Pin_11	//PB11--->>TFT --RST

//#define LCD_CS_SET(x) LCD_CTRL->ODR=(LCD_CTRL->ODR&~LCD_CS)|(x ? LCD_CS:0)

//Һ�����ƿ���1�������궨��
#define	LCD_SCL_SET  	GPIO_SetBits(GPIOA,LCD_SCL)  
#define	LCD_SDA_SET  	GPIO_SetBits(GPIOA,LCD_SDA)  
#define	LCD_CS_SET  	GPIO_SetBits(GPIOA,LCD_CS)  

#define	LCD_LED_SET  	GPIO_SetBits(GPIOB,LCD_LED)  
#define	LCD_RS_SET  	GPIO_SetBits(GPIOB,LCD_RS)  
#define	LCD_RST_SET  	GPIO_SetBits(GPIOB,LCD_RST)  

//Һ�����ƿ���0�������궨��
#define	LCD_SCL_CLR  	GPIO_ResetBits(GPIOA,LCD_SCL)  
#define	LCD_SDA_CLR  	GPIO_ResetBits(GPIOA,LCD_SDA)  
#define	LCD_CS_CLR 	    GPIO_ResetBits(GPIOA,LCD_CS)  

#define	LCD_LED_CLR  	GPIO_ResetBits(GPIOB,LCD_LED)  
#define	LCD_RS_CLR  	GPIO_ResetBits(GPIOB,LCD_RS)  
#define	LCD_RST_CLR  	GPIO_ResetBits(GPIOB,LCD_RST)  

#define LCD_DATAOUT(x) LCD_DATA->ODR=x; //�������
#define LCD_DATAIN     LCD_DATA->IDR;   //��������

#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
LCD_DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
} 



void LCD_GPIO_Init(void);
void Lcd_WriteIndex(uint8_t Index);
void Lcd_WriteData(uint8_t Data);
void Lcd_WriteReg(uint8_t Index,uint8_t Data);
uint16_t Lcd_ReadReg(uint8_t LCD_Reg);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(uint16_t Color);
void Lcd_SetXY(uint16_t x,uint16_t y);
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data);
unsigned int Lcd_ReadPoint(uint16_t x,uint16_t y);
void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end);
void LCD_WriteData_16Bit(uint16_t Data);


/******************************************gui**********************************/
uint16_t LCD_BGR2RGB(uint16_t c);
void Gui_Circle(uint16_t X,uint16_t Y,uint16_t R,uint16_t fc); 
void Gui_DrawLine(uint16_t x0, uint16_t y0,uint16_t x1, uint16_t y1,uint16_t Color);  
void Gui_box(uint16_t x, uint16_t y, uint16_t w, uint16_t h,uint16_t bc);
void Gui_box2(uint16_t x,uint16_t y,uint16_t w,uint16_t h, uint16_t mode);
void DisplayButtonDown(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void DisplayButtonUp(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
void Gui_DrawFont_GBK16(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s);
void Gui_DrawFont_GBK24(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s);
void Gui_DrawFont_Num32(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint16_t num) ;


#endif
