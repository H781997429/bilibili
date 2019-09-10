#include "stm32f4xx.h"
#include "pwmout.h"
#include "delay.h"
#include "mode.h"
#include "lcd_driver.h"
#include "lcd_display.h"
#include "key.h"
#include "bsp_usart.h"
#include "relay.h"
#include "bsp_adc.h"
// ADC转换的电压值通过MDA方式传到SRAM
__IO uint16_t ADC_ConvertedValue;
float ADC_Vol; 
u8 mode=0;
extern u8 Key_tmp;
extern void Menu_Init(void);

int main()
{
	Rheostat_Init();
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
		ADC_Vol =(float) ADC_ConvertedValue/4096*(float)3.3; // 读取转换的AD值

        printf("\r\n AD value = 0x%04X \r\n", ADC_ConvertedValue); 
        printf("\r\n AD value = %f V \r\n",ADC_Vol); 
		delay_ms(100);
	}
}




