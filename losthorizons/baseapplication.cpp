#include "stdafx.h"
#include "baseapplication.h"
#include <iostream>
#include "config.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

BaseApplication::BaseApplication() : receiver(new KeyListener)
{
	gConfig.Load();
}

BaseApplication::~BaseApplication()
{
	graphics->drop();
	gConfig.Save();
}

void BaseApplication::init()
{
	buildGraphics();
	game = new Gameloop(graphics, receiver);
	run();
}

void BaseApplication::restart()
{
	IrrlichtDevice *oldGraphics = graphics;
	buildGraphics();
	oldGraphics->drop();
}

void BaseApplication::run()
{
	//graphics loop
	while(graphics->run())
	{
		graphics->getVideoDriver()->beginScene(true, true, SColor(255,100,101,140));

		//run game
		game->run();
		graphics->getSceneManager()->drawAll();
		graphics->getGUIEnvironment()->drawAll();

		graphics->getVideoDriver()->endScene();

		if (resolutionX != gConfig.iResolutionX ||
			resolutionY != gConfig.iResolutionY ||
			fullscreen != gConfig.bFullScreen) {
			restart();
		}
	}
}

void BaseApplication::buildGraphics()
{
	graphics = createDevice(EDT_DIRECT3D9,
		dimension2du(gConfig.iResolutionX, gConfig.iResolutionY),
		gConfig.iBits,
		gConfig.bFullScreen,
		false,
		false,
		receiver);
		
	if(!graphics)
	{
		std::cerr << "Error creating device";
		std::exit(1);
	}

	resolutionX = gConfig.iResolutionX;
	resolutionY = gConfig.iResolutionY;
	fullscreen = gConfig.bFullScreen;
}
