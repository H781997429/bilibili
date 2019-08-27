#include "Lcd_Driver.h"
#include "delay.h"
//#include "Picture.h"
#include "lcd_display.h"
unsigned char Num[10]={0,1,2,3,4,5,6,7,8,9};
void Redraw_Mainmenu(void)
{

	Lcd_Clear(GRAY0);
	
	DisplayButtonUp(15,20,113,40); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(16,22,BLACK,GRAY0,"ģʽһ");

	DisplayButtonUp(15,50,113,70); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(16,52,BLACK,GRAY0,"ģʽ��");

	DisplayButtonUp(15,80,113,100); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(16,82,BLACK,GRAY0,"ģʽ��");
	
	DisplayButtonUp(15,110,113,130); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(16,112,BLACK,GRAY0,"ģʽ��");
	delay_ms(50);
	

}

void Num_Test(void)
{
	u8 i=0;
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(16,20,RED,GRAY0,"Num Test");
	delay_ms(1000);
	Lcd_Clear(GRAY0);

	for(i=0;i<10;i++)
	{
	Gui_DrawFont_Num32((i%3)*40,32*(i/3)+5,RED,GRAY0,Num[i+1]);
	delay_ms(100);
	}
	
}

void Font_Test(void)
{
	delay_ms(1000);
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(16,30,YELLOW,GRAY0,"ģʽ");
	Gui_DrawFont_GBK16(0,100,BLUE,GRAY0,"Tel:13945374432");
	Gui_DrawFont_GBK16(0,130,RED,GRAY0, "QQ:xiaojiang");	
	delay_ms(1800);	
}

void Color_Test(void)
{
	u8 i=1;
	Lcd_Clear(GRAY0);
	
	Gui_DrawFont_GBK16(20,10,BLUE,GRAY0,"Color Test");
	delay_ms(200);

	while(i--)
	{
		Lcd_Clear(WHITE);
		Lcd_Clear(BLACK);
		Lcd_Clear(RED);
	  	Lcd_Clear(GREEN);
	  	Lcd_Clear(BLUE);
	}		
}

//ȡģ��ʽ ˮƽɨ�� ������ ��λ��ǰ
void showimage(const unsigned char *p) //��ʾͼƬ
{
  	int i; 
	unsigned char picH,picL;
	Lcd_Clear(WHITE); //����  
	
		
			Lcd_SetRegion(0,0,128,160);		//��������
		    for(i=0;i<128*160;i++)
			 {	
			 	picL=*(p+i*2);	//���ݵ�λ��ǰ
				picH=*(p+i*2+1);				
				LCD_WriteData_16Bit(picH<<8|picL);  						
			 }	
		 
			
}

void Menu_Init(void)
{
	Lcd_Init();
	LCD_LED_SET;
	Lcd_Clear(GRAY0);
	//Redraw_Mainmenu();
}
void Test_Demo(void)
{
	Lcd_Init();
	LCD_LED_SET;//ͨ��IO���Ʊ�����				
	//Redraw_Mainmenu();//�������˵�(�����������ڷֱ��ʳ�������ֵ�����޷���ʾ)
	//Color_Test();//�򵥴�ɫ������
	//Num_Test();//������������
	//Font_Test();//��Ӣ����ʾ����		
	//showimage(gImage_xj);//ͼƬ��ʾʾ��
	delay_ms(2000);
	//LCD_LED_CLR;//IO���Ʊ�����	
	
}
