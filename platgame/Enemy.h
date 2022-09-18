#pragma once
#include "stdafx.h"
#include "SDLGameObject.h"
class Enemy: public SDLGameObject
{
public:
	Enemy(const LoaderParams* pParams);
	virtual  void draw();
	virtual void update();
	virtual void clean();
	virtual void checkDirection();
  int getMinesLife(){return m_mineslife;}
private:
	int m_mineslife;
};

