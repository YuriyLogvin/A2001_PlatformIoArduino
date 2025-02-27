/*
 * FontEmk.cpp
 *
 *  Created on: 12 ρεπο. 2018 π.
 *      Author: banz
 */

#include <FontEmk.h>

Font::Font(uint8_t charWidth, uint8_t charHeight, const Color& fColor, const Color& bColor) {
	_CharBitMaskBits = charWidth;
	_FontColor = fColor;
	_BackColor = bColor;
	_CharHeight = charHeight;
}

Font::~Font() {
	// TODO Auto-generated destructor stub
}

uint16_t Font::DrawChar(char ch, Canvas& canv, uint16_t x, uint16_t y)
{
	return 0;
}

uint16_t Font::CharWidth(char ch)
{
	return 0;
}


void Font::_DrawChar(Canvas& canv, uint16_t x, uint16_t y, const uint8_t* charBitMaskArray)
{
    uint8_t temp;
    uint16_t pos;
    uint16_t bCount = _CharBitMaskBits / 8;
    bCount += (_CharBitMaskBits % 8) ? 1 : 0;

	canv.SetWindow(x, y, x+_CharBitMaskBits-1, y+_CharHeight-1);
	{
		for (pos = 0; pos < _CharBitMaskBits*_CharHeight; pos++)
		{
			uint16_t bPos = pos / 8;
			temp=charBitMaskArray[bPos];
			temp>>=(pos%8);

			if(temp&0x01)
				canv.DrawWindowPoint(_FontColor);
			else
				canv.DrawWindowPoint(_BackColor);
		}
	}
}

void Font::_DrawCharTransparent(Canvas& canv, uint16_t x, uint16_t y, const uint8_t* charBitMaskArray)
{
    uint8_t temp;
    uint16_t pos = 0, i, yF = 0;
    uint16_t bCount = _CharBitMaskBits / 8;
    bCount += (_CharBitMaskBits % 8) ? 1 : 0;

    if (x > canv.Width())
    	return;

    for (;(y < canv.Height()) && (yF < _CharHeight-1) ; y++, yF++)
	{
		for (i = x; i < x + _CharBitMaskBits; pos++, i++)
		{
			uint16_t bPos = pos / 8;
			temp=charBitMaskArray[bPos];
			temp>>=(pos%8);

			if(temp&0x01)
				canv.DrawPoint(i, y, _FontColor);
		}

	}

}

void Font::SetFontColor(const Color& color)
{
	_FontColor = color;
}

