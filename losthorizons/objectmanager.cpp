//#include "stdafx.h"
#include "objectmanager.h"
#include <iostream>

std::vector<ItemProperties> ObjectManager::itemList;
std::vector<ShipProperties> ObjectManager::shipList;

ObjectManager::ObjectManager(IrrlichtDevice *graphics)
{
	//read in items and ships
	//heres the list of items and ships so far
	//would prefer not to use pointers but since there are inherited classes we have to
	std::cout << "Loading item properties...." << std::endl;
	itemList.push_back(ItemProperties(graphics, "items/water.xml"));
	shipList.push_back(ShipProperties(graphics, "items/ships/praetorian_cruiser.xml"));

}

ObjectManager::~ObjectManager()
{

}