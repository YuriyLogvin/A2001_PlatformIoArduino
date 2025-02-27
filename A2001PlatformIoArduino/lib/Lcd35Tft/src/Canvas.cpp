/*
 * Canvas.cpp
 *
 *  Created on: 27 ���. 2018 �.
 *      Author: banz
 */

#include "Canvas.h"
#include "Gui.h"
#include "lcd.h"

Canvas::Canvas(uint16_t x,uint16_t y, uint16_t sz_x,uint16_t sz_y) {
	// TODO Auto-generated constructor stub
	__X = x;
	__Y = y;
	_Sz_x = sz_x;
	_Sz_y = sz_y;

}

Canvas::Canvas(const Canvas& obj)
{
	__X = obj.__X;
	__Y = obj.__Y;
	_Sz_x = obj._Sz_x;
	_Sz_y = obj._Sz_y;
}

Canvas::~Canvas() {
	// TODO Auto-generated destructor stub
}

void Canvas::DrawPoint(uint16_t x,uint16_t y,const Color& color)
{
	if (x > _Sz_x)
		return;
	if (y > _Sz_y)
		return;
	Gui::DrawPoint(__X + x, __Y + y, color);
}

void Canvas::SetWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	LCD_SetWindows(__X+x1, __Y+y1, __X+x2, __Y+y2);
}

void Canvas::DrawWindowPoint(const Color& color)
{
	//LCD_DrawPoint_16Bit(color.RGB());
	LCD_DrawPoint_RGB(color.R(), color.G(), color.B());
}

void Canvas::DrawWindowPoint(const uint16_t color)
{
	LCD_DrawPoint_16Bit(color);
}







/*void Canvas::DrawBmp16(uint16_t x,uint16_t y,const uint16_t *p)
{
	Gui::DrawBmp16(x, y, p);
}*/
