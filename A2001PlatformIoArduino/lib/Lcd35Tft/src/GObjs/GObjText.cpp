/*
 * GObjText.cpp
 *
 *  Created on: 12 ρεπο. 2018 π.
 *      Author: banz
 */

#include <GObjs/GObjText.h>

GObjText::GObjText(const Canvas& canvas, Font* font, const char* val, GObj* parentObj) :
	GObj(canvas, parentObj)
{
	_Value = val;
	_Font = font;
	_ValueDrawed = false;
	_Align = TextAlignes::Left;
}

GObjText::~GObjText() {
	if (_Font)
		delete _Font;
	_Font = 0;
}

void GObjText::SetText(const char* val)
{
	if (_Value == val)
		return;
	_ValueDrawed = false;
	_Value = val;
}

void GObjText::ResetDrawState()
{
	_ValueDrawed = false;
}

void GObjText::SetColor(const Color& color)
{
	_Font->SetFontColor(color);
}

void GObjText::Redraw()
{
	if (_ValueDrawed)
		return;

	GObj::Redraw();

	_ValueDrawed = true;
	std::string::const_iterator cit;
	uint16_t x = 0;

	uint16_t textLen = 0;
	for (cit = _Value.begin(); cit != _Value.end(); cit++)
	{
		textLen += _Font->CharWidth(*cit);
	}

	switch (_Align)
	{
	case TextAlignes::Right:
		x = _Canvas.Width() - textLen - _Canvas.Width() / 0x10;
		if (x > _Canvas.Width())
			x = 0;
		break;
	case TextAlignes::Center:
		x = (_Canvas.Width() - textLen) / 2;
		if (x > _Canvas.Width())
			x = 0;
		break;
	default:
		break;
	}

	GObj::RedrawRect(0, 0, _Canvas.Width(), _Canvas.Height());

	for (cit = _Value.begin(); cit != _Value.end(); cit++)
	{
		uint16_t dx = _Font->DrawChar(*cit, _Canvas, x, 0);
		//x += _Font->Width();
		x += dx;
	}
}

void GObjText::SetAlign(const TextAlignes val)
{
	_Align = val;
}

