/*
 * GObjMngr.h
 *
 *  Created on: 31 ���. 2018 �.
 *      Author: banz
 */

#ifndef GOBJMNGR_H_
#define GOBJMNGR_H_

#include <list>

#include "GObj.h"

class GObjMngr {
	std::list<GObj*> _Objs;

public:
	GObjMngr();
	virtual ~GObjMngr();

	void Add(GObj* gObj);
	void Remove(GObj* gObj);
	void RemoveAll();

	void Redraw();
};

#endif /* GOBJMNGR_H_ */
