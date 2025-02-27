/*
 * Color.cpp
 *
 *  Created on: 11 ����. 2018 �.
 *      Author: banz
 */

#include "Color.h"

Color::Color() {
	__R = 0;
	__G = 0;
	__B = 0;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b)
{
	__R = r;
	__G = g;
	__B = b;
}

Color::Color(const Color& val)
{
	__R = val.__R;
	__G = val.__G;
	__B = val.__B;
}

Color::~Color() {
}


uint8_t Color::R() const
{
	return __R;
}

uint8_t Color::G() const
{
	return __G;
}

uint8_t Color::B() const
{
	return __B;
}

uint16_t Color::RGB() const
{
	if (__R==__G && __G==__B)
		return ((__R << 10) & 0xF800) | ((__G << 5) & 0x7C0) | ((__B >> 1) & 0x1F); //����� ��� 1 ������ ����� ����
	return ((__R << 10) & 0xF800) | ((__G << 5) & 0x7E0) | ((__B >> 1) & 0x1F);
	//return ((_R << 10) & 0xF800) | ((_G << 5) & 0x7E0) | ((_B >> 1) & 0x1F) | 0x20;
	//return ((_R << 10) & 0xF800) | ((_G << 5) & 0x7C0) | ((_B >> 1) & 0x1F);
}

