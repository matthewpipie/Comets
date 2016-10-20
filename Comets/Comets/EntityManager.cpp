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
	Comet testComet;
	int count = 0;
	do {
		canExist = true;
		testComet.initPos();
		for (int i = 0; i < _comets.size(); i++) {
			if (testComet.isColliding(&_comets[i])) {
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
	_comets.push_back(testComet);
}

void EntityManager::eraseDeadComets() {
	for (std::vector<Comet>_cometI = _comets.begin(); _cometI != _comets.end(); /*++_cometI*/) {
		if (!_cometI->isAlive()) {
			_cometI = _comets.erase(_cometI);
		}
		else {
			++_cometI;
		}
	}
	// std::cout << _comets.size() << std::endl;
}

void EntityManager::eraseDeadPlayers() {
	/*Player test;
	Sprite *test2 = &test;
	std::vector<Sprite> test5(_players.begin(), _players.end());
	std::vector<Sprite> *3test = &_players;*/
	eraseDeadSprites(_players);
}

bool EntityManager::arePlayersAlive() {
	if (_players.size() < 1) {
		return false;
	}
	return true;
}

template<class SPRITE>
EntityManager::eraseDeadSprites(SPRITE &sprite) {
	for (auto spriteI = sprite->begin(); spriteI != sprite->end(); /*++_cometI*/) {
		//std::cout << _playerI->isAlive() << std::endl;
		if (!spriteI->isAlive()) {
			spriteI = sprite->erase(spriteI);
		}
		else {
			++spriteI;
		}
	}
}