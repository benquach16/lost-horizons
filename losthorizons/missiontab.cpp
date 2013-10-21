#include "missiontab.h"
#include "globals.h"

using namespace base;

MissionTab::MissionTab(IGUITabControl *tabs, MissionManager *missionManager) : MenuTab(), missionList(0), missionDescription(0),
	missionManager(missionManager), marker(new Marker)
{
	tab = tabs->addTab(L"Mission Log");

	missionList = guienv->addListBox(rect<s32>(20, 20, 300, 480), tab);
	missionDescription = guienv->addStaticText(L"", rect<s32>(320, 20, 780, 480), false, true, tab);

	marker->setVisible(false);
}

MissionTab::~MissionTab()
{
	delete marker;
}

void MissionTab::run()
{
	loadMissions();
	//see if player has a mission selected
	int selected = missionList->getSelected();
	if(selected != -1)
	{
		//we have one selected
		std::vector<Mission> missions = missionManager->getMissions();
		missionDescription->setText(missions[selected].getDesc().c_str());
		//how do we tell player ware objective is?
		//we set objective marker
		marker->setVisible(true);
		marker->setPosition(missions[selected].getCurrObjPos());
	}
	else
	{
		marker->setVisible(false);
	}
}

void MissionTab::loadMissions()
{
	//load missions from mission manager
	if(!missionList->getItemCount())
	{
		for(unsigned i = 0; i < missionManager->getMissions().size(); i++)
		{
			missionList->addItem(missionManager->getMissions()[i].getName().c_str());
		}
	}
}
