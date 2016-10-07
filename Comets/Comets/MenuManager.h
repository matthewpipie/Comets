#pragma once
#include "stdafx.h"
#include "MenuGroup.h"
class MenuManager
{
public:
	MenuManager();
	~MenuManager();

	MenuGroup _mainMenu;
	MenuGroup _difficulties;
	MenuGroup _options;
	MenuGroup _credits;
	
	void defineMenus();
	void setMenuLocations();
	MenuGroup *findMenuGroup(std::string idToFind);

};



