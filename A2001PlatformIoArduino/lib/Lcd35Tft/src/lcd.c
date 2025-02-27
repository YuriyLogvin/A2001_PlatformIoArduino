#include <lcd.h>
#include "stdlib.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//����Ӳ������Ƭ��STM32F103RBT6,��Ƶ72M  ��Ƭ��������ѹ3.3V
//QDtech-TFTҺ������ for STM32 IOģ��
//xiao��@ShenZhen QDtech co.,LTD
//��˾��վ:www.qdtech.net
//�Ա���վ��http://qdtech.taobao.com
//��˾�ṩ����֧�֣��κμ������⻶ӭ��ʱ����ѧϰ
//�̻�(����) :+86 0755-23594567 
//�ֻ�:15989313508���빤�� 
//����:QDtech2008@gmail.com 
//Skype:QDtech2008
//��������QQȺ:324828016
//��������:2013/5/13
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������ȫ�����Ӽ������޹�˾ 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////	
/****************************************************************************************************
//=======================================Һ���������߽���==========================================//
STM32 PB���Һ����DB0~DB16,��������ΪDB0��PB0,..DB15��PB15.   
//=======================================Һ���������߽���==========================================//
//LCD_CS	��PC9	//Ƭѡ�ź�
//LCD_RS	��PC8	//�Ĵ���/����ѡ���ź�
//LCD_WR	��PC7	//д�ź�
//LCD_RD	��PC6	//���ź�
//LCD_RST	��PC5	//��λ�ź�
//LCD_LED	��PC10	//��������ź�(�ߵ�ƽ����)
//=========================================������������=========================================//
//��ʹ�ô�������ģ�鱾��������������ɲ�����
//MO(MISO)	��PC2	//SPI�������
//MI(MOSI)	��PC3	//SPI��������
//PEN		��PC1	//�������ж��ź�
//TCS		��PC13	//����ICƬѡ
//CLK		��PC0	//SPI����ʱ��
**************************************************************************************************/	
	   
//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;

//������ɫ,������ɫ
u16 POINT_COLOR = 0x0000,BACK_COLOR = 0xFFFF;  
u16 DeviceCode;	 


//******************************************************************
//��������  LCD_WR_REG
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ��Һ��������д��д16λָ��
//���������Reg:��д���ָ��ֵ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_WR_REG(u8 data)
{ 
	LCD_RS_CLR;//д��ַ  
 	LCD_CS_CLR; 
	DATAOUT(data); 
	LCD_WR_CLR; 
	LCD_WR_SET; 
 	LCD_CS_SET; 	
}

//******************************************************************
//��������  LCD_WR_DATA
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ��Һ��������д��д16λ����
//���������Data:��д�������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_WR_DATA(u16 data)
{
	LCD_RS_SET;
	LCD_CS_CLR;
	DATAOUT(data);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;

}
//******************************************************************
//��������  LCD_DrawPoint_16Bit
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    8λ���������д��һ��16λ����
//���������(x,y):�������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_DrawPoint_16Bit(u16 color)
{
#if LCD_USE8BIT_MODEL==1
	LCD_CS_CLR;
	LCD_RD_SET;
	LCD_RS_SET;//д��ַ  	 
	DATAOUT(color>>8);	
	LCD_WR_CLR;
	LCD_WR_SET;	
	DATAOUT(color);	
	LCD_WR_CLR;
	LCD_WR_SET;	 
	LCD_CS_SET;
#else
	LCD_WR_DATA(color); 
#endif


}

void LCD_DrawPoint_RGB(u8 r, u8 g, u8 b)
{
#if LCD_Use18BitPixel==1
	LCD_CS_CLR;
	LCD_RD_SET;
	LCD_RS_SET;
	DATAOUT(r<<2);
	LCD_WR_CLR;
	LCD_WR_SET;
	DATAOUT(g<<2);
	LCD_WR_CLR;
	LCD_WR_SET;
	DATAOUT(b<<2);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;
#else
	u16 color = 0;
	if (r==g && g==b)
		color = ((r << 10) & 0xF800) | ((g << 5) & 0x7C0) | ((b >> 1) & 0x1F); //����� ��� 1�� ������ ����� ����
	else
		color = ((r << 10) & 0xF800) | ((g << 5) & 0x7E0) | ((b >> 1) & 0x1F);

	LCD_CS_CLR;
	LCD_RD_SET;
	LCD_RS_SET;//д��ַ
	DATAOUT(color>>8);
	LCD_WR_CLR;
	LCD_WR_SET;
	DATAOUT(color);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;
#endif
}

