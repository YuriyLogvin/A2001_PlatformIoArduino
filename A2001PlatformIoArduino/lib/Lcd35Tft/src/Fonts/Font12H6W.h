/*
 * Font12H6W.h
 *
 *  Created on: 12 ρεπο. 2018 π.
 *      Author: banz
 */

#ifndef FONTS_FONT12H6W_H_
#define FONTS_FONT12H6W_H_

#include "FontEmk.h"

class Font12H6W : public Font {
public:
	Font12H6W();
	virtual ~Font12H6W();

	virtual uint16_t DrawChar(char ch, Canvas& canv, uint16_t x, uint16_t y);

};

#endif /* FONTS_FONT12H6W_H_ */
