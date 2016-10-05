#include "MenuItem.h"



MenuItem::MenuItem() :
	text("Error!") {
	rect->x = 0;
	rect->y = 0;
	rect->w = 0;
	rect->h = 0;
}
MenuItem::MenuItem(std::string newText) {
	text = newText;
	rect->x = 0;
	rect->y = 0;
	rect->w = 0;
	rect->h = 0;
}

MenuItem::~MenuItem()
{
}
