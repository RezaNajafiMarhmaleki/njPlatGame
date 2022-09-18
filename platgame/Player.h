#include "stdafx.h"
#include "SDLGameObject.h"

class Player: public SDLGameObject
{
public:
	Player(const LoaderParams* pParams);
	virtual  void draw();
 virtual void update();
	virtual void clean();
  virtual void checkDirection();
  int getScore(){return m_score;}
  int getLife(){return m_life;}
  void setLife(int life){  m_life = life;}
private:
	int m_score;
	int m_life;
};

