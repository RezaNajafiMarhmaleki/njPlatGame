# njPlatGame
platgame with VC++ projects and opengl library

 
بازی platgame  ضمن استفاده از کتابخانه OpenGL  با زبان C++  و به صورت شی گرا پیاده سازی شده است. این بازی شبیه بازی ماریو می باشد و پلیر بازی یکسری مراحل را طی می کند و امتیاز کسب می کند و هنگام بازی نباید به  Enemy  برخورد کند.
این برنامه از توابع کتابخانه ای زیر استفاده می کند.
•	SDL2-2.0.3
•	SDL2_image-2.0.0
•	SDL2_mixer-2.0.0
•	SDL2_ttf-2.0.12
•	GLFiles (GLU)

عنوان کلاس های برنامه. 
•	 Enemy
•	Player
•	Game
•	GameObject
•	InputHandler
•	Level
•	LoaderParams
•	SDLGameObject
•	TextManager
•	TextureManager
•	Vector2D
کلاس دیاگرام بازی پلت به صورت زیر می باشد.
 
 
Object:
منظور از Object هر نوع شی اعم از بازیگر(Player)، دشمن(Enemy) می باشد.
کلاس Vector2D:
توسط این کلاس بردار x, y پیاده سازی شده است. این کلاس توابع زیر را انجام می دهد.
•	(x1,y1)+(x2,y2)	=>	x1+x2,y1+y2
•	(x1,y1)* scalar	=>	x1* scalar, y1* scalar
•	(x1,y1)-(x2,y2)	=>	x1-x2,y1-y2
•	(x1,y1)/ scalar	=>	x1/ scalar,y1/ scalar

 
#include<math.h>
class Vector2D
{
public:
	 
Vector2D(float x, float y): m_x(x), m_y(y) {}
float getX() { return m_x; }
float getY() { return m_y; }
void setX(float x) { m_x = x; }
void setY(float y) { m_y = y; }
float length() { return sqrt(m_x * m_x + m_y * m_y); }
Vector2D operator+(const Vector2D& v2) const
{return Vector2D(m_x + v2.m_x, m_y + v2.m_y);}

friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
{v1.m_x += v2.m_x;v1.m_y += v2.m_y;return v1;}

Vector2D operator*(float scalar)
{return Vector2D(m_x * scalar, m_y * scalar);}

Vector2D& operator*=(float scalar)
{m_x *= scalar;m_y *= scalar;return *this;}

Vector2D operator-(const Vector2D& v2) const
{return Vector2D(m_x - v2.m_x, m_y - v2.m_y);}

friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
{v1.m_x -= v2.m_x;v1.m_y -= v2.m_y;return v1;}

Vector2D operator/(float scalar)
{return Vector2D(m_x / scalar, m_y / scalar);}

Vector2D& operator/=(float scalar)
{m_x /= scalar;m_y /= scalar;return *this;}
void normalize()
{
float len = length();
if ( len > 0) // we never want to attempt to divide by 0
{
(*this) *= 1 / len;
}
}
private:
	float m_x;
	float m_y;
};




کلاس SDLGameObject:
وظیفه این کلاس رسم Object ها بر روی صفحه نمایش، بررسی وضعیت Object از تمام سمت ها و بررسی برخورد دو Object با همدیگر را بر عهده دارد.
#include "GameObject.h"
#include "Vector2D.h"
class SDLGameObject: public GameObject
{
public:
SDLGameObject(const LoaderParams* pParams);
virtual void draw();
virtual void update();
virtual void clean();
تابع زیر شی را از تمام جهات بررسی می کند. در صورتی که از هر سمتی دیوار و یا امتیاز باشد در خانه مذکور مقداری بالای 0 قرار می گیرد.
0	0	0
0	 
2
1	1	1


0	0	0
0	 
 


virtual void checkDirection();
تابع checkCollision دو شی را بررسی می کند و در صورتی که از هر طرف با شی برخورد کند مقدار true به تابع بر می گرداند.
 virtual bool checkCollision(SDLGameObject *cby   );

 protected:
مکان Object  بر روی بردار
Vector2D m_position;    
سرعت حرکت Object  
Vector2D m_velocity;
شتاب Object
Vector2D m_acceleration;
int m_width;
int m_height;
int m_currentRow;
int m_currentFrame;
int m_maxFrame;
std::string m_textureID;
مقدار پیش فرضm_velocity 
float m_speed;
وضعیت Object از تمام اطراف 
int m_direction[3][3];

Vector2D* m_directionPosition[3][3];
};



