/*
 * GObj.h
 *
 *  Created on: 27 лип. 2018 р.
 *      Author: banz
 */

#ifndef GOBJ_H_
#define GOBJ_H_

#include "Canvas.h"

class GObj {
protected:
	Canvas _Canvas;
	GObj* _ParentObj;
public:
	GObj(const Canvas& canvas, GObj* parentObj = 0);
	//GObj(const GObj& obj);
	virtual ~GObj();

	virtual void Redraw();
	virtual void RedrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
	virtual void ResetDrawState() = 0;

};

#endif /* GOBJ_H_ */
