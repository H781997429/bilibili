#include "pwmout.h"
/****************************************************
双路pwm输出控制舵机
pwm周期10ms,频率100hz.舵机控制180度正脉宽900-1 -> 4500-1
脉宽+1 角度增大0.05度
900-1 -> 0度  |  2700-1 -> 90度 | 4500-1 -> 180度
角度计算公式:pwmout=角度*20+900-1
****************************************************/


/****************初始化pwm输出引脚*******************/
static void TIM_GPIO_Config(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启相关的GPIO外设时钟*/
	RCC_AHB1PeriphClockCmd (OCPWMX_GPIO_CLK | OCPWMY_GPIO_CLK, ENABLE); 
    /* 定时器通道引脚复用 */
	GPIO_PinAFConfig(OCPWMX_GPIO_PORT,OCPWMX_PINSOURCE,OCPWMX_AF); 
    GPIO_PinAFConfig(OCPWMY_GPIO_PORT,OCPWMY_PINSOURCE,OCPWMY_AF); 
	/* 定时器通道引脚配置 */															   
	GPIO_InitStructure.GPIO_Pin = OCPWMX_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(OCPWMX_GPIO_PORT, &GPIO_InitStructure);
/********************************************************/															   
	GPIO_InitStructure.GPIO_Pin = OCPWMY_PIN;	
	GPIO_Init(OCPWMY_GPIO_PORT, &GPIO_InitStructure);
}


/*********************初始化timex tim5*******************/
static void TIM_PWM_X_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	// 开启TIMx_CLK
  RCC_APB1PeriphClockCmd(TIMX_CLK, ENABLE); 

  /* 累计 TIM_Period个后产生一个更新或者中断*/		
  //当定时器从0计数到8999，即为9000次，为一个定时周期
  TIM_TimeBaseStructure.TIM_Period = 18000-1;       
	
	// 通用控制定时器时钟源TIMxCLK = HCLK/2=90MHz 
	// 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=1800000Hz
  TIM_TimeBaseStructure.TIM_Prescaler = 50-1;	
  // 采样时钟分频
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  // 计数方式
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	// 初始化定时器TIMx, x[2,3,4,5,12,13,14] 
	TIM_TimeBaseInit(TIMX, &TIM_TimeBaseStructure);
	/*PWM模式配置*/
	/* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = 2700-1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //当定时器计数值小于CCR1_Val时为高电平
  TIM_OC2Init(TIMX, &TIM_OCInitStructure);	 //使能通道2
	/*使能通道1重载*/
	TIM_OC2PreloadConfig(TIMX, TIM_OCPreload_Enable);
	// 使能定时器
	TIM_ITConfig(TIMX,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIMX, ENABLE);		
}

/**********************************y坐标pwm 100Hz**********/
static void TIM_PWM_Y_Config(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	

  RCC_APB1PeriphClockCmd(TIMY_CLK, ENABLE); 
  TIM_TimeBaseStructure.TIM_Period = 18000-1;       
  TIM_TimeBaseStructure.TIM_Prescaler = 50-1;	
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIMY, &TIM_TimeBaseStructure);
	/*PWM模式配置*/
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = 2700-1;//初始值
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //当定时器计数值小于CCR1_Val时为高电平
  TIM_OC3Init(TIMY, &TIM_OCInitStructure);	 //使能通道3
  TIM_OC3PreloadConfig(TIMY, TIM_OCPreload_Enable);
  TIM_ITConfig(TIMY,TIM_IT_Update,ENABLE);
	// 使能定时器
  TIM_Cmd(TIMY, ENABLE);		
}
void PWM_Configuration(void)
{
	TIM_GPIO_Config();
	TIM_PWM_X_Config();
	TIM_PWM_Y_Config();
}

/**********************************************************/

/*定义角度->pwm转换函数*/
void Xout(float angle)
{
	if(angle>=0 && angle<=180)
	{
		TIM_SetCompare2(TIMX,angle*20+899);
		//注意通道
	}
}
void Yout(float angle)
{
	if(angle>=0 && angle<=180)
	{
		TIM_SetCompare3(TIMY,angle*20+899);
		//注意通道
	}
}

/****************************初始化调平*********************/

