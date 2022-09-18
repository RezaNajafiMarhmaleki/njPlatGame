#pragma once

#include "SDL.h"
#include "SDL_TTF.h"

class TextManager
{
public:
	static TextManager* Instance()
{
	if(s_pInstance == 0)
	{
		s_pInstance = new TextManager();
		return s_pInstance;
	}
	return s_pInstance;
}	

void drawText( SDL_Renderer* gRenderer,std::string string,int size,int x, int y,
	int r=0,int g=0,int b=0, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
std::string intToString(int i);
void init(void);

private:
	TextManager(void);
	~TextManager(void);
	static TextManager* s_pInstance ;	

};

