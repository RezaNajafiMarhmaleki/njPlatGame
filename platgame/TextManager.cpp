#include "StdAfx.h"
#include "TextManager.h"
#include <string>
using namespace  std;

TextManager*  TextManager::s_pInstance(0);

TextManager::TextManager(void)
{	
}
void TextManager::init(void)
{	
	if( TTF_Init() == -1 )
	{
		std::cout << "SDL_ttf could not initialize! SDL_ttf Error: "<<  TTF_GetError() << "\n";
	}
	else
	{
		std::cout << "SDL TTF init success\n";

	}
				
}

TextManager::~TextManager(void)
{
	TTF_Quit();
}

// TTF_Init() must be called before using this function.
// Remember to call TTF_Quit() when done.
void TextManager::drawText(SDL_Renderer* gRenderer,std::string string,int size,int x, int y,
	int r,int g,int b,SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	
	TTF_Font* gFont = TTF_OpenFont("../media/arial.ttf", size);
	
	SDL_Color textColor = { 0, 0, 0 };

	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, string.c_str(), textColor );

	SDL_Texture* mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );

	int mWidth=0,mHeight=0;

	if( mTexture == NULL )
	{
		printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Get image dimensions
		mWidth = textSurface->w;
		mHeight = textSurface->h;
	}

	//Get rid of old surface
	SDL_FreeSurface( textSurface );

	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}


	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );

	SDL_DestroyTexture( mTexture );

	TTF_CloseFont(gFont);
}

std::string TextManager::intToString(int i)
{
std::string s = std::to_string((long double)i);
    return s;
}