void LCD_DrawPointAt_RGB(u16 x,u16 y, u8 r, u8 g, u8 b)
{
	LCD_SetCursor(x,y);
	LCD_DrawPoint_RGB(r,g,b);
}

//******************************************************************
//��������  LCD_DrawPoint
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ��ָ��λ��д��һ�����ص�����
//���������(x,y):�������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_DrawPoint(u16 x,u16 y)
{
#if LCD_USE8BIT_MODEL==1
#if LCD_Use18BitPixel==1
#else
	LCD_SetCursor(x,y);//���ù��λ��
	LCD_CS_CLR;
	LCD_RD_SET;
	LCD_RS_SET;//д��ַ
	DATAOUT(POINT_COLOR>>8);
	LCD_WR_CLR;
	LCD_WR_SET;
	DATAOUT(POINT_COLOR);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;
#endif //LCD_Use18BitPixel==1
#else
	LCD_SetCursor(x,y);//���ù��λ��
	LCD_WR_DATA(POINT_COLOR);
#endif


}

//******************************************************************
//��������  LCD_WriteReg
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    д�Ĵ�������
//���������LCD_Reg:�Ĵ�����ַ
//			LCD_RegValue:Ҫд�������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{	
	LCD_WR_REG(LCD_Reg);  
	LCD_WR_DATA(LCD_RegValue);	    		 
}	   
	 
//******************************************************************
//��������  LCD_WriteRAM_Prepare
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ��ʼдGRAM
//			�ڸ�Һ��������RGB����ǰ��Ӧ�÷���дGRAMָ��
//�����������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
}	 

//******************************************************************
//��������  LCD_Clear
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    LCDȫ�������������
//���������Color:Ҫ���������ɫ
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_Clear(u16 Color)
{
	u32 index=0;      
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);	
#if LCD_USE8BIT_MODEL==1
	LCD_RS_SET;//д���� 
	LCD_CS_CLR;	   
	for(index=0;index<lcddev.width*lcddev.height;index++)
	{
		DATAOUT(Color>>8);	
		LCD_WR_CLR;
		LCD_WR_SET;	
		
		DATAOUT(Color);	
		LCD_WR_CLR;
		LCD_WR_SET;	   
	}
	LCD_CS_SET;	
#else //16λģʽ
	for(index=0;index<lcddev.width*lcddev.height;index++)
	{
		LCD_WR_DATA(Color);		  
	}
#endif
	
} 

void _PinInit()
{
	LCD_RST_SET;
	LCD_CS_SET;
	LCD_WR_SET;
	LCD_RD_SET;
	LCD_RS_CLR;

}

// Data write strobe, ~2 instructions and always inline
#define WR_STROBE { LCD_WR_CLR; LCD_WR_SET; }

//******************************************************************
//��������  LCD_Reset
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    LCD��λ������Һ����ʼ��ǰҪ���ô˺���
//�����������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_RESET(void)
{

	_PinInit();
	delay_ms(10);

	LCD_RST_CLR;
	//delay_ms(100);
	delay_ms(2);
	LCD_RST_SET;

	LCD_RS_CLR;//д��ַ
 	LCD_CS_CLR;
	DATAOUT(0);
	WR_STROBE;

	for(uint8_t i=0; i<3; i++) WR_STROBE; // Three extra 0x00s

	LCD_CS_SET;

	delay_ms(2);

}
 	 
