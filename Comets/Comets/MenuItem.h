#pragma once
#include "stdafx.h"
class MenuItem
{
public:
	MenuItem();
	MenuItem(std::string id);
	MenuItem(std::string id, std::string newText);
	void resetRect();
	~MenuItem();
	std::string text;
	SDL_Rect rect;
	std::string id;
};

