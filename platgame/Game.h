#include "SDL.h"
#include "SDLGameObject.h"
#include <vector>
using std::vector;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FPS = 60;
const float DELAY_TIME = 1000.0f / FPS;

class Game
{
public:

	~Game(void);
	// simply set the running variable to true
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags=0);
	void render();
	void update();
	void handleEvents();
	void clean();
	void Delay(){// add the delay
		Uint32 frameTime = SDL_GetTicks() - frameStart;
		if(frameTime< DELAY_TIME)
		{
			SDL_Delay((int)(DELAY_TIME - frameTime));
		}
	} 

	void setframeStart(){ frameStart= SDL_GetTicks();}
	// a function to access the private running variable
	bool running() { return m_bRunning; }
	static Game* Instance()
	{
		if(s_pInstance == 0)
		{
		s_pInstance = new Game();
		return s_pInstance;
		}
		return s_pInstance;
	}
	SDL_Renderer* getRenderer() const { return m_pRenderer; }
	SDL_Window* getpWindow() const { return m_pWindow; }
	void GameOver();
	void GameWin();
private:
	
	Game(void);
	Uint32 frameStart;
		bool m_bRunning;
		SDL_Window* m_pWindow;
		SDL_Renderer* m_pRenderer;
		std::vector<SDLGameObject*> m_gameObjects;
		static Game* s_pInstance;
};

typedef Game TheGame;