#include "stdafx.h"
#include "startmenu.h"
#include "globals.h"
#include "config.h"
#include <iostream>

using namespace base;

StartMenu::StartMenu(DataManager *data)
	: MenuWindow(), data(data), saved(true), close(false), config(0), confirmClose(0)
{
	//create window
	window = guienv->addWindow(rect<s32>(0,0,width,height), true);
	window->setDrawBackground(false);
	window->setDraggable(false);
	window->getCloseButton()->setVisible(false);

	//setup GUI font and other stuff
	gui::IGUISkin* metallic = guienv->createSkin(gui::EGST_WINDOWS_METALLIC);
	guienv->setSkin(metallic);
	metallic->drop();
	/*gui::IGUIFont *micro = guienv->getFont("res/font/verdana_micro.xml");
	gui::IGUIFont *menu_font = guienv->getFont("res/font/large.xml");*/
	gui::IGUIFont *astro = guienv->getFont("res/font/system.xml");
	guienv->getSkin()->setFont(astro);
	
	//setup colors for gui
	for (s32 i = 0; i < gui::EGDC_COUNT; ++i) {
		video::SColor col = guienv->getSkin()->getColor((gui::EGUI_DEFAULT_COLOR)i);
		col.setAlpha(208);
		col.setBlue(128);
		col.setGreen(118);
		col.setRed(108);
		guienv->getSkin()->setColor((gui::EGUI_DEFAULT_COLOR)i, col);
	}

	guienv->getSkin()->setColor(gui::EGDC_BUTTON_TEXT, video::SColor(255,255,255,255));
	guienv->getSkin()->setColor(gui::EGDC_HIGH_LIGHT_TEXT, video::SColor(255,255,255,255));
	guienv->getSkin()->setColor(gui::EGDC_3D_DARK_SHADOW, video::SColor(128,40,50,60));
	guienv->getSkin()->setColor(gui::EGDC_3D_SHADOW, video::SColor(128,80,90,100));
	guienv->getSkin()->setColor(gui::EGDC_ACTIVE_BORDER, video::SColor(255,145,155,165));
	guienv->getSkin()->setColor(gui::EGDC_INACTIVE_BORDER, video::SColor(128,80,90,100));
	guienv->getSkin()->setColor(gui::EGDC_GRAY_TEXT, video::SColor(128,40,50,60));
	guienv->getSkin()->setColor(gui::EGDC_WINDOW_SYMBOL, video::SColor(255,255,255,255));
	guienv->getSkin()->setColor(gui::EGDC_INACTIVE_CAPTION, video::SColor(255,200,200,200));
	guienv->getSkin()->setColor(gui::EGDC_ACTIVE_CAPTION, video::SColor(255,250,250,250));

	//create logo
	guienv->addImage(vdriver->getTexture("res/menu/lost_horizons_logo.png"), position2d<s32>(width/2-256,0), true, window);

	//create menu buttons
	resume = guienv->addButton(rect<s32>(width/2-50,height/2+20,width/2+50,height/2+40), window, -1, L"Resume");
	newgame = guienv->addButton(rect<s32>(width/2-50,height/2+20,width/2+50,height/2+40), window, -1, L"New Game");
	loadgame = guienv->addButton(rect<s32>(width/2-50,height/2+60,width/2+50,height/2+80), window, -1, L"Load Game");
	savegame = guienv->addButton(rect<s32>(width/2+10,height/2+60,width/2+110,height/2+80), window, -1, L"Save Game");
	closegame = guienv->addButton(rect<s32>(width/2-50,height/2+140,width/2+50,height/2+160), window, -1, L"Main Menu");
	options = guienv->addButton(rect<s32>(width/2-50,height/2+100,width/2+50,height/2+120), window, -1, L"Options");
	quit = guienv->addButton(rect<s32>(width/2-50,height/2+140,width/2+50,height/2+160), window, -1, L"Quit");

	//set button visibility
	savegame->setVisible(false);

	//create child windows
	config = new OptionMenu(window);
	confirmClose = new MessageMenu(rect<s32>(width/2-120,height/2-40,width/2+120,height/2+40), window, 0, MessageMenu::YESNO, false, false);
	confirmClose->moveButtons(position2d<s32>(0,-5));
	confirmClose->addText(position2d<s32>(20,15), dimension2d<u32>(60,50), L"You did not save. Are you sure?");

	setVisible(true);
}

//delete everything
StartMenu::~StartMenu()
{
	delete config;
	delete confirmClose;
}

void StartMenu::run()
{
	MenuWindow::run();
	if (getVisible()) {
		window->getParent()->getParent()->bringToFront(window->getParent()); // dafuq is dis shit omg so bad
		if (resume->isPressed()) {
			saved = false;
			setVisible(false);
		}
		if (newgame->isPressed()) {
			gConfig.bPlay = true;
			shift();
			game->createNewGame();
			setVisible(false);
		}
		if (loadgame->isPressed()) {
			if (gConfig.bPlay) {
				delete game;
				game = new Gameloop(data);
			} else {
				gConfig.bPlay = true;
				shift();
			}
			//game->createLoadedGame();
			data->load("saves/___TEST_SAVE___.lsv");//temporary
			setVisible(false);
		}
		if (savegame->isPressed()) {
			saved = true;
			//function for saving
			data->save("saves/___TEST_SAVE___.lsv");//temporary
			setVisible(false);
		}
		if (closegame->isPressed() && gConfig.bPlay) {
			if (gConfig.bCheckIfSaved && !saved) {
				confirmClose->setVisible(true);
			} else {
				close = true;
			}
		}
		if (options->isPressed()) {
			config->setVisible(true);
		}
		if (quit->isPressed()) {
			gConfig.bExit = true;
		}
		if (close) {
			gConfig.bPlay = false;
			shift();
			delete game;
			game = new Gameloop(data);
		}
		config->run();
		close = MessageMenu::YES == confirmClose->run();
	}
}

void StartMenu::shift()
{
	if (gConfig.bPlay) {
		newgame->setVisible(false);
		loadgame->move(position2d<s32>(-60,0));
		savegame->setVisible(true);
		quit->setVisible(false);
	} else {
		newgame->setVisible(true);
		loadgame->move(position2d<s32>(60,0));
		savegame->setVisible(false);
		quit->setVisible(true);
	}
}
