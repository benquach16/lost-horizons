#ifndef _MENUWINDOW_H_
#define _MENUWINDOW_H_

#include "irrlicht.h"

using namespace irr;
using namespace core;
using namespace gui;

//This is the base class of menus in the game

class MenuWindow
{
public:
	MenuWindow(irr::IrrlichtDevice *graphics) : visible(false), graphics(graphics), window(0) {}
	virtual ~MenuWindow()
	{
		window->drop();
	}

	void run()
	{
		window->setVisible(visible);
	}

	bool getVisible()
	{
		return visible;
	}

private:
	bool visible;

protected:
	irr::IrrlichtDevice *graphics;
	gui::IGUIWindow *window;
};
#endif
