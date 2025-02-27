/*
 * FontTimes32.h
 *
 *  Created on: 14 ρεπο. 2018 π.
 *      Author: banz
 */
#ifndef FONTS_FONTTimes32_H_
#define FONTS_FONTTimes32_H_

#include "FontEmk.h"

class FontTimes32 : public Font {
public:
	FontTimes32();
	virtual ~FontTimes32();
	virtual uint16_t DrawChar(char ch, Canvas& canv, uint16_t x, uint16_t y);
	virtual uint16_t CharWidth(char ch);
};

#endif