//******************************************************************
//��������  LCD_Init
//ILI9486
//******************************************************************
void LCD_Init(void)
{  

 	LCD_RESET();

	//************* Start Initial Sequence **********//
 	//exit_sleep_mode
	LCD_WR_REG(0x11);
	delay_ms(50);
	//Power Setting
	//0xC0, 2, 0x0d, 0x0d,        //Power Control 1 [0E 0E]
	LCD_WR_REG(0xC0);
	LCD_WR_DATA(0x0d);
	LCD_WR_DATA(0x0d);

    //0xC1, 2, 0x43, 0x00,        //Power Control 2 [43 00]
	LCD_WR_REG(0xC1);
	LCD_WR_DATA(0x43);
	LCD_WR_DATA(0x00);

    //0xC2, 1, 0x00,      //Power Control 3 [33]
	LCD_WR_REG(0xC2);
	LCD_WR_DATA(0x00);

    //0xC5, 4, 0x00, 0x48, 0x00, 0x48,    //VCOM  Control 1 [00 40 00 40]
	LCD_WR_REG(0xC5);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x48);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x48);

    //0xB4, 1, 0x00,      //Inversion Control [00]
	LCD_WR_REG(0xB4);
	LCD_WR_DATA(0x00);

    //0xB6, 3, 0x02, 0x02, 0x3B,  // Display Function Control [02 02 3B]
	LCD_WR_REG(0xB6);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x3B);

/*	LCD_WR_REG(0x36);
#ifdef ORIENTATION_VERTICAL
	LCD_WR_DATA(0x0A);
#else //ORIENTATION_VERTICAL
	LCD_WR_DATA(0x09);
#endif //ORIENTATION_VERTICAL*/

	//set_pixel_format
	LCD_WR_REG(0x3A);
#if LCD_Use18BitPixel
	LCD_WR_DATA(0x66);
#else
	//LCD_WR_DATA(0x55);
	//LCD_WR_DATA(0x11);
#endif

	//0xE0, 15, 0x0F, 0x21, 0x1C, 0x0B, 0x0E, 0x08, 0x49, 0x98, 0x38, 0x09, 0x11, 0x03, 0x14, 0x10, 0x00,
	LCD_WR_REG(0xE0);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x21);
	LCD_WR_DATA(0x1C);
	LCD_WR_DATA(0x0B);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x49);
	LCD_WR_DATA(0x98);
	LCD_WR_DATA(0x38);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x14);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x00);
	//0xE1, 15, 0x0F, 0x2F, 0x2B, 0x0C, 0x0E, 0x06, 0x47, 0x76, 0x37, 0x07, 0x11, 0x04, 0x23, 0x1E, 0x00,
	LCD_WR_REG(0xE1);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x2F);
	LCD_WR_DATA(0x2B);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x0E);
	LCD_WR_DATA(0x06);
	LCD_WR_DATA(0x47);
	LCD_WR_DATA(0x76);
	LCD_WR_DATA(0x37);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x04);
	LCD_WR_DATA(0x23);
	LCD_WR_DATA(0x1E);
	LCD_WR_DATA(0x00);


	//Gamma Setting
	/*LCD_WR_REG(0xC8);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x32);
	LCD_WR_DATA(0x36);
	LCD_WR_DATA(0x45);
	LCD_WR_DATA(0x06);
	LCD_WR_DATA(0x16);
	LCD_WR_DATA(0x37);
	LCD_WR_DATA(0x75);
	LCD_WR_DATA(0x77);
	LCD_WR_DATA(0x54);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x00);*/
	
	
	//set_column_address
	/*LCD_WR_REG(0x2A);
	delay_ms(1);
	LCD_WR_DATA(0x00);
	delay_ms(1);
	LCD_WR_DATA(0x00);
	delay_ms(1);
	LCD_WR_DATA(0x01);
	delay_ms(1);
	LCD_WR_DATA(0x3F);
	delay_ms(1);*/
	
	//set_page_address
	/*LCD_WR_REG(0x2B);
	delay_ms(1);
	LCD_WR_DATA(0x00);
	delay_ms(1);
	LCD_WR_DATA(0x00);
	delay_ms(1);
	LCD_WR_DATA(0x01);
	delay_ms(1);
	LCD_WR_DATA(0xE0);
	delay_ms(100);*/

	//set_display_on
	LCD_WR_REG(0x29);

	//LCD_WR_REG(0x002c);

	delay_ms(50);

	LCD_SetParam();//����LCD����
	LCD_LED(1);//��������

	//LCD_Clear(WHITE);


	//LCD_WR_REG(0x39);
}

