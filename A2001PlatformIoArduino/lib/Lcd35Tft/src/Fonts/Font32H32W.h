/*
 * Font32H32W.h
 *
 *  Created on: 13 ρεπο. 2018 π.
 *      Author: banz
 */

#ifndef FONTS_FONT32H32W_H_
#define FONTS_FONT32H32W_H_

#include "FontEmk.h"

class Font32H32W : public Font {
public:
	Font32H32W();
	virtual ~Font32H32W();

	virtual uint16_t DrawChar(char ch, Canvas& canv, uint16_t x, uint16_t y);
};

#endif /* FONTS_FONT32H32W_H_ */
