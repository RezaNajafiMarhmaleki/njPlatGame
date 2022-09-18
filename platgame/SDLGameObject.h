#pragma once
#include "GameObject.h"
#include "Vector2D.h"
class SDLGameObject: public GameObject
{
public:
SDLGameObject(const LoaderParams* pParams);
virtual void draw();
virtual void update();
virtual void clean();
virtual void checkDirection();
 virtual bool checkCollision(SDLGameObject *cby   );

protected:
Vector2D m_position;
Vector2D m_velocity;
Vector2D m_acceleration;
int m_width;
int m_height;
int m_currentRow;
int m_currentFrame;
int m_maxFrame;
std::string m_textureID;
	float m_speed;
int m_direction[3][3];
Vector2D* m_directionPosition[3][3];
};

