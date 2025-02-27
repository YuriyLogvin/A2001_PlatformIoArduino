/*
 * FontTimes64.h
 *
 *  Created on: 24 ρεπο. 2018 π.
 *      Author: banz
 */

#ifndef FONTS_FONTTIMES64_H_
#define FONTS_FONTTIMES64_H_

#include "FontEmk.h"

class FontTimes64 : public Font {
public:
	FontTimes64();
	virtual ~FontTimes64();
	virtual uint16_t DrawChar(char ch, Canvas& canv, uint16_t x, uint16_t y);
};

#endif /* FONTS_FONTTIMES64_H_ */
