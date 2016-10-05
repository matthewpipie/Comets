#pragma once
#include "stdafx.h"
#include "MenuItem.h"
class MenuGroup
{
public:
	MenuGroup();
	~MenuGroup();
	std::vector<MenuItem> actionButtons;
	std::vector<MenuItem> menuButtons;
	std::vector<MenuItem> text;
};

