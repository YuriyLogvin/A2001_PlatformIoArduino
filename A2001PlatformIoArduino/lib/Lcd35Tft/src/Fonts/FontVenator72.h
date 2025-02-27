/*
 * FontVenator80.h
 *
 *  Created on: 1 груд. 2018 р.
 *      Author: banz
 */
#ifndef FONTS_FONTVenator72_H_
#define FONTS_FONTVenator72_H_

#include "FontEmk.h"

class FontVenator72 : public Font {
public:
	FontVenator72();
	virtual ~FontVenator72();
	virtual uint16_t DrawChar(char ch, Canvas& canv, uint16_t x, uint16_t y);
	virtual uint16_t CharWidth(char ch);
};

#endif
