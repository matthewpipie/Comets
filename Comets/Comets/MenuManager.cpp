#include "MenuManager.h"



MenuManager::MenuManager()
{
	defineMenus();
	setMenuLocations();

}

void MenuManager::defineMenus() {
	_mainMenu.menuButtons.push_back(MenuItem("play", "Play"));
	_mainMenu.menuButtons.push_back(MenuItem("options", "Options"));
	_mainMenu.menuButtons.push_back(MenuItem("credits", "Credits"));
	_mainMenu.actionButtons.push_back(MenuItem("quit", "Quit"));

	_difficulties.actionButtons.push_back(MenuItem("easy", "Easy"));
	_difficulties.actionButtons.push_back(MenuItem("medium", "Medium"));
	_difficulties.actionButtons.push_back(MenuItem("hard", "Hard"));
	_difficulties.actionButtons.push_back(MenuItem("crazy", "Crazy"));
	_difficulties.actionButtons.push_back(MenuItem("insane", "Insane"));
	_difficulties.actionButtons.push_back(MenuItem("actuallyImpossible", "Actually Impossible"));
	_difficulties.actionButtons.push_back(MenuItem("back", "Back"));

	_options.actionButtons.push_back(MenuItem("back", "Back"));
	_options.actionButtons.push_back(MenuItem("music", "Music"));
	_options.textButtons.push_back(MenuItem("p1controlsText", "Player 1 Controls"));
	_options.textButtons.push_back(MenuItem("p2controlsText", "Player 2 Controls"));
	_options.textButtons.push_back(MenuItem("p3controlsText", "Player 3 Controls"));
	_options.textButtons.push_back(MenuItem("p4controlsText", "Player 4 Controls"));
	_options.actionButtons.push_back(MenuItem("p1controls", "Loading..."));
	_options.actionButtons.push_back(MenuItem("p2controls", "Loading..."));
	_options.actionButtons.push_back(MenuItem("p3controls", "Loading..."));
	_options.actionButtons.push_back(MenuItem("p4controls", "Loading..."));

	_credits.actionButtons.push_back(MenuItem("back", "Back"));
	_credits.textButtons.push_back(MenuItem("matthew", "Everything-er: Matthew Giordano"));
}


MenuManager::~MenuManager()
{
}

MenuGroup *MenuManager::findMenuGroup(std::string idToFind) {
	//will find MenuGroup (out of the 4) containing idToFind
	return &_options;
}

void MenuManager::setMenuLocations() {
	//will set menu locations using a lot of findMenuGroups
}