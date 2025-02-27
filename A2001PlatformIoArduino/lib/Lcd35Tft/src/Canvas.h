/*
 * Canvas.h
 *
 *  Created on: 27 ���. 2018 �.
 *      Author: banz
 */

#ifndef CANVAS_H_
#define CANVAS_H_

#include <stdint.h>
#include "Color.h"
class GObj;

class Canvas {
	friend GObj;
	uint16_t __X;
	uint16_t __Y;
	uint16_t _Sz_x;
	uint16_t _Sz_y;

public:
	Canvas(uint16_t x,uint16_t y, uint16_t sz_x,uint16_t sz_y);
	Canvas(const Canvas& obj);
	virtual ~Canvas();

	void DrawPoint(uint16_t x,uint16_t y,const Color& color);
	//void DrawBmp16(uint16_t x,uint16_t y,const uint16_t *p);

	void SetWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
	void DrawWindowPoint(const Color& color);
	void DrawWindowPoint(const uint16_t color);

	uint16_t Width() {return _Sz_x;};
	uint16_t Height() {return _Sz_y;};

	uint16_t X() {return __X;};
	uint16_t Y() {return __Y;};

};

#endif /* CANVAS_H_ */
