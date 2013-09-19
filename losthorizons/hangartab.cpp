#include "stdafx.h"
#include "hangartab.h"

HangarTab::HangarTab(gui::IGUITabControl *tabs, Player *player) : MenuTab(), player(player),
	heavySlot(0), heavySlotWeapon(0), mediumSlot(0), mediumSlotWeapon(0), lightSlot(0), lightSlotWeapon(0), 
	repair(0), refit(0)
{
	tab = tabs->addTab(L"Hangar");
	//add hangar stuff
	//hangar allows the player to refit his ship
	//and repair
	guienv->addStaticText(L" Slot", rect<s32>(20,20,60,40), false, true, tab);
	heavySlot = guienv->addComboBox(rect<s32>(20,40,60,60),tab);
	heavySlotWeapon = guienv->addComboBox(rect<s32>(70,40,270,60),tab);

	guienv->addStaticText(L" Slot", rect<s32>(20,60,60,80), false, true, tab);
	mediumSlot = guienv->addComboBox(rect<s32>(20,80,60,100), tab);
	mediumSlotWeapon = guienv->addComboBox(rect<s32>(70,80,270,100), tab);

	guienv->addStaticText(L" Slot", rect<s32>(20,100,60,120), false, true, tab);
	lightSlot = guienv->addComboBox(rect<s32>(20,120,60,140), tab);
	lightSlotWeapon = guienv->addComboBox(rect<s32>(70,120,270,140), tab);

	refit = guienv->addButton(rect<s32>(290,40,390,60), tab, -1, L"Refit");
}

HangarTab::~HangarTab()
{

}

void HangarTab::run(SpaceStation *target)
{
	loadInventories();
	loadWeaponLists();

	if(refit->isPressed())
	{
		//refit for currently selected slot
		//add the item back to inventory
		player->getInventory().addItem(player->getInfo().mediumTurrets[mediumSlot->getSelected()]->getTurretType(), 1);
		player->setMediumTurret(ObjectManager::E_TURRET_LIST::PHOTONI, mediumSlot->getSelected());
		player->getInventory().removeItem(player->getInfo().mediumTurrets[mediumSlot->getSelected()]->getTurretType());
		mediumSlotWeapon->clear();
	}
}

//protected function
void HangarTab::loadInventories()
{
	//if they're empty make sure we refill them
	if(!heavySlot->getItemCount())
	{
		for(unsigned i = 0; i < player->getInfo().heavyTurrets.size(); ++i)
		{
			heavySlot->addItem(std::to_wstring(i).c_str());
		}
	}
	if(!mediumSlot->getItemCount())
	{
		for(unsigned i = 0; i < player->getInfo().mediumTurrets.size(); ++i)
		{
			mediumSlot->addItem(std::to_wstring(i).c_str());
		}
	}
	if(!lightSlot->getItemCount())
	{
		for(unsigned i = 0; i < player->getInfo().lightTurrets.size(); ++i)
		{
			lightSlot->addItem(std::to_wstring(i).c_str());
		}
	}
}

//protected function
void HangarTab::loadWeaponLists()
{
	//update the combobox to allow the player to choose weapons
	//create unique lists for each weaponslot

	if(mediumSlot->getSelected() != -1)
	{
		if(!mediumSlotWeapon->getItemCount())
		{
			mediumSlotWeapon->addItem(ObjectManager::turretList[mediumSlot->getSelected()].getName().c_str());
			for (unsigned i = 0; i < player->getInventory().getWeaponsList().size(); ++i)
			{
				mediumSlotWeapon->addItem(player->getInventory().getWeaponsList()[i].c_str());
			}
		}
	}
	if(lightSlot->getSelected() != -1)
	{
		if(lightSlotWeapon->getItemCount())
		{
			lightSlotWeapon->addItem(ObjectManager::turretList[lightSlot->getSelected()].getName().c_str());
		}
	}
}
