/*
 * GObjMngr.cpp
 *
 *  Created on: 31 ���. 2018 �.
 *      Author: banz
 */

#include "GObjMngr.h"

GObjMngr::GObjMngr() {
	// TODO Auto-generated constructor stub

}

GObjMngr::~GObjMngr() {
	// TODO Auto-generated destructor stub
}

void GObjMngr::Add(GObj* gObj)
{
	_Objs.push_back(gObj);
}

void GObjMngr::Remove(GObj* gObj)
{
	_Objs.remove(gObj);
}

void GObjMngr::RemoveAll()
{
	_Objs.clear();
}

void GObjMngr::Redraw()
{
	std::list<GObj*>::iterator it;
	for (it = _Objs.begin(); it != _Objs.end();it++)
	{
		(*it)->Redraw();
	}

}

