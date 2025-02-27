/*
 * GObjText.h
 *
 *  Created on: 12 ρεπο. 2018 π.
 *      Author: banz
 */

#ifndef GOBJS_GOBJTEXT_H_
#define GOBJS_GOBJTEXT_H_

#include "GObj.h"
#include <string>
#include "FontEmk.h"
#include "EmkUiVars.h"

class GObjText : public GObj
{
	std::string _Value;
	Font* _Font;
	bool _ValueDrawed;
	TextAlignes _Align;

public:
	GObjText(const Canvas& canvas, Font* font, const char* val, GObj* parentObj = 0);
	virtual ~GObjText();

	virtual void Redraw();
	virtual void ResetDrawState();

	void SetText(const char* val);

	void SetAlign(const TextAlignes val);

	void SetColor(const Color& color);

};

#endif /* GOBJS_GOBJTEXT_H_ */
