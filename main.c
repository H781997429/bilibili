#include "stm32f4xx.h"
#include "pwmout.h"
#include "delay.h"
#include "mode.h"
#include "lcd_driver.h"
#include "lcd_display.h"
#include "key.h"
#include "bsp_usart.h"
#include "relay.h"

u8 mode=0;
extern u8 Key_tmp;
extern void Menu_Init(void);

int main()
{
	
	SysTick_Init();
	Debug_USART_Config();
	printf("\nInit beginning! ---->>>>");
	PWM_Configuration();		
	Menu_Init();
	RELAY_GPIO_Config();
	KEY_GPIO_ConfigAndDetect();
	TIMx_Configuration();
	printf("\nInit end! ");
	while(1)
	{
		mode_value();
		
	}
}