کلاس TextureManager:
این کلاس کلیه عملیات لود عکس و ترسیم عکس بر روی صفحه را بر عهده دارد.
#include "stdafx.h"
#include <map>
#include "SDL.h"
#include <SDL_image.h>

using std::map;

class TextureManager
{
public:
static TextureManager* Instance()
{
	if(s_pInstance == 0)
	{
		s_pInstance = new TextureManager();
		return s_pInstance;
	}
	return s_pInstance;
}	
~TextureManager(void);
تابع load عکسی را لود کرده و در لیست textureMap با نام id ذخیره می کند تا در طول برنامه از آن استفاده شود.
	bool load(std::string fileName,std::string id,SDL_Renderer* pRenderer);
تابع draw عکسی لود شده در لیست textureMap بر اساس بردار x,y بر روی صفحه ترسیم می کند.
	// draw
	void draw(std::string id, int x, int y, int width, int
		height, SDL_Renderer* pRenderer, SDL_RendererFlip flip =
		SDL_FLIP_NONE);
تابع drawFrame عکسی که دارای خاصیت فریم بندی می باشد را بر روی صفحه رسم می کند. فریم جاری را currentFrame تایین میکند.
	// drawframe
	void drawFrame(std::string id, int x, int y, int width, int
		height, int currentRow, int currentFrame, SDL_Renderer*
		pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	TextureManager(void);
لیست عکس های لود شده
	std::map<std::string, SDL_Texture*> m_textureMap;
	//static TextureManager* s_pInstance;
static TextureManager* s_pInstance ;	
};



کلاس TextManager:
این کلاس وظیفه ترسیم متن بر روی صفحه را بر عهده دارد. این کلاس از یک فونت پیش فرض arial.ttf که داخل پوشه media قرار داده شده است استفاده می کند.
کلاس InputHandler:
این کلاس ورودی صفحه کلید را بررسی می کند.
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
	bool isKeyDown(SDL_Scancode key);در صورتی که کلید مورد نظر فشار داده شده باشد مقدار درست را بر میگرداند
	bool InputHandler::isQuit( );درصورتی که کاربر برنامه را ببندد این تابع مفدار درست را بر می گرداند
	void clean();
private:
	InputHandler();
	~InputHandler() {}
	static InputHandler* s_pInstance;
};
typedef InputHandler TheInputHandler;
 
