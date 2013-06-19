#ifndef _OPTIONMENU_H_
#define _OPTIONMENU_H_

#include "menuwindow.h"
#include "irrlicht.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace gui;

//displays options to change config
class OptionMenu : public MenuWindow
{
public:
	OptionMenu(irr::IrrlichtDevice *graphics);

	void run();

	bool OptionMenu::get(gui::IGUICheckBox *item);
	int OptionMenu::get(gui::IGUIComboBox *item, const int* val);

private:
	int resY[8];
	int resX[8];
	gui::IGUIElement *control;
	gui::IGUIComboBox *resolution;
	//gui::IGUIComboBox *dynamicLighting;		to implement
	gui::IGUICheckBox *fullscreen;
	//gui::IGUICheckBox *vsync;				to implement
	gui::IGUIButton *quit;
	gui::IGUIButton *apply;
};
#endif
