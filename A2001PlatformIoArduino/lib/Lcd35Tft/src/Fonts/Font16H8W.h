/*
 * Font16H8W.h
 *
 *  Created on: 13 ρεπο. 2018 π.
 *      Author: banz
 */

#ifndef FONTS_FONT16H8W_H_
#define FONTS_FONT16H8W_H_

#include "FontEmk.h"

class Font16H8W : public Font {
public:
	Font16H8W();
	virtual ~Font16H8W();

	virtual uint16_t DrawChar(char ch, Canvas& canv, uint16_t x, uint16_t y);

};

#endif /* FONTS_FONT16H8W_H_ */
