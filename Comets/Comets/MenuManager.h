#pragma once
#include "stdafx.h"
#include "MenuGroup.h"
class MenuManager
{
public:
	MenuManager();
	~MenuManager();

	MenuGroup _mainMenu;
	MenuGroup _options;
	MenuGroup _difficulties;
	MenuGroup _credits;

};



