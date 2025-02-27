/*
 * FontVenator24.h
 *
 *  Created on: 8 ����. 2018 �.
 *      Author: banz
 */
#ifndef FONTS_FONTVenator24_H_
#define FONTS_FONTVenator24_H_

#include "FontEmk.h"

class FontVenator24 : public Font {
public:
	FontVenator24();
	virtual ~FontVenator24();
	virtual uint16_t DrawChar(char ch, Canvas& canv, uint16_t x, uint16_t y);
	virtual uint16_t CharWidth(char ch);
};

#endif
