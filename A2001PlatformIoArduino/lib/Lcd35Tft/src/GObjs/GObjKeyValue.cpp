/*
 * GObjKeyValue.cpp
 *
 *  Created on: 3 זמגע. 2018 נ.
 *      Author: banz
 */

#include <GObjs/GObjKeyValue.h>

GObjKeyValue::GObjKeyValue(const Canvas& canvas, Font* fontKey, Font* fontValue, const char* key, const char* val, GObj* parentObj) : GObj(canvas, parentObj)
{
	_Key = key;
	_Value = val;
	_FontKey = fontKey;
	_FontValue = fontValue;
	_KeyDrawed = false;
	_ValueDrawed = false;
	_KeyDrawedLength = 0;
	_ValueDrawedLength = 0;

	_KeyAlign = TextAlignes::Left;
	_ValueAlign = TextAlignes::Left;
}

GObjKeyValue::~GObjKeyValue()
{
	if (_FontKey)
		delete _FontKey;
	_FontKey = 0;

	if (_FontValue)
		delete _FontValue;
	_FontValue = 0;
}

void GObjKeyValue::SetKey(const char* key)
{
	if (_Key == key)
		return;
	_Key = key;
	_KeyDrawed = false;
}

void GObjKeyValue::SetValue(const char* val)
{
	if (_Value == val)
		return;
	_Value = val;
	_ValueDrawed = false;
}

void GObjKeyValue::ResetDrawState()
{
	_KeyDrawed = false;
	_ValueDrawed = false;
}

void GObjKeyValue::Redraw()
{
	//GObj::Redraw();

	std::string::const_iterator cit;
	uint16_t x = 0;
	uint16_t y = 0;
	if (!_KeyDrawed)
	{
		_KeyDrawed = true;
		x = 0;
		y = 0;
		if (_Canvas.Height() > _FontKey->Height())
			y = (_Canvas.Height() - _FontKey->Height()) / 2;

		uint16_t textLen = 0;
		uint8_t keyChars = 0;
		for (cit = _Key.begin(); cit != _Key.end(); cit++)
		{
			textLen += _FontKey->CharWidth(*cit);
			keyChars++;
		}

		if (keyChars != _KeyDrawedLength)
			GObj::RedrawRect(0, 0, _Canvas.Width() / 3, _Canvas.Height());

		switch (_KeyAlign)
		{
		case TextAlignes::Right:
			x = _Canvas.Width() / 3 - _Canvas.Width() / 0x10;
			if (x > textLen)
				x -= textLen;
			else
				x = 0;
			break;
		case TextAlignes::Center:
			x = (_Canvas.Width() / 3 - textLen) / 2;
			break;

		default:
			break;
		}

		for (cit = _Key.begin(); cit != _Key.end(); cit++)
		{
			GObj::RedrawRect(x, y, x + _FontKey->Width(), y + _FontKey->Height());
			uint16_t dx = _FontKey->DrawChar(*cit, _Canvas, x, y);
			x += dx;
		}

		_KeyDrawedLength = keyChars;
	}

	if (!_ValueDrawed)
	{
		_ValueDrawed = true;
		x = _Canvas.Width() / 3;
		y = 0;
		if (_Canvas.Height() > _FontValue->Height())
			y = (_Canvas.Height() - _FontValue->Height()) / 2;

		uint8_t valChars = 0;
		uint16_t textLen = 0;
		for (cit = _Value.begin(); cit != _Value.end(); cit++)
		{
			textLen += _FontKey->CharWidth(*cit);
			valChars++;
		}

		if (valChars != _ValueDrawedLength)
			GObj::RedrawRect(_Canvas.Width() / 3, 0, _Canvas.Width(), _Canvas.Height());

		switch (_ValueAlign)
		{
		case TextAlignes::Right:
			x = _Canvas.Width() - textLen - _Canvas.Width() / 0x10;
			if (x > _Canvas.Width())
				x = _Canvas.Width() / 3;
			break;
		case TextAlignes::Center:
			x = _Canvas.Width() / 3 + (_Canvas.Width() * 2 / 3 - textLen) / 2;
			break;
		default:
			break;
		}

		for (cit = _Value.begin(); cit != _Value.end(); cit++)
		{
			GObj::RedrawRect(x, y, x + _FontValue->Width(), y + _FontValue->Height());
			uint16_t dx = _FontValue->DrawChar(*cit, _Canvas, x, y);
			x += dx;
		}

		_ValueDrawedLength = valChars;
	}
}

void GObjKeyValue::SetKeyAlign(const TextAlignes val)
{
	_KeyAlign = val;
}

void GObjKeyValue::SetValueAlign(const TextAlignes val)
{
	_ValueAlign = val;
}
