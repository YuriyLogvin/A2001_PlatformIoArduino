/*
 * FontEmk.h
 *
 *  Created on: 12 ρεπο. 2018 π.
 *      Author: banz
 */

#ifndef FONTEMK_H_
#define FONTEMK_H_

#include "Canvas.h"


class Font {
public:
	virtual ~Font();

	virtual uint16_t DrawChar(char ch, Canvas& canv, uint16_t x, uint16_t y);
	virtual uint16_t CharWidth(char ch);

	uint8_t Width() {return _CharBitMaskBits;};
	uint8_t Height() {return _CharHeight;};

	void SetFontColor(const Color& color);


protected:
	Font(uint8_t charWidth, uint8_t charHeight, const Color& fColor, const Color& bColor);

	uint8_t _CharBitMaskBits;
	uint8_t _CharHeight;
	Color _FontColor;
	Color _BackColor;
	void _DrawChar(Canvas& canv, uint16_t x, uint16_t y, const uint8_t* charBitMaskArray);
	void _DrawCharTransparent(Canvas& canv, uint16_t x, uint16_t y, const uint8_t* charBitMaskArray);
};

#endif /* FONTEMK_H_ */
