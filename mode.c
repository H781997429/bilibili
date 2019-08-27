#include "mode.h"
#include "key.h"

extern u8 mode;
extern u8 Key_tmp;
u8 time = 100;


void mode_value(void)
{
	if(Key_tmp == 0x10)
	{	
		mode++;
		Key_tmp = 0;
		Lcd_Clear(GRAY0);
	}
	switch(mode)
		{
			case 1:mode1();break;
			case 2:mode2();break;
			case 3:mode3();break;
			case 4:mode4();break;
			default:  break; 				
		}
	if(mode>4)
	{
		mode = 0;
	}
}
/************************模式一，初始化模式********************/
void mode1(void)
{
	static s8 tmpx,tmpy;

	if(Key_tmp != 0 )
	{	
		switch(Key_tmp)
		{
			case 0x01:tmpx++;break;
			case 0x02:tmpx--;break;
			case 0x03:tmpy++;break;
			case 0x04:tmpy--;break;
			case 0x05:tmpx=tmpx+10;break;
			case 0x06:tmpx=tmpx-10;break;
			case 0x07:tmpy=tmpy+10;break;
			case 0x08:tmpy=tmpy-10;break;
			case 0x09:time=time+1;break;
			case 0x0a:time=time-1;break;
			case 0x0b:time=time+10;break;
			case 0x0c:time=time-10;break;
			default:  break; 
		}
	Key_tmp = 0;
	}
	Gui_DrawFont_GBK16(2,5,BLUE,GRAY0,"俯仰角");
	Gui_DrawFont_Num32(20,22, BLUE, GRAY0, (90+tmpy)/100);
	Gui_DrawFont_Num32(50,22, BLUE, GRAY0, (90+tmpy)%100/10);
	Gui_DrawFont_Num32(80,22, BLUE, GRAY0, (90+tmpy)%10);
	Gui_DrawFont_GBK16(2,58,RED,GRAY0,"偏离角");
	Gui_DrawFont_Num32(20,74,RED,GRAY0,(90+tmpx)/100);
    Gui_DrawFont_Num32(50,74,RED,GRAY0,(90+tmpx)%100/10);
    Gui_DrawFont_Num32(80,74,RED,GRAY0,(90+tmpx)%10);	
	
	Gui_DrawFont_GBK16(2,107,RED,GRAY0,"充电时间");
	Gui_DrawFont_Num32(2,123,RED,GRAY0,(time)/100);
    Gui_DrawFont_Num32(30,123,RED,GRAY0,(time)%100/10);
	Gui_DrawFont_Num32(55,123,RED,GRAY0, 10);
    Gui_DrawFont_Num32(81,123,RED,GRAY0,(time)%10);	
	Gui_DrawFont_GBK16(112,139,RED,GRAY0, "s");
	
	Xout(90+tmpx);
	Yout(90-tmpy);
	
}
/*************************模式二，角度，距离模式*****************/
void mode2(void)
{
	Gui_DrawFont_GBK16(16,22,BLACK,GRAY0,"模式一");
	Gui_DrawFont_GBK16(16,52,BLUE,GRAY0,"模式二");
	Gui_DrawFont_GBK16(16,82,BLACK,GRAY0,"模式三");
	Gui_DrawFont_GBK16(16,112,BLACK,GRAY0,"模式四");

}
/**************************模式三，自动瞄准模式*****************/
void mode3(void)
{
	Gui_DrawFont_GBK16(16,22,BLACK,GRAY0,"模式一");
	Gui_DrawFont_GBK16(16,52,BLACK,GRAY0,"模式二");
	Gui_DrawFont_GBK16(16,82,BLUE,GRAY0,"模式三");
	Gui_DrawFont_GBK16(16,112,BLACK,GRAY0,"模式四");

}

/*********************模式四，扫描模式**************************/
void mode4(void)
{
	Gui_DrawFont_GBK16(16,22,BLACK,GRAY0,"模式一");
	Gui_DrawFont_GBK16(16,52,BLACK,GRAY0,"模式二");
	Gui_DrawFont_GBK16(16,82,BLACK,GRAY0,"模式三");
	Gui_DrawFont_GBK16(16,112,BLUE,GRAY0,"模式四");

}
