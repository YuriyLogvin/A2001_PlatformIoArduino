/*
 * GObjPicStretched.cpp
 *
 *  Created on: 23 лист. 2018 р.
 *      Author: banz
 */

#include <GObjs/GObjPicStretched.h>
#include <vector>

GObjPicStretched::GObjPicStretched(const Canvas& canvas, const ImgHeaderPixel* img, uint16_t imgHeight, uint16_t imgWidth ) :
	GObj(canvas)
{
	_Img = img;
	_Height = imgHeight;
	_Width = imgWidth;
	_Drawed = false;
}

GObjPicStretched::~GObjPicStretched()
{
}

void GObjPicStretched::Redraw()
{
	if (_Drawed)
		return;
	GObj::Redraw();
	RedrawRect(0, 0, _Canvas.Width(), _Canvas.Height());
	_Drawed = true;
}


//mask = {1, 2, 3, 4, 5, 6};

//res = _ChangeBits(val, mask);
//std::next_permutation(mask.begin(), mask.end());


/*uint8_t GObjPicStretched::_ChangeBits(uint8_t val)
{
	uint8_t res = 0;

	for (uint16_t i = 0; i < _PermitationVector.size(); ++i)
	{
		res |= ((val & (1 << i)) >> i) << _PermitationVector[i];
	}

	if (res != 0)
		return res;
	else
		return 0;
}*/

volatile int xxxx = 0;

void GObjPicStretched::RedrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{

	GObj::RedrawRect(x1, y1, x2, y2);

	_Canvas.SetWindow(x1, y1, x2, y2);

	volatile const ImgHeaderPixel* img = 0;

	for (uint16_t y = y1; y < y2; y++)
	{

		for (uint16_t x = x1; x < x2; x++)
		{
			uint16_t yImg = y;
			if (_Height <= y)
				yImg = _Height - 1;
			uint16_t xImg = x;
			if (_Width <= x)
				xImg = _Width - 1;

			img = &_Img[yImg * _Width + xImg];

			Color col(img->R, img->G, img->B);

			_Canvas.DrawWindowPoint(col);
		}

		if (y > 200)
			xxxx++;
	}

}

