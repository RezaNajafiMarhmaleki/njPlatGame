#include "StdAfx.h"
#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Level.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) :
	GameObject(pParams), m_position((float)pParams->getX(),(float) pParams->getY()),
	m_velocity(0,0),m_acceleration(0,0),m_speed(pParams->getSpeed()),m_currentFrame(pParams->getcurrentFrame())
{
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = 1;
	m_maxFrame =  pParams->getmaxFrame();
	 for(int i=0;i<3;i++)
		 for(int j=0;j<3;j++)
				m_directionPosition[i][j] = 0;
}

void SDLGameObject::draw()
{
TextureManager::Instance()->drawFrame(m_textureID,
	(int) m_position.getX()- Level::Instance()->viewportx,
	(int) m_position.getY()- Level::Instance()->viewporty,m_width, m_height, 
	m_currentRow, m_currentFrame,
	Game::Instance()->getRenderer());
}
void SDLGameObject::update()
{
	m_velocity += m_acceleration;
	m_position += m_velocity;
}

void SDLGameObject::clean()
{
}

 void SDLGameObject::checkDirection(){
	 
	 for(int i=0;i<3;i++)
		 for(int j=0;j<3;j++)
			if(m_directionPosition[i][j]!=0)
				delete m_directionPosition[i][j];

	//check left - middel
	float _x=m_position.getX()/32;
	float _y=(m_position.getY()+m_height/2)/32;

	int b = Level::Instance()->getlevelBrick((int)_x,(int)_y);
	m_direction[1][0]  = b>0?b:0;
	m_directionPosition[1][0] = new Vector2D(_x,_y);

	 //check left - top
	 _x=m_position.getX()/32;
	 _y=(m_position.getY())/32;

	b = Level::Instance()->getlevelBrick((int)_x,(int)_y);
	m_direction[0][0]  = b>0?b:0;
	m_directionPosition[0][0] = new Vector2D(_x,_y);

	 //check left - bottom
	  _x=m_position.getX()/32;
	  _y=(m_position.getY()+m_height)/32;

	b = Level::Instance()->getlevelBrick((int)_x,(int)_y);
	m_direction[2][0]  = b>0?b:0;
	m_directionPosition[2][0] = new Vector2D(_x,_y);

	 //check top
	  _x=(m_position.getX()+m_width/2)/32;
	  _y=(m_position.getY())/32;

	b = Level::Instance()->getlevelBrick((int)_x,(int)_y);
	m_direction[0][1]  = b>0?b:0;
	m_directionPosition[0][1] = new Vector2D(_x,_y);


	 //check bottom
	  _x=(m_position.getX()+m_width/2)/32;
	  _y=(m_position.getY()+m_height)/32;

	b = Level::Instance()->getlevelBrick((int)_x,(int)_y);
	m_direction[2][1]  = b>0?b:0;
	m_directionPosition[2][1] = new Vector2D(_x,_y);


	//check right - middel
	_x=(m_position.getX()+m_width)/32;
	_y=(m_position.getY()+m_height/2)/32;

	b = Level::Instance()->getlevelBrick((int)_x,(int)_y);
	m_direction[1][2]  = b>0?b:0;
	m_directionPosition[1][2] = new Vector2D(_x,_y);

	 //check right - top
	 _x=(m_position.getX()+m_width)/32;
	 _y=(m_position.getY())/32;

	b = Level::Instance()->getlevelBrick((int)_x,(int)_y);
	m_direction[0][2]  = b>0?b:0;
	m_directionPosition[0][2] = new Vector2D(_x,_y);

	 //check right - bottom
	  _x=(m_position.getX()+m_width)/32;
	  _y=(m_position.getY()+m_height)/32;

	b = Level::Instance()->getlevelBrick((int)_x,(int)_y);
	m_direction[2][2]  = b>0?b:0;
	m_directionPosition[2][2] = new Vector2D(_x,_y);

	 //check center - center
	  _x=(m_position.getX()+m_width/2)/32;
	  _y=(m_position.getY()+m_height/2)/32;

	b = Level::Instance()->getlevelBrick((int)_x,(int)_y);
	m_direction[1][1]  = b>0?b:0;
	m_directionPosition[1][1] = new Vector2D(_x,_y);
  }



 bool SDLGameObject::checkCollision(SDLGameObject *cby   )
{
	SDL_Rect a = {
		m_position.getX(),
		m_position.getY(),
		m_width,m_height
	};
	SDL_Rect b = {
		cby->m_position.getX()-Level::Instance()->viewportx,
		cby->m_position.getY()-Level::Instance()->viewporty,
		cby->m_width,cby->m_height
	};
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
