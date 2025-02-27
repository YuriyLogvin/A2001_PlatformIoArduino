/*
 * FontVenator45.h
 *
 *  Created on: 2 груд. 2018 р.
 *      Author: banz
 */
#ifndef FONTS_FONTVenator45_H_
#define FONTS_FONTVenator45_H_

#include "FontEmk.h"

class FontVenator45 : public Font {
public:
	FontVenator45();
	virtual ~FontVenator45();
	virtual uint16_t DrawChar(char ch, Canvas& canv, uint16_t x, uint16_t y);
	virtual uint16_t CharWidth(char ch);
};

#endif
