//�з���ֵ�ľ���������ó���,����8��io��������,ֻҪ�ڶ�Ӧ����ͷ�ļ��и��ĺ궨�弴��
//������ʹ�ö�ʱ����ʱ,ÿ10ms��һ���ж��жϰ����Ƿ񱻰���
//�뱾�����йص��������������ļ���.hͷ�ļ��·�ע�ʹ�,����Ϊʾ�����ɵ���
//2019.8.24  v1.0

#include <delay.h>
#include <key.h>
u8 Key_tmp;

//��ʼ��rcc
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

//��ʼ��column1111,row0000
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


//��ʼ��row1111,column0000
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

//stm32������̷�תɨ�跨
//���˾������ɨ�������ڶ�ʱ���жϷ��������
//ÿ10ms����һ���жϷ������
void scan_key(void)
{
	u8 TEMP_COMBINE = 0, TEMP_ROW = 0, TEMP_COLUMN = 0;
 	s8 Key_value = 20;//��ʼֵ����Ϊ0~15 
	static u8 key_count = 0;//�������ж�ɨ��Ĵ���
	
	ROCI_GPIO_Config();//��ʼ����
	TEMP_ROW = (u8)(((u8)DETECT_C1) << 3) |
				   (((u8)DETECT_C2) << 2) |
				   (((u8)DETECT_C3) << 1) |
				   (((u8)DETECT_C4) << 0);
	if(TEMP_ROW != 0x0f)
	{
		  
        //��ֹ����ʱ,�����������±������
        if (key_count <= 2)
        {
            key_count++;
        }
	}
	//����������������̧���������0 
	else
	{
		key_count = 0;
		//TEMP_ROW = 0x0f;	
	}
	//����������2��ɨ������ڰ���״̬
    //����Ϊ����ȷʵ��������
    if (key_count == 2)
    {          	
		RICO_GPIO_Config();
		TEMP_COLUMN = (u8)(((u8)DETECT_R1) << 3) |
						  (((u8)DETECT_R2) << 2) |
						  (((u8)DETECT_R3) << 1) |
						  (((u8)DETECT_R4) << 0);
		TEMP_COMBINE = (u8)((TEMP_ROW << 4) | TEMP_COLUMN); // Combine the two situation and we can know which key was pressed down.
		printf("��ֵ��%x\r\n",TEMP_COMBINE);
		switch(TEMP_COMBINE)
		{
			 //������Ӧ��������Ը���������������صļ�ֵ�� 
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
		printf("��ֵ��%c\r\n",Key_value);
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
	GPIO_RCC_Config();//��ʼ��ʱ��
	printf("\nInit Key!");
}
