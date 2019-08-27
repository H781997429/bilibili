#include "pwmout.h"
/****************************************************
˫·pwm������ƶ��
pwm����10ms,Ƶ��100hz.�������180��������900-1 -> 4500-1
����+1 �Ƕ�����0.05��
900-1 -> 0��  |  2700-1 -> 90�� | 4500-1 -> 180��
�Ƕȼ��㹫ʽ:pwmout=�Ƕ�*20+900-1
****************************************************/


/****************��ʼ��pwm�������*******************/
static void TIM_GPIO_Config(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*������ص�GPIO����ʱ��*/
	RCC_AHB1PeriphClockCmd (OCPWMX_GPIO_CLK | OCPWMY_GPIO_CLK, ENABLE); 
    /* ��ʱ��ͨ�����Ÿ��� */
	GPIO_PinAFConfig(OCPWMX_GPIO_PORT,OCPWMX_PINSOURCE,OCPWMX_AF); 
    GPIO_PinAFConfig(OCPWMY_GPIO_PORT,OCPWMY_PINSOURCE,OCPWMY_AF); 
	/* ��ʱ��ͨ���������� */															   
	GPIO_InitStructure.GPIO_Pin = OCPWMX_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(OCPWMX_GPIO_PORT, &GPIO_InitStructure);
/********************************************************/															   
	GPIO_InitStructure.GPIO_Pin = OCPWMY_PIN;	
	GPIO_Init(OCPWMY_GPIO_PORT, &GPIO_InitStructure);
}


/*********************��ʼ��timex tim5*******************/
static void TIM_PWM_X_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	// ����TIMx_CLK
  RCC_APB1PeriphClockCmd(TIMX_CLK, ENABLE); 

  /* �ۼ� TIM_Period�������һ�����»����ж�*/		
  //����ʱ����0������8999����Ϊ9000�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Period = 18000-1;       
	
	// ͨ�ÿ��ƶ�ʱ��ʱ��ԴTIMxCLK = HCLK/2=90MHz 
	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=1800000Hz
  TIM_TimeBaseStructure.TIM_Prescaler = 50-1;	
  // ����ʱ�ӷ�Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  // ������ʽ
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	// ��ʼ����ʱ��TIMx, x[2,3,4,5,12,13,14] 
	TIM_TimeBaseInit(TIMX, &TIM_TimeBaseStructure);
	/*PWMģʽ����*/
	/* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = 2700-1;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
  TIM_OC2Init(TIMX, &TIM_OCInitStructure);	 //ʹ��ͨ��2
	/*ʹ��ͨ��1����*/
	TIM_OC2PreloadConfig(TIMX, TIM_OCPreload_Enable);
	// ʹ�ܶ�ʱ��
	TIM_ITConfig(TIMX,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIMX, ENABLE);		
}

/**********************************y����pwm 100Hz**********/
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
	/*PWMģʽ����*/
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = 2700-1;//��ʼֵ
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  	  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
  TIM_OC3Init(TIMY, &TIM_OCInitStructure);	 //ʹ��ͨ��3
  TIM_OC3PreloadConfig(TIMY, TIM_OCPreload_Enable);
  TIM_ITConfig(TIMY,TIM_IT_Update,ENABLE);
	// ʹ�ܶ�ʱ��
  TIM_Cmd(TIMY, ENABLE);		
}
void PWM_Configuration(void)
{
	TIM_GPIO_Config();
	TIM_PWM_X_Config();
	TIM_PWM_Y_Config();
}

/**********************************************************/

/*����Ƕ�->pwmת������*/
void Xout(float angle)
{
	if(angle>=0 && angle<=180)
	{
		TIM_SetCompare2(TIMX,angle*20+899);
		//ע��ͨ��
	}
}
void Yout(float angle)
{
	if(angle>=0 && angle<=180)
	{
		TIM_SetCompare3(TIMY,angle*20+899);
		//ע��ͨ��
	}
}

/****************************��ʼ����ƽ*********************/

