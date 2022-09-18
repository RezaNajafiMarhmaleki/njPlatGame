#include "stdafx.h"
#include "Game.h"
#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"
#include "InputHandler.h"
#include "Level.h"
#include "TextManager.h"

Game* Game::s_pInstance ( 0);

Game::Game(void) 
{
}


Game::~Game(void)
{
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags){
	 
	if(flags==0)
		 flags=SDL_WINDOW_SHOWN  | SDL_WINDOW_OPENGL ;//| SDL_WINDOW_FULLSCREEN_DESKTOP;

	if(xpos==0)
		xpos = SDL_WINDOWPOS_UNDEFINED;
	if(ypos==0)
		ypos = SDL_WINDOWPOS_UNDEFINED;

	// attempt to initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		// init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos,width, height, flags);
		if(m_pWindow != 0) // window init success
		{
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if( !( IMG_Init( imgFlags ) & imgFlags ) )
			{
				printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
				return false; // renderer init fail
			}

			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if(m_pRenderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer,255,255,255,255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}

	TextManager::Instance()->init();

	std::cout << "init success\n";


	m_bRunning = true; // everything inited successfully,	start the main loop


	//tiles
		TextureManager::Instance()->load("../media/1.png" ,"tile1", m_pRenderer);
		TextureManager::Instance()->load("../media/2.png" ,"tile2", m_pRenderer);
		TextureManager::Instance()->load("../media/3.png" ,"tile3", m_pRenderer);
		TextureManager::Instance()->load("../media/-2.png" ,"tile-2", m_pRenderer);
		TextureManager::Instance()->load("../media/-3.png" ,"tile-3", m_pRenderer);
		TextureManager::Instance()->load("../media/-4.png" ,"tile-4", m_pRenderer);
		TextureManager::Instance()->load("../media/-5.png" ,"tile-5", m_pRenderer);
		TextureManager::Instance()->load("../media/70.png" ,"tile70", m_pRenderer);
		TextureManager::Instance()->load("../media/71.png" ,"tile71", m_pRenderer);
		TextureManager::Instance()->load("../media/99.png" ,"tile99", m_pRenderer);
		TextureManager::Instance()->load("../media/GameOver.png" ,"GameOver", m_pRenderer);
		TextureManager::Instance()->load("../media/YouWin.png" ,"YouWin", m_pRenderer);
		TextureManager::Instance()->load("../media/Slug.png" ,"Slug", m_pRenderer);
		
	// Player 
	TextureManager::Instance()->load("../media/player.png" ,"player", m_pRenderer);
	m_gameObjects.push_back(new Player(new LoaderParams(0,100,30,40,"player",6,0)));

	//Enemy
	TextureManager::Instance()->load("../media/Worm.png" ,"Worm", m_pRenderer);
	m_gameObjects.push_back(new Enemy(new LoaderParams(150,5,32,14,"Worm",12,0.5)));
	m_gameObjects.push_back(new Enemy(new LoaderParams(1200,5,32,34,"Slug",8,0.9)));
	m_gameObjects.push_back(new Enemy(new LoaderParams(500,5,32,14,"Worm",12,0.5)));
	m_gameObjects.push_back(new Enemy(new LoaderParams(800,5,32,34,"Slug",8,0.9)));
	m_gameObjects.push_back(new Enemy(new LoaderParams(1000,5,32,14,"Worm",12,0.5)));

	//level
	Level::Instance()->width = SCREEN_WIDTH;
	Level::Instance()->height = SCREEN_HEIGHT;
	Level::Instance()->viewportx = 0;
	Level::Instance()->viewporty = 0;

	return true;	
}

void Game::render(){
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color

	Level::Instance()->render();

	for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}


	Player* player = (Player*) m_gameObjects[0];

	TextureManager::Instance()->draw("tile99",32,0,32, 32, Game::Instance()->getRenderer());
	std::string tstring = TextManager::Instance()->intToString(player->getLife());
	TextManager::Instance()->drawText(Game::Instance()->getRenderer(),tstring,14,64,16);

	tstring = "Score: ";
	tstring += TextManager::Instance()->intToString(player->getScore());
	TextManager::Instance()->drawText(Game::Instance()->getRenderer(),tstring,14,128,16);

	SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update(){
	for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
		if(i>0){
			if(m_gameObjects[0]->checkCollision(m_gameObjects[i]))
			{	
				Player* player = (Player*) m_gameObjects[0];
				player->setLife(player->getLife()-10);
			}
		}

	}
}

void Game::handleEvents(){
	if(	TheInputHandler::Instance()->isQuit()
		|| TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
			m_bRunning = false;
}
void Game::clean(){
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	IMG_Quit();
	SDL_Quit();
}

void Game::GameOver(){
	TextureManager::Instance()->draw("GameOver",
		SCREEN_WIDTH/2,SCREEN_HEIGHT/2,189, 30, 	
		Game::Instance()->getRenderer());
	SDL_RenderPresent(m_pRenderer); // draw to the screen
	SDL_Delay(3000);
	m_bRunning = false;
}
void Game::GameWin(){
	TextureManager::Instance()->draw("YouWin",
		SCREEN_WIDTH/2,SCREEN_HEIGHT/2,189, 30, 	
		Game::Instance()->getRenderer());
	SDL_RenderPresent(m_pRenderer); // draw to the screen
	SDL_Delay(3000);
	m_bRunning = false;
}