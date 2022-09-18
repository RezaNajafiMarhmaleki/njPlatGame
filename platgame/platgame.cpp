
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
