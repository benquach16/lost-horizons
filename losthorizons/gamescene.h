#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

//Here we manage the current scene and all objects inside of the scene
//We shouldn't deal with creating multiple scenes too much, since an entire solar system should be a single scene
//only for the implementation of multiple solar systems
//so for now, keep the design as a singleton
#include <list>
#include <stack>

#include "player.h"
#include "fighter.h"
#include "spacestation.h"
#include "projectile.h"
#include "sun.h"
#include "planet.h"
#include "objectmanager.h"
#include "playercamera.h"
#include "keylistener.h"
#include "effect.h"

enum E_GAME_SCENE
{
	SCENE_MAINMENU,
	SCENE_TAU_CETI,
};

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

class GameScene
{
public:
	GameScene();
	//parameterized constructor
	//for creating a specific scene
	GameScene(IrrlichtDevice *graphics, E_GAME_SCENE scene = SCENE_MAINMENU);
	~GameScene();
	void loadScene();
	void saveScene();
	void run(f32 frameDeltaTime);

	PlayerCamera *createPlayerCam(const vector3df &position = vector3df(0.f,0.f,0.f));
	Ship *createShip(const E_GAME_FACTION &faction, ObjectManager::E_SHIP_LIST shipType = ObjectManager::E_SHIP_LIST::PRAE_CRUISER,
					 const vector3df &position = vector3df(0.f,0.f,0.f), const vector3df &rotation = vector3df(0.f,0.f,0.f));
	Ship *createShip(u32 ID, const ShipInformation &info, const vector3df &position, const vector3df &rotation);
	Sun *createSun(const vector3df &position = vector3df(0.f,0.f,0.f), const vector3df &scale = vector3df(1.f,1.f,1.f));
	SpaceStation *createStation(const E_GAME_FACTION faction, ObjectManager::E_STATION_LIST stationType = ObjectManager::E_STATION_LIST::TRADING,
					const vector3df &position = vector3df(), const vector3df& rotation = vector3df());
	PlayerCamera *getCurrentSceneCamera();
	E_GAME_SCENE getScene();
	
private:
	E_GAME_SCENE scene;
	PlayerCamera *playerCam;
	IrrlichtDevice *graphics;
	ISceneNode *skybox;
	std::stack<ISceneNode*> sceneObjects;		//stores static scene node objects
	std::stack<Object*> dynamicObjects;			//stores the stuff with more complexity
};

#endif