کلاس Level:
این کلاس شامل مراحل بازی می باشد. هر مرحله در داخل یک آرایه دو بعدی  ذخیره می شود. به عنوان مثال آرایه زیر را در نظر بگیرید.
int  level1[][15] ={
		{00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
		{00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
		{00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
		{00,00,00,00,-2,00,00,00,00,00,00,00,00,00,01},
		{00,00,00,00,-3,00,00,00,00,00,00,02,00,00,03},
		{00,00,00,00,-4,00,00,00,00,00,-5,01,00,00,00},
		{00,00,00,00,00,00,00,00,00,00,00,01,00,00,00},
		{00,00,00,00,00,00,00,00,00,00,-5,01,00,00,02},
		{00,00,00,00,00,00,00,00,00,00,71,03,00,00,01},
		{00,00,00,00,00,00,00,72,00,00,00,00,00,02,01},
		{00,00,00,00,00,00,00,00,00,02,00,00,00,01,01},
		{00,00,00,00,00,00,00,00,00,01,00,00,00,01,03},
		{00,00,00,00,00,02,00,00,00,01,00,00,00,01,00},
		{00,00,00,00,99,01,00,00,00,03,00,00,70,03,00},
		{00,00,00,00,00,03,00,00,00,00,00,00,00,00,02},
		{00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
		{00,00,00,00,00,00,00,00,00,00,00,00,00,00,01},
};

اعداد 01 در واقع   ، اعداد 02 ، اعداد 03   ، اعداد زیر صفر چمن ها و ابرها می باشند به عنوان مثال منفی 2، منفی 3 و منفی 4 ابرها و اعداد بالای 70 امتیاز ها را تشکیل می دهند.
 
هر یک از این شکل ها دارای اندازه 32x32 می باشد پس اندازه صفحه 640 در 480 می باشد. در صورتی که اندازه آرایه بیشتر از 640 باشد حالت scrolling انجام می شود.
 

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
scrolling به سمت راست
	bool ViewPort_Inc();
scrolling به سمت چپ

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



کلاس Enemy (دشمن) :
این کلاس از کلاس SDLGameObject ارث بری می کند. وظیفه این کلاس تغییر فریم های موضوع و حرکت اتوماتیک آن به سمت چپ و راست در صورتی که مانع در جلوی راه نباشد.
#include "StdAfx.h"
#include "Enemy.h"
#include "Game.h"
#include "Level.h"

Enemy::Enemy(const LoaderParams* pParams):
SDLGameObject(pParams)
	{}

void Enemy::draw()
{
SDLGameObject::draw();
}
 
 void  Enemy::update() 
{
	checkDirection();
شرط زیر در صورتی که Enemy در حال حرکت رو به سمت راست باشد اجرا می شود. شرط بعدی در صورتی که جلوی Enemy مانعی وجود نداشته باشد همچنان به راه خود ادامه می دهد در غیر این صورت Enemy حرکت نمی کند.
	if(m_velocity.getX()>=0)
		if((m_direction[1][2]<=0 || m_direction[1][2]>=70 )&& m_direction[2][2]>0){
			m_velocity.setX(m_speed);
			m_currentFrame = int(((SDL_GetTicks() / 100) % (m_maxFrame/2)))+(m_maxFrame/2);
		}else{
			m_velocity.setX(0);
		}
شرط زیر در صورتی که Enemy در حال حرکت رو به سمت چپ باشد اجرا می شود. شرط بعدی در صورتی که جلوی Enemy مانعی وجود نداشته باشد همچنان به راه خود ادامه می دهد در غیر این صورت Enemy حرکت نمی کند.

	If(m_velocity.getX()<=0)
		if((m_direction[1][0]<=0 || m_direction[1][0]>=70 )&& m_direction[2][0]>0){
			m_velocity.setX(-m_speed);
			m_currentFrame = int(((SDL_GetTicks() / 100) % (m_maxFrame/2)));
		}else{
			m_velocity.setX(0);
		}
در صورتی که Enemy زیر پایش خالی باشد رو به سمت پایین حرکت می کند.
	if(m_velocity.getY( ) <0)
		m_velocity.setY(m_velocity.getY()+1);

	if( m_acceleration.getY( ) <0)
		m_acceleration.setY(m_acceleration.getY()+1);

	if(m_direction[0][2]>0 &&( m_velocity.getY() <0 || m_acceleration.getY() <0)){
		m_velocity.setY(0);
		m_acceleration.setY(0) ;
	}

	if(m_direction[2][1]<=0 && m_velocity.getY( ) >=0 && m_acceleration.getY( ) >=0)
		m_velocity.setY(6);
	else if (m_velocity.getY()>0)
		m_velocity.setY(0);

	SDLGameObject::update();

}

  void Enemy::clean()
{
	SDLGameObject::clean();
}  
  void Enemy::checkDirection(){
	SDLGameObject::checkDirection();
  }

کلاس Player:
#include "StdAfx.h"
#include "Player.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Game.h"
#include "Level.h"

Player::Player(const LoaderParams* pParams):
SDLGameObject(pParams),m_score(0),m_life(100)
	{}

void Player::draw()
{
TextureManager::Instance()->drawFrame(m_textureID,
	(int) m_position.getX(),
	(int) m_position.getY(),m_width, m_height, 
	m_currentRow, m_currentFrame,
	Game::Instance()->getRenderer());
}
 void  Player::update() 
{
	checkDirection();

	m_velocity.setX(0);

در صورتی که Player میزان زندگی او کمتر یا مساوی صفر باشد یا در صورتی که Player از پایین صفحه خارج شود بازی Over می شود.
	if(m_position.getY()>=SCREEN_HEIGHT || m_life<=0)
		TheGame::Instance()->GameOver();
در صورتی که Player  به انتهای صفحه رسیده باشد مرحله را برده است.
	if(m_position.getX()+m_width>=SCREEN_WIDTH)
		TheGame::Instance()->GameWin();
	دستور زیر Scroll به سمت راست را  انجام می دهد
	if(m_position.getX()>= SCREEN_WIDTH-(SCREEN_WIDTH/3 ) || 
		(Level::Instance()->viewportx%32>0)  ){
		if(Level::Instance()->ViewPort_Inc())
			m_position.setX(m_position.getX()-1);
	}
	/*if(m_position.getX()<= (SCREEN_WIDTH/3 ) ){
		if(Level::Instance()->ViewPort_Dec())
			m_position.setX(m_position.getX()+32);
	}*/
چهار شرط زیر هر چهار طرف پلیر را بررسی می کند در صورتی که از هر طرفی امتیاز یا لایف باشد ابتدا شی امتیاز از بازی حذف و امتیاز پلیر افزایش می یابد.
	If(m_direction[1][0]>=70){
		Level::Instance()->setlevelBrick(*m_directionPosition[1][0],0);
		if(m_direction[1][0]==99)
			m_life+=9;
		else
			m_score+=8;
		m_direction[1][0] = 0;
	}
	if(m_direction[2][1]>=70){
		Level::Instance()->setlevelBrick(*m_directionPosition[2][1],0);
		if(m_direction[2][1]==99)
			m_life+=9;
		else
			m_score+=8;
		m_direction[2][1] = 0;
	}
	if(m_direction[0][1]>=70){
		Level::Instance()->setlevelBrick(*m_directionPosition[0][1],0);
		if(m_direction[0][1]==99)
			m_life+=9;
		else
			m_score+=8;
		m_direction[0][1] = 0;
	}
	if(m_direction[1][2]>=70){
		Level::Instance()->setlevelBrick(*m_directionPosition[1][2],0);
		if(m_direction[1][2]==99)
			m_life+=9;
		else
			m_score+=8;
		m_direction[1][2] = 0;
	}
در صورتی که کلید راست فشار داده شده باشد و جلوی راه پلیر خالی باشد پلیر به سمت جلو حرکت داده می شود.
	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	if(m_direction[1][2]<=0 && m_position.getX()+m_width<SCREEN_WIDTH){
		m_velocity.setX(2);
		m_currentFrame = int(((SDL_GetTicks() / 100) % 3));تغییر فریم پلیر
	}

	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	if(m_direction[1][0]<=0 && m_position.getX()>0){
		m_velocity.setX(-2);		
		m_currentFrame = int(((SDL_GetTicks() / 100) % 3))+3;
	}

	if(m_velocity.getY( ) <0)
		m_velocity.setY(m_velocity.getY()+1);

	if( m_acceleration.getY( ) <0)
		m_acceleration.setY(m_acceleration.getY()+1);

	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))پرش پلیر
		if(m_direction[2][1]>0 && m_direction[0][1]<=0){
			if(m_acceleration.getY( ) ==0){
				m_velocity.setY(-10);
				m_acceleration.setY(-3);
			}
		}

	if(m_direction[0][2]>0 &&( m_velocity.getY() <0 || m_acceleration.getY() <0)){
		m_velocity.setY(0);
		m_acceleration.setY(0) ;
	}

	if(m_direction[2][1]<=0 && m_velocity.getY( ) >=0 && m_acceleration.getY( ) >=0)
		m_velocity.setY(5);
	else if (m_velocity.getY()>0)
		m_velocity.setY(0);

	SDLGameObject::update();

}

  void Player::clean()
{
	SDLGameObject::clean();
} 
تابع زیر  را از جهات مختلف بررسی می کند و نتیجه را در یک آرایه 3 در 3 ذخیره می کند. شکل زیر را درنظر بگیرید.
  
 

معادل آن آرایه m_direction به صورت زیر می باشد

0	0	0
70	0	2
1	1	1

 
 void Player::checkDirection(){
	 
	 for(int i=0;i<3;i++)
		 for(int j=0;j<3;j++)
			if(m_directionPosition[i][j]!=0)
				delete m_directionPosition[i][j];

	//check left - middel
	float _x=m_position.getX()/32;
	float _y=(m_position.getY()+m_height/2)/32;

	int b = Level::Instance()->getlevelBrick((int)_x,(int)_y,true);
	m_direction[1][0]  = b>0?b:0;
	m_directionPosition[1][0] = new Vector2D(_x,_y);

	 //check left - top
	 _x=m_position.getX()/32;
	 _y=(m_position.getY())/32;

	b = Level::Instance()->getlevelBrick((int)_x,(int)_y,true);
	m_direction[0][0]  = b>0?b:0;
	m_directionPosition[0][0] = new Vector2D(_x,_y);

	 //check left - bottom
	  _x=m_position.getX()/32;
	  _y=(m_position.getY()+m_height)/32;

	b = Level::Instance()->getlevelBrick((int)_x,(int)_y,true);
	m_direction[2][0]  = b>0?b:0;
	m_directionPosition[2][0] = new Vector2D(_x,_y);

	 //check top
	  _x=(m_position.getX()+m_width/2)/32;
	  _y=(m_position.getY())/32;

	b = Level::Instance()->getlevelBrick((int)_x,(int)_y,true);
	m_direction[0][1]  = b>0?b:0;
	m_directionPosition[0][1] = new Vector2D(_x,_y);


	 //check bottom
	  _x=(m_position.getX()+m_width/2)/32;
	  _y=(m_position.getY()+m_height)/32;

	b = Level::Instance()->getlevelBrick((int)_x,(int)_y,true);
	m_direction[2][1]  = b>0?b:0;
	m_directionPosition[2][1] = new Vector2D(_x,_y);


	//check right - middel
	_x=(m_position.getX()+m_width)/32;
	_y=(m_position.getY()+m_height/2)/32;

	b = Level::Instance()->getlevelBrick((int)_x,(int)_y,true);
	m_direction[1][2]  = b>0?b:0;
	m_directionPosition[1][2] = new Vector2D(_x,_y);

	 //check right - top
	 _x=(m_position.getX()+m_width)/32;
	 _y=(m_position.getY())/32;

	b = Level::Instance()->getlevelBrick((int)_x,(int)_y,true);
	m_direction[0][2]  = b>0?b:0;
	m_directionPosition[0][2] = new Vector2D(_x,_y);

	 //check right - bottom
	  _x=(m_position.getX()+m_width)/32;
	  _y=(m_position.getY()+m_height)/32;

	b = Level::Instance()->getlevelBrick((int)_x,(int)_y,true);
	m_direction[2][2]  = b>0?b:0;
	m_directionPosition[2][2] = new Vector2D(_x,_y);

	 //check center - center
	  _x=(m_position.getX()+m_width/2)/32;
	  _y=(m_position.getY()+m_height/2)/32;

	b = Level::Instance()->getlevelBrick((int)_x,(int)_y,true);
	m_direction[1][1]  = b>0?b:0;
	m_directionPosition[1][1] = new Vector2D(_x,_y);
  }

کلاس Game:
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

LoaderParams(0,100,30,40,"player",6,0) پارامتر  اول و دوم مربوط به مکان Player ، پارامتر سوم و چهارم ارتفاع و عرض Player، پارامتر ششم نام Texture لود شده و پارامتر هفتم تعداد فریم و پارامتر هشتم سرعت Player می باشد.

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
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw 

	Level::Instance()->render();

	for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}


	Player* player = (Player*) m_gameObjects[0];
ترسیم اطلاعات مربوط به میزان امتیاز و میزان زندگی Player بر روی صفحه نمایش.
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
بررسی برخورد Player با Enemy و در صورت برخورد میزان لایف(زندگی) پلیر کاهش پیدا می کند.
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
			m_bRunning = false;پایان بازی
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
	m_bRunning = false; پایان بازی
}
void Game::GameWin(){
	TextureManager::Instance()->draw("YouWin",
		SCREEN_WIDTH/2,SCREEN_HEIGHT/2,189, 30, 	
		Game::Instance()->getRenderer());
	SDL_RenderPresent(m_pRenderer); // draw to the screen
	SDL_Delay(3000);
	m_bRunning = false;
}
 
شروع برنامه:
#include "stdafx.h"
#include "Game.h"
int main( int argc, char* args[] )
{
	TheGame::Instance()->init("Plat Game",0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	
	while(TheGame::Instance()->running()){
		
		TheGame::Instance()->setframeStart();

		TheGame::Instance()->handleEvents();

		TheGame::Instance()->update();

		TheGame::Instance()->render();

		TheGame::Instance()->Delay();
		
	}

	TheGame::Instance()->clean();
	return 0;
}



