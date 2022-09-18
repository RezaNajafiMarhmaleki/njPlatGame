#include "StdAfx.h"
#include "InputHandler.h"

InputHandler* InputHandler::s_pInstance ( 0);

InputHandler::InputHandler(void)
{
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
	const Uint8 *m_keystates = SDL_GetKeyboardState(NULL);
	if(m_keystates != 0)
	{
		if(m_keystates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool InputHandler::isQuit( )
{
	SDL_Event event;
       while(SDL_PollEvent(&event)) {
            if(event.type==SDL_QUIT)
			return true;
	   }
	return false;
}
