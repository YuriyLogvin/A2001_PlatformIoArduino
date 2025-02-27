/*
 * FontTimes120.h
 *
 *  Created on: 24 ρεπο. 2018 π.
 *      Author: banz
 */

#ifndef FONTS_FONTTIMES120_H_
#define FONTS_FONTTIMES120_H_

#include "FontEmk.h"

class FontTimes120 : public Font  {
public:
	FontTimes120();
	virtual ~FontTimes120();
	virtual uint16_t DrawChar(char ch, Canvas& canv, uint16_t x, uint16_t y);

};

#endif /* FONTS_FONTTIMES120_H_ */
