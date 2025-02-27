/*
 * Color.h
 *
 *  Created on: 11 ����. 2018 �.
 *      Author: banz
 */

#ifndef COLOR_H_
#define COLOR_H_

#include "stdint.h"

class Color {
	uint8_t __R;
	uint8_t __G;
	uint8_t __B;
public:
	Color();
	Color(uint8_t r, uint8_t g, uint8_t b);
	Color(const Color&);
	~Color();

	uint8_t R() const;
	uint8_t G() const;
	uint8_t B() const;

	uint16_t RGB() const;


	static uint8_t MaxColorValue() {return 0x3f;};

	static Color White() {return Color(MaxColorValue(), MaxColorValue(), MaxColorValue());};
	static Color Black() {return Color(0, 0, 0);};
	static Color Red() {return Color(MaxColorValue(), 0, 0);};
	static Color Green() {return Color(0, MaxColorValue(), 0);};
	static Color Blue() {return Color(0, 0, MaxColorValue());};
};

#endif /* COLOR_H_ */
