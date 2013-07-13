#include "stdafx.h"
#include "gamescenemanager.h"

GameSceneManager::GameSceneManager() : currentScene(0)
{

}

GameSceneManager::GameSceneManager(irr::IrrlichtDevice *graphics) : currentScene(new GameScene(graphics)), graphics(graphics)
{
	//create scene
}

GameSceneManager::GameSceneManager(irr::IrrlichtDevice *graphics, E_GAMESCENES scene) : currentScene(new GameScene(graphics, scene)),
	graphics(graphics)
{
	//create specific scene
}

GameSceneManager::~GameSceneManager()
{
	delete currentScene;
}

void GameSceneManager::runCurrentScene(float frameDeltaTime)
{
	if(currentScene)
		currentScene->run(frameDeltaTime);
}

void GameSceneManager::changeCurrentScene(E_GAMESCENES scene)
{
	//need to delete the entire scene
	
	if(currentScene)
	{
		delete currentScene;
		currentScene = new GameScene(graphics, scene);
	}
	else
		currentScene = new GameScene(graphics, scene);
}

GameScene *GameSceneManager::getCurrentScene()
{
	return currentScene;
}