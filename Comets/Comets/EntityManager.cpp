#include "EntityManager.h"
#include "Errors.h"


EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

void EntityManager::makeComet() {
	bool canExist = false;
	std::auto_ptr<Comet> testComet;
	int count = 0;
	do {
		canExist = true;
		testComet->initPos();
		for (int i = 0; i < _comets.size(); i++) {
			if (testComet->isColliding(&*_comets[i])) {
				canExist = false;
				break;
			}
		}
		count++;
		//std::cout << "Looked for comet space " << count << " times." << std::endl;
		if (count > 2000) {
			fatalError("Error: Could not find spawn location for comet.");
		}
	} while (!canExist);
	_comets.push_back(testComet); //TODO: memory leak? does this work in the first place?
}

void EntityManager::eraseDeadComets() {
	eraseDeadSprites(_comets);
}

void EntityManager::eraseDeadPlayers() {
	eraseDeadSprites(_players);
}

bool EntityManager::arePlayersAlive() {
	if (_players.size() < 1) {
		return false;
	}
	return true;
}

template<class SPRITES>
void EntityManager::eraseDeadSprites(SPRITES &sprites) {
	for (auto spriteI = sprites.begin(); spriteI != sprites.end(); /*++_cometI*/) {
		//std::cout << _playerI->isAlive() << std::endl;
		if (!(*spriteI)->isAlive()) {
			spriteI = sprites.erase(spriteI);
		}
		else {
			++spriteI;
		}
	}
}