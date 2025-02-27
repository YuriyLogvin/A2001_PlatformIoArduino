/*
 * GObj.cpp
 *
 *  Created on: 27 ���. 2018 �.
 *      Author: banz
 */

#include "GObj.h"

GObj::GObj(const Canvas& canvas, GObj* parentObj)
	: _Canvas(canvas)
{
	_ParentObj = parentObj;
	if (_ParentObj)
	{
		_Canvas.__X += _ParentObj->_Canvas.X();
		_Canvas.__Y += _ParentObj->_Canvas.Y();
	}
}

/*GObj::GObj(const GObj& obj)
	: _Canvas(obj._Canvas)
{

}*/

GObj::~GObj() {
	// TODO Auto-generated destructor stub
}

void GObj::Redraw()
{
	if (_ParentObj)
		_ParentObj->Redraw();
}

void GObj::RedrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	if (_ParentObj)
		_ParentObj->RedrawRect(_Canvas.X() - _ParentObj->_Canvas.X() + x1, _Canvas.Y() - _ParentObj->_Canvas.Y() + y1, _Canvas.X() - _ParentObj->_Canvas.X() + x2, _Canvas.Y() - _ParentObj->_Canvas.Y() + y2);
}

