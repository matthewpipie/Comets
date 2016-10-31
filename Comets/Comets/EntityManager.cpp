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
			Comet *tempComet = &_comets[i];
			if (testComet.isColliding(tempComet)) {
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

void EntityManager::clean() {
	eraseDeadComets();
	eraseDeadPlayers();
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

void EntityManager::detectCollision() {
	for (int k = 0; k < _players.size(); k++) {
		for (int i = 0; i < _comets.size(); i++) {
			if (_comets[i].isColliding(&_players[k])) {
				_players[k].resolveCollision();
				_comets[i].setAlive(false);
			}
			for (int j = i + 1; j < _comets.size(); j++) {
				if (_comets[i].isColliding(&_comets[j])) {
					_comets[i].resolveCollision(&_comets[j]);
				}
			}
		}
	}

}
/*
void EntityManager::everyFrame() {
	tryToTwinkleStars();
	moveComets();
	tryToMakeComet();
	movePlayers();
	fixCollision();
	checkPlayers();
	cleanComets();
}*/



template<class SPRITES>
void EntityManager::eraseDeadSprites(SPRITES &sprites) {
	for (auto spriteI = sprites.begin(); spriteI != sprites.end(); /*++_cometI*/) {
		//std::cout << _playerI->isAlive() << std::endl;
		if (!spriteI->isAlive()) {
			spriteI = sprites.erase(spriteI);
		}
		else {
			++spriteI;
		}
	}
}

void EntityManager::tryToTwinkleStars() {
	for (_starI = _stars.begin(); _starI != _stars.end(); ++_starI) {
		_starI->twinkle();
	}
}

void EntityManager::moveComets() {
	/*
	if (MainGame::frameCount % 1 == 0) {
	for (_i = _sprites.begin(); _i != _sprites.end(); ++_i) {
	_i->setPos(MainGame::frameCount % 100, 0);
	}
	}*/

	for (_cometI = _comets.begin(); _cometI != _comets.end(); ++_cometI) {
		_cometI->moveComet();
	}

	
}

void EntityManager::tryToMakeComet() {
	if (MainGame::frameCount % Constants::COMET_SPAWN_RATE == 0) {
		makeComet();
		//std::cout << _comets.size() << std::endl;
		//std::cout << "Frame: " << MainGame::frameCount << std::endl;
	}
}