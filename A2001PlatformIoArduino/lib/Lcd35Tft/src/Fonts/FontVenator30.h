/*
 * FontVenator30.h
 *
 *  Created on: 2 груд. 2018 р.
 *      Author: banz
 */
#ifndef FONTS_FONTVenator30_H_
#define FONTS_FONTVenator30_H_

#include "FontEmk.h"

class FontVenator30 : public Font {
public:
	FontVenator30();
	virtual ~FontVenator30();
	virtual uint16_t DrawChar(char ch, Canvas& canv, uint16_t x, uint16_t y);
	virtual uint16_t CharWidth(char ch);
};

#endif
