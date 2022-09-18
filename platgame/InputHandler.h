#include "SDL.h"
class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if(s_pInstance == 0)
		{
		s_pInstance = new InputHandler();
		}
		return s_pInstance;
	}
	bool isKeyDown(SDL_Scancode key);
	bool InputHandler::isQuit( );
	void clean();
private:
	InputHandler();
	~InputHandler() {}
	static InputHandler* s_pInstance;
};
typedef InputHandler TheInputHandler;