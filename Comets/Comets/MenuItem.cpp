#include "MenuItem.h"



MenuItem::MenuItem() :
	text("Error!"),
	id("") {
	resetRect();
}
MenuItem::MenuItem(std::string newid) :
	text("Error!") {
	id = newid;
	resetRect();
}
MenuItem::MenuItem(std::string newid, std::string newText) {
	text = newText;
	id = newid;
	resetRect();
}

MenuItem::~MenuItem()
{
}

void MenuItem::resetRect() {
	rect->x = 0;
	rect->y = 0;
	rect->w = 0;
	rect->h = 0;
}