void LCD_InitOld(void)
{

 	LCD_RESET();

	//************* Start Initial Sequence **********//
	LCD_WR_REG(0x11);
	delay_ms(20);
	LCD_WR_REG(0xD0);
	LCD_WR_DATA(0x07);
	LCD_WR_DATA(0x42);
	LCD_WR_DATA(0x18);

	LCD_WR_REG(0xD1);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x07);//07
	LCD_WR_DATA(0x10);

	LCD_WR_REG(0xD2);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x02);

	LCD_WR_REG(0xC0);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x3B);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x11);

	LCD_WR_REG(0xC5);
	LCD_WR_DATA(0x03);

	LCD_WR_REG(0xC8);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x32);
	LCD_WR_DATA(0x36);
	LCD_WR_DATA(0x45);
	LCD_WR_DATA(0x06);
	LCD_WR_DATA(0x16);
	LCD_WR_DATA(0x37);
	LCD_WR_DATA(0x75);
	LCD_WR_DATA(0x77);
	LCD_WR_DATA(0x54);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0x36);
	LCD_WR_DATA(0x0A);

	LCD_WR_REG(0x3A);
	LCD_WR_DATA(0x55);

	LCD_WR_REG(0x2A);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x3F);

	LCD_WR_REG(0x2B);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0xE0);
	delay_ms(120);
	LCD_WR_REG(0x29);
	LCD_WR_REG(0x002c);

	LCD_SetParam();//����LCD����
	LCD_LED(1);//��������
	LCD_Clear(WHITE);
}


//******************************************************************
//��������  LCD_SetWindows
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ������ʾ����
//���������(xStar,yStar):�������Ͻ���ʼ����
//	 	   	(xEnd,yEnd):�������½ǽ�������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{	
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(xStar>>8);
	LCD_WR_DATA(0x00FF&xStar);		
	LCD_WR_DATA(xEnd>>8);
	LCD_WR_DATA(0x00FF&xEnd);

	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(yStar>>8);
	LCD_WR_DATA(0x00FF&yStar);		
	LCD_WR_DATA(yEnd>>8);
	LCD_WR_DATA(0x00FF&yEnd);	

	LCD_WriteRAM_Prepare();	//��ʼд��GRAM				
}   

//******************************************************************
//��������  LCD_SetCursor
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ���ù��λ��
//���������Xpos:������
//			Ypos:������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	  	    			
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(Xpos>>8);
	LCD_WR_DATA(0x00FF&Xpos);		
	LCD_WR_DATA((Xpos+1)>>8);
	LCD_WR_DATA(0x00FF&(Xpos+1));

	
	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(Ypos>>8);
	LCD_WR_DATA(0x00FF&Ypos);		
	LCD_WR_DATA((Ypos+1)>>8);
	LCD_WR_DATA(0x00FF&(Ypos+1));

	LCD_WriteRAM_Prepare();	//��ʼд��GRAM	
} 

//******************************************************************
//��������  LCD_SetParam
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ����LCD������������к�����ģʽ�л�
//�����������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void LCD_SetParam(void)
{ 
	lcddev.wramcmd=0x2C;
#if USE_HORIZONTAL==1
	lcddev.dir=1;//����
	lcddev.width=480;
	lcddev.height=320;
	lcddev.setxcmd=0x2A;
	lcddev.setycmd=0x2B;			
	LCD_WriteReg(0x36,0x28);

#else//����
	lcddev.dir=0;//����				 	 		
	lcddev.width=320;
	lcddev.height=480;
	lcddev.setxcmd=0x2A;
	lcddev.setycmd=0x2B;	
	//1 LCD_WriteReg(0x36,0x0A);
	//2 LCD_WriteReg(0x36,0x8A);
	LCD_WriteReg(0x36,0x8A);
#endif
}	 
