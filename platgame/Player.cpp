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

	if(m_position.getY()>=SCREEN_HEIGHT || m_life<=0)
		TheGame::Instance()->GameOver();

	if(m_position.getX()+m_width>=SCREEN_WIDTH)
		TheGame::Instance()->GameWin();
	
	if(m_position.getX()>= SCREEN_WIDTH-(SCREEN_WIDTH/3 ) || 
		(Level::Instance()->viewportx%32>0)  ){
		if(Level::Instance()->ViewPort_Inc())
			m_position.setX(m_position.getX()-1);
	}
	/*if(m_position.getX()<= (SCREEN_WIDTH/3 ) ){
		if(Level::Instance()->ViewPort_Dec())
			m_position.setX(m_position.getX()+32);
	}*/

	if(m_direction[1][0]>=70){
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

	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	if(m_direction[1][2]<=0 && m_position.getX()+m_width<SCREEN_WIDTH){
		m_velocity.setX(2);
		m_currentFrame = int(((SDL_GetTicks() / 100) % 3));
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

	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
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