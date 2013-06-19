#include "stdafx.h"
#include "gameloop.h"

Gameloop::Gameloop()
{
}

Gameloop::Gameloop(IrrlichtDevice *graphics, KeyListener *receiver) : currentScene(new GameScene), 
	graphics(graphics), receiver(receiver)
{
	//create player and camera
	playerCam = graphics->getSceneManager()->addCameraSceneNode();
}

Gameloop::~Gameloop()
{
}

void Gameloop::run()
{
	playerControl();
	cameraControl();
}

void Gameloop::playerControl()
{
	//all actions the player can do are stored here
	if(receiver->isKeyDown(irr::KEY_KEY_X))
	{
		//accelerate

	}
}

void Gameloop::cameraControl()
{
	
}
