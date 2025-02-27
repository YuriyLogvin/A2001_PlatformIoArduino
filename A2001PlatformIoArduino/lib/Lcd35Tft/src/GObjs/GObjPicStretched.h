/*
 * GObjPicStretched.h
 *
 *  Created on: 23 лист. 2018 р.
 *      Author: banz
 */

#ifndef GOBJS_GOBJPICSTRETCHED_H_
#define GOBJS_GOBJPICSTRETCHED_H_

#include "GObj.h"
//#include <vector>

struct ImgHeaderPixel
{
	const uint8_t R;
	const uint8_t G;
	const uint8_t B;
};

class GObjPicStretched : public GObj
{
	const ImgHeaderPixel* _Img;
	uint16_t _Height;
	uint16_t _Width;
	bool _Drawed;

public:
	GObjPicStretched(const Canvas& canvas, const ImgHeaderPixel*, uint16_t imgHeight, uint16_t imgWidth );
	virtual ~GObjPicStretched();

	virtual void Redraw();
	virtual void RedrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
	virtual void ResetDrawState() {};

	void RedrawRRR() {_Drawed = false;};

	/*std::vector<uint8_t> _PermitationVector;
	uint8_t _ChangeBits(uint8_t val);
	void SetPermitationVector(const std::vector<uint8_t>& permitationVector)
	{
		_PermitationVector = permitationVector;
	};*/

};

#endif /* GOBJS_GOBJPICSTRETCHED_H_ */
