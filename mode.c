#include "mode.h"
#include "key.h"

extern u8 Key_tmp;
/************************ģʽһ����ʼ��ģʽ********************/
void mode1(void)
{
	static s8 tmpx,tmpy;

	if(Key_tmp != 0)
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
			default:  break; 
		}
	Key_tmp = 0;
	}
	Gui_DrawFont_GBK16(16,22,BLUE,GRAY0,"������");
	Gui_DrawFont_Num32(20,50, BLUE, GRAY0, (90+tmpy)/100);
	Gui_DrawFont_Num32(50,50, BLUE, GRAY0, (90+tmpy)%100/10);
	Gui_DrawFont_Num32(80,50, BLUE, GRAY0, (90+tmpy)%10);
	Gui_DrawFont_GBK16(16,85,RED,GRAY0,"ƫ���");
	Gui_DrawFont_Num32(20,112,RED,GRAY0,(90+tmpx)/100);
    Gui_DrawFont_Num32(50,112,RED,GRAY0,(90+tmpx)%100/10);
    Gui_DrawFont_Num32(80,112,RED,GRAY0,(90+tmpx)%10);	
	Xout(90+tmpx);
	Yout(90-tmpy);
	
}
/*************************ģʽ�����Ƕȣ�����ģʽ*****************/
void mode2(void)
{
	Gui_DrawFont_GBK16(16,22,BLACK,GRAY0,"ģʽһ");
	Gui_DrawFont_GBK16(16,52,BLUE,GRAY0,"ģʽ��");
	Gui_DrawFont_GBK16(16,82,BLACK,GRAY0,"ģʽ��");
	Gui_DrawFont_GBK16(16,112,BLACK,GRAY0,"ģʽ��");

}
/**************************ģʽ�����Զ���׼ģʽ*****************/
void mode3(void)
{
	Gui_DrawFont_GBK16(16,22,BLACK,GRAY0,"ģʽһ");
	Gui_DrawFont_GBK16(16,52,BLACK,GRAY0,"ģʽ��");
	Gui_DrawFont_GBK16(16,82,BLUE,GRAY0,"ģʽ��");
	Gui_DrawFont_GBK16(16,112,BLACK,GRAY0,"ģʽ��");

}

/*********************ģʽ�ģ�ɨ��ģʽ**************************/
void mode4(void)
{
	Gui_DrawFont_GBK16(16,22,BLACK,GRAY0,"ģʽһ");
	Gui_DrawFont_GBK16(16,52,BLACK,GRAY0,"ģʽ��");
	Gui_DrawFont_GBK16(16,82,BLACK,GRAY0,"ģʽ��");
	Gui_DrawFont_GBK16(16,112,BLUE,GRAY0,"ģʽ��");

}
