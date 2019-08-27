//有返回值的矩阵键盘配置程序,所用8个io可以乱序,只要在对应按键头文件中更改宏定义即可
//本程序使用定时器定时,每10ms进一次中断判断按键是否被按下
//与本程序有关的其他外设配置文件在.h头文件下方注释处,可作为示例自由调用
//2019.8.24  v1.0

#include <delay.h>
#include <key.h>
u8 Key_tmp;

//初始化rcc
void GPIO_RCC_Config(void)
{
	RCC_AHB1PeriphClockCmd(C1_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(C2_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(C3_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(C4_GPIO_CLK, ENABLE);

	RCC_AHB1PeriphClockCmd(R1_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(R2_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(R3_GPIO_CLK, ENABLE);
	RCC_AHB1PeriphClockCmd(R4_GPIO_CLK, ENABLE);
}

//初始化column1111,row0000
void ROCI_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_Structure;
	
	//============ Column =============
	GPIO_Structure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Structure.GPIO_OType = GPIO_OType_PP;
	GPIO_Structure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Structure.GPIO_Pin = C1_PIN;
	GPIO_Init(C1_GPIO_PORT, &GPIO_Structure);

	GPIO_Structure.GPIO_Pin = C2_PIN;
	GPIO_Init(C2_GPIO_PORT, &GPIO_Structure);

	GPIO_Structure.GPIO_Pin = C3_PIN;
	GPIO_Init(C3_GPIO_PORT, &GPIO_Structure);
	
	GPIO_Structure.GPIO_Pin = C4_PIN;
	GPIO_Init(C4_GPIO_PORT, &GPIO_Structure);
	
	//============== Row ===============
	GPIO_Structure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Structure.GPIO_OType = GPIO_OType_PP;
	GPIO_Structure.GPIO_PuPd = GPIO_PuPd_DOWN;
	
	GPIO_Structure.GPIO_Pin = R1_PIN;
	GPIO_Init(R1_GPIO_PORT, &GPIO_Structure);

	GPIO_Structure.GPIO_Pin = R2_PIN;
	GPIO_Init(R2_GPIO_PORT, &GPIO_Structure);

	GPIO_Structure.GPIO_Pin = R3_PIN;
	GPIO_Init(R3_GPIO_PORT, &GPIO_Structure);
	
	GPIO_Structure.GPIO_Pin = R4_PIN;
	GPIO_Init(R4_GPIO_PORT, &GPIO_Structure);
	
	GPIO_ResetBits(R1_GPIO_PORT, R1_PIN);
	GPIO_ResetBits(R2_GPIO_PORT, R2_PIN);
	GPIO_ResetBits(R3_GPIO_PORT, R3_PIN);
	GPIO_ResetBits(R4_GPIO_PORT, R4_PIN);
	
}


//初始化row1111,column0000
void RICO_GPIO_Config(void)
{
	u16 j;
	GPIO_InitTypeDef GPIO_Structure;
	
	//============== Row ==================
	GPIO_Structure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Structure.GPIO_OType = GPIO_OType_PP;
	GPIO_Structure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Structure.GPIO_Pin = R1_PIN;
	GPIO_Init(R1_GPIO_PORT, &GPIO_Structure);

	GPIO_Structure.GPIO_Pin = R2_PIN;
	GPIO_Init(R2_GPIO_PORT, &GPIO_Structure);
	
	GPIO_Structure.GPIO_Pin = R3_PIN;
	GPIO_Init(R3_GPIO_PORT, &GPIO_Structure);
	
	GPIO_Structure.GPIO_Pin = R4_PIN;
	GPIO_Init(R4_GPIO_PORT, &GPIO_Structure);
	
	//============ Column ================
	GPIO_Structure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Structure.GPIO_OType = GPIO_OType_PP;
	GPIO_Structure.GPIO_PuPd = GPIO_PuPd_DOWN;
	
	GPIO_Structure.GPIO_Pin = C1_PIN;
	GPIO_Init(C1_GPIO_PORT, &GPIO_Structure);

	GPIO_Structure.GPIO_Pin = C2_PIN;
	GPIO_Init(C2_GPIO_PORT, &GPIO_Structure);
	
	GPIO_Structure.GPIO_Pin = C3_PIN;
	GPIO_Init(C3_GPIO_PORT, &GPIO_Structure);
	
	GPIO_Structure.GPIO_Pin = C4_PIN;
	GPIO_Init(C4_GPIO_PORT, &GPIO_Structure);
	
	GPIO_ResetBits(C1_GPIO_PORT, C1_PIN);
	GPIO_ResetBits(C2_GPIO_PORT, C2_PIN);
	GPIO_ResetBits(C3_GPIO_PORT, C3_PIN);
	GPIO_ResetBits(C4_GPIO_PORT, C4_PIN);
	for(j=0;j<1000;j++);
}

//stm32矩阵键盘翻转扫描法
//将此矩阵键盘扫描程序放在定时器中断服务程序里
//每10ms进入一次中断服务程序
void scan_key(void)
{
	u8 TEMP_COMBINE = 0, TEMP_ROW = 0, TEMP_COLUMN = 0;
 	s8 Key_value = 20;//初始值不能为0~15 
	static u8 key_count = 0;//按键被中断扫描的次数
	
	ROCI_GPIO_Config();//初始化行
	TEMP_ROW = (u8)(((u8)DETECT_C1) << 3) |
				   (((u8)DETECT_C2) << 2) |
				   (((u8)DETECT_C3) << 1) |
				   (((u8)DETECT_C4) << 0);
	if(TEMP_ROW != 0x0f)
	{
		  
        //防止长按时,持续自增导致变量溢出
        if (key_count <= 2)
        {
            key_count++;
        }
	}
	//若产生抖动按键被抬起则计数清0 
	else
	{
		key_count = 0;
		//TEMP_ROW = 0x0f;	
	}
	//若按键连续2次扫描均处于按下状态
    //则认为按键确实被按下了
    if (key_count == 2)
    {          	
		RICO_GPIO_Config();
		TEMP_COLUMN = (u8)(((u8)DETECT_R1) << 3) |
						  (((u8)DETECT_R2) << 2) |
						  (((u8)DETECT_R3) << 1) |
						  (((u8)DETECT_R4) << 0);
		TEMP_COMBINE = (u8)((TEMP_ROW << 4) | TEMP_COLUMN); // Combine the two situation and we can know which key was pressed down.
		printf("数值：%x\r\n",TEMP_COMBINE);
		switch(TEMP_COMBINE)
		{
			 //按键对应的码表（可以根据需求调整欲返回的键值） 
            case S1: Key_tmp = 0x01;Key_value = '1'; break;
            case S2: Key_tmp = 0x02;Key_value = '2'; break;
            case S3: Key_tmp = 0x03;Key_value = '3'; break;                
            case S4: Key_tmp = 0x04;Key_value = '4'; break;                                              
            case S5: Key_tmp = 0x05;Key_value = '5'; break;
            case S6: Key_tmp = 0x06;Key_value = '6'; break;
            case S7: Key_tmp = 0x07;Key_value = '7'; break;
            case S8: Key_tmp = 0x08;Key_value = '8'; break;                                  
            case S9: Key_tmp = 0x09;Key_value = '9'; break;
            case S10: Key_tmp = 0x0a;Key_value = 'A'; break;
            case S11: Key_tmp = 0x0b;Key_value = 'B'; break;
            case S12: Key_tmp = 0x0c;Key_value = 'C'; break;                                    
            case S13: Key_tmp = 0x0d;Key_value = 'D'; break;
            case S14: Key_tmp = 0x0e;Key_value = 'E'; break;
            case S15: Key_tmp = 0x0f;Key_value = 'F'; break;
            case S16: Key_tmp = 0x10;Key_value = 'G'; break;
            default:   break;     
		}
		printf("键值：%c\r\n",Key_value);
		TEMP_COLUMN = (u8)(((u8)DETECT_R1)<<3) |
						  (((u8)DETECT_R2)<<2) |
						  (((u8)DETECT_R3)<<1) |
						  (((u8)DETECT_R4)<<0);
		if (TEMP_COLUMN == 0x0F)
		{
			key_count = 0;  
		}
	}
//	return Key_tmp;	
}
			



void KEY_GPIO_ConfigAndDetect(void)
{
	GPIO_RCC_Config();//初始化时钟
	printf("\nInit Key!");
}
