/*
 * GObjKeyValue.h
 *
 *  Created on: 3 זמגע. 2018 נ.
 *      Author: banz
 */

#ifndef GOBJS_GOBJKEYVALUE_H_
#define GOBJS_GOBJKEYVALUE_H_

#include "GObj.h"
#include <string>
#include "FontEmk.h"
#include "EmkUiVars.h"

class GObjKeyValue : public GObj
{
	std::string _Key;
	std::string _Value;
	Font* _FontKey;
	Font* _FontValue;
	bool _KeyDrawed;
	bool _ValueDrawed;
	uint8_t _KeyDrawedLength;
	uint8_t _ValueDrawedLength;
	TextAlignes _KeyAlign;
	TextAlignes _ValueAlign;
public:
	GObjKeyValue(const Canvas& canvas, Font* fontKey, Font* fontValue, const char* key, const char* val, GObj* parentObj = 0);
	virtual ~GObjKeyValue();

	virtual void Redraw();

	virtual void ResetDrawState();

	void SetKey(const char* val);
	void SetValue(const char* val);

	void SetKeyAlign(const TextAlignes val);
	void SetValueAlign(const TextAlignes val);

};

#endif /* GOBJS_GOBJKEYVALUE_H_ */
