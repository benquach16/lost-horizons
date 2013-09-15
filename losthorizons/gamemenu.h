#ifndef _GAMEMENU_H_
#define _GAMEMENU_H_

#include "menuwindow.h"
#include "player.h"
#include "shiptab.h"
//show ingame information in this menu

class GameMenu : public MenuWindow
{
public:
	GameMenu(Player* player);
	~GameMenu();

	virtual void run();

protected:
	void initializeDisplay();
	
	Player* player;

	gui::IGUITabControl* tabs;

	//initializing tabs
	ShipTab* ship;
	//MenuTab* cargo;
	//MenuTab* crew;
	//MenuTab* loadout;
	//MenuTab* hangar;
	//MenuTab* missionLog;
};
#endif
