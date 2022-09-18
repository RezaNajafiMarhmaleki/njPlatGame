#pragma once

#include "Vector2D.h"

class Level
{

public:
	static Level* Instance()
	{
		if(s_pInstance == 0)
		{
		s_pInstance = new Level();
		}
		return s_pInstance;
	}
	
	int viewportx;
	int viewporty;
	int width;
	int height;
	void update();
	void render();
	int getlevelBrick(int x,int y,bool byviewport=false);
	void setlevelBrick(Vector2D v1,int value);
	void setlevel(int level){m_current_level=level;}
	int getlevel( ){return m_current_level;}
	bool ViewPort_Inc();
	bool ViewPort_Dec();
private:
	Level( ):viewportx(0),	   viewporty(0),width(0),height(0)
	   {}
	Level(int x,int y,int w,int h):
	  viewportx(x),	   viewporty(y),width(w),height(h)
	   {}
	~Level() {}
	int m_current_level;
static Level* s_pInstance;
};

