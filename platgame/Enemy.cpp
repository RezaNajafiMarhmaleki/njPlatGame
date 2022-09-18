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

	if(m_velocity.getX()>=0)
		if((m_direction[1][2]<=0 || m_direction[1][2]>=70 )&& m_direction[2][2]>0){
			m_velocity.setX(m_speed);
			m_currentFrame = int(((SDL_GetTicks() / 100) % (m_maxFrame/2)))+(m_maxFrame/2);
		}else{
			m_velocity.setX(0);
		}

	if(m_velocity.getX()<=0)
		if((m_direction[1][0]<=0 || m_direction[1][0]>=70 )&& m_direction[2][0]>0){
			m_velocity.setX(-m_speed);
			m_currentFrame = int(((SDL_GetTicks() / 100) % (m_maxFrame/2)));
		}else{
			m_velocity.setX(0);
		}

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