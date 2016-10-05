#pragma once
#include "stdafx.h"
class MenuItem
{
public:
	MenuItem();
	MenuItem(std::string newText);
	~MenuItem();
	std::string text;
	SDL_Rect *rect;
};

