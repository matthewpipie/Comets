/* Copyright (C) 2016 Matthew Giordano
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#include <stdlib.h>
#include <string>
#include "stdafx.h"
#include "MainGame.h"
#include "Errors.h"

int MainGame::frameCount = 0;

MainGame::MainGame() : _window(nullptr), 
	_maxFPS(60.0f), 
	_gameState(GameState::PLAY), 
	pause(false),
	fullscreenMode(0),
	_mouseX(0),
	_mouseY(0) {
	std::fill(_keysPressed, _keysPressed + sizeof(_keysPressed), 0);
}

MainGame::~MainGame() {
}

void MainGame::run() {
	initSDL();
	makeWindow();
	makeRenderer();
	loadTextures();
	
	restartGame();

	// _sprites[0].initTexture(_renderer);
	// _sprites[1].initTexture(_renderer, "resources/comet.bmp");
	// _sprites[2].initTexture(_renderer, "resources/comet.bmp");
	// _sprites[3].initTexture(_renderer, "resources/comet.bmp");
	// _sprites[4].initTexture(_renderer, "resources/comet.bmp");
	// _sprites[0].setPixelAttributes(00, 0, 64, 64);
	// _sprites[1].setPixelAttributes(16, 0, 32, 32);
	// _sprites[2].setPixelAttributes(16 + 32, 0, 63, 63);
	// _sprites[3].setPixelAttributes(16 + 32 + 63, 0, 126, 126);
	// _sprites[0].setAttributes(16 + 32 + 63 + 126, 0, 20, 20);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	/*_sprites[0].rect.x = 0;
	_sprites[0].rect.y = 0;
	_sprites[0].rect.w = 100;
	_sprites[0].rect.h = 100;*/

	gameLoop();
}

void MainGame::initSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fatalError("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
	}
	SDL_GL_SetSwapInterval(0);
	SDL_ShowCursor(0);
}

void MainGame::makeWindow() {
	_window = SDL_CreateWindow("SDL Fun", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (_window == nullptr) {
		fatalError("SDL Window could not initialize! SDL_Error: " + std::string(SDL_GetError()));
	}
}

void MainGame::makeRenderer() {
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == nullptr) {
		SDL_DestroyWindow(_window);
		fatalError("SDL Renderer could not initialize! SDL_Error: " + std::string(SDL_GetError()));
	}
}

void MainGame::loadTextures() {
	Comet::initCometTexture(_renderer);
	Star::initStarTexture(_renderer);
	Player::initPlayerTexture(_renderer);
}

void MainGame::restartGame() {
	makeComets();
	makeStars();
	makePlayers();
}

void MainGame::makeComets() {
	_comets.resize(0);
	for (int i = 0; i < Constants::COMET_COUNT; i++) {
		makeComet();
	}

	/*makeComet();
	makeComet();
	_comets[0].setPos(0., 0.);
	_comets[0].setAngle(45.);
	_comets[0].setSpeed(.011);
	_comets[1].setPos(100., 100.);
	_comets[1].setAngle(225.);
	_comets[1].setSpeed(.011);*/
}

void MainGame::makeStars() {
	_stars.resize(0);
	for (int i = 0; i < Constants::STAR_COUNT; i++) {
		_stars.push_back(Star());
		_stars[i].initStar();
	}
}

void MainGame::makePlayers() {
	_players.resize(0);
	for (int i = 0; i < Constants::PLAYER_COUNT; i++) {
		_players.push_back(Player());
		_players[i].playerNumber = i;
		_players[i].initPos();
	}
}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		float startTicks = SDL_GetTicks();

		processInput();
		if (!pause) {
			moveComets();
			movePlayers();
			fixCollision();
			bool shouldContinue = checkPlayers();
			cleanComets();
			drawGame();
			if (!shouldContinue) {
				pause = true;
				restartGame();
				continue;
			}
		}

		float frameTicks = SDL_GetTicks() - startTicks;

		if (MainGame::frameCount % 60 == 0) {
			 //std::cout << MainGame::frameCount << std::endl;
		}

		if (1000.0f / _maxFPS > frameTicks) {
			SDL_Delay((Uint32)(1000.0f / _maxFPS - frameTicks));
		}
		if (!pause) {
			MainGame::frameCount++;
		}
	}
	// X button pressed
	SDL_DestroyTexture(Star::starTexture);
	SDL_DestroyTexture(Comet::cometTexture);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
	exit(0);
}

void MainGame::processInput() {
	SDL_Event evnt;

	// Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_KEYDOWN:
				if (evnt.key.keysym.sym > 127) {
					evnt.key.keysym.sym -= Constants::CONSTANT_SDL_CONTROL_NUMBER;
				}
				_keysPressed[evnt.key.keysym.sym] = true;
				//std::cout << evnt.key.keysym.sym << std::endl;
				if (evnt.key.keysym.sym == SDLK_f) {
					fullscreenMode = !fullscreenMode;
					SDL_SetWindowFullscreen(_window, fullscreenMode == 0 ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
					SDL_RenderPresent(_renderer);
					int h, w;
					SDL_GetRendererOutputSize(_renderer, &w, &h);
					//std::cout << w << " " << h << std::endl;
					Constants::SCREEN_WIDTH = w;
					Constants::SCREEN_WIDTH_CALC = Constants::SCREEN_WIDTH - 1;
					Constants::SCREEN_HEIGHT = h;
					Constants::SCREEN_HEIGHT_CALC = Constants::SCREEN_HEIGHT - 1;
					restartGame();
				}
				break;
			case SDL_KEYUP:
				if (evnt.key.keysym.sym > 127) {
					evnt.key.keysym.sym -= Constants::CONSTANT_SDL_CONTROL_NUMBER;
				}
				_keysPressed[evnt.key.keysym.sym] = false;
				//std::cout << evnt.key.keysym.sym << " is rip" << std::endl;
				break;
			case SDL_MOUSEMOTION:
				_mouseX = evnt.motion.x;
				_mouseY = evnt.motion.y;
				/*// std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
				if (evnt.motion.x == 0) {
					//pause = true;
				} else {
					pause = false; 
				}
				// _sprites[0].setMiddlePixelPos(evnt.motion.x, evnt.motion.y); */
				break;
		}
	}

	if (_keysPressed[SDLK_ESCAPE]) {
		_gameState = GameState::EXIT;
	}
	if (_keysPressed[SDLK_SPACE]) {
		pause = false;
	}

}

void MainGame::drawGame() {
	/*Get window surface
	SDL_Surface *screenSurface = SDL_GetWindowSurface(_window);

	// Fill the surface white
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

	// Update the surface
	SDL_UpdateWindowSurface(_window);*/

	SDL_RenderClear(_renderer);

	for (_starI = _stars.begin(); _starI != _stars.end(); ++_starI) {  // render stars first, before anything else, so they are in the bkg
		SDL_Rect temprect = _starI->getFixedRect();
		SDL_RenderCopy(_renderer, Star::starTexture, NULL, &temprect);
		// std::cout << "Star copying @ X:" << _starI->_x << " Y: " << _starI->_y << " W: " << _starI->_w << " H: " << _starI->_h << " TXT: " << _starI->texture << std::endl;
	}
	for (_cometI = _comets.begin(); _cometI != _comets.end(); ++_cometI) {
		SDL_Rect temprect = _cometI->getFixedRect();
		SDL_RenderCopy(_renderer, Comet::cometTexture, NULL, &temprect);
	}
	for (_playerI = _players.begin(); _playerI != _players.end(); ++_playerI) {
		int playerNumber = _playerI->playerNumber;
		SDL_SetTextureColorMod(Player::playerTexture, Constants::shipColors[playerNumber][0], Constants::shipColors[playerNumber][1], Constants::shipColors[playerNumber][2]);
		SDL_Rect temprect = _playerI->getFixedRect();
		SDL_RenderCopy(_renderer, Player::playerTexture, NULL, &temprect);
	}

	SDL_RenderPresent(_renderer);
	// std::cout << "DONE!" << std::endl;
}

void MainGame::movePlayers() {
	//std::cout << _mouseX << Constants::SCREEN_HEIGHT_CALC - _mouseY << std::endl;
	std::vector<double> xMovements;
	std::vector<double> yMovements;
	//int al
	for (_playerI = _players.begin(); _playerI != _players.end(); ++_playerI) {
		int playerNumber = _playerI->playerNumber;
		if (playerNumber != 0) {
			int currentLen = xMovements.size();
			if (_keysPressed[Constants::CONTROL_UP[Constants::PLAYER_CONTROLS[playerNumber]]]) {
				xMovements.push_back(0);
				yMovements.push_back(1);
			}
			else if (_keysPressed[Constants::CONTROL_DOWN[Constants::PLAYER_CONTROLS[playerNumber]]]) {
				xMovements.push_back(0);
				yMovements.push_back(-1);
			}

			if (_keysPressed[Constants::CONTROL_LEFT[Constants::PLAYER_CONTROLS[playerNumber]]]) {
				xMovements.push_back(-1);
				yMovements.push_back(0);
			}
			else if (_keysPressed[Constants::CONTROL_RIGHT[Constants::PLAYER_CONTROLS[playerNumber]]]) {
				xMovements.push_back(1);
				yMovements.push_back(0);
			}
			if (currentLen == xMovements.size()) {
				xMovements.push_back(0);
				yMovements.push_back(0);
			}
		}
		else {
			if (playerNumber == 0) {
				_playerI->setPixelPos(_mouseX, Constants::SCREEN_HEIGHT_CALC - _mouseY);
			}
			xMovements.push_back(0);
			yMovements.push_back(0);
		}


	}
	for (int i = 0; i < _players.size(); i++) {
		_players[i].move(xMovements[i], yMovements[i]);
	}
	for (_playerI = _players.begin(); _playerI != _players.end(); ++_playerI) {
		if (_playerI->getPercentX() > 100) {
			_playerI->setPercentX(100);
		}
		else if (_playerI->getPercentX() < 0) {
			_playerI->setPercentX(0);
		}
		if (_playerI->getPercentY() > 100) {
			_playerI->setPercentY(100);
		}
		else if (_playerI->getPercentY() < 0) {
			_playerI->setPercentY(0);
		}
	}
}

void MainGame::moveComets() {
	/*
	if (MainGame::frameCount % 1 == 0) {
		for (_i = _sprites.begin(); _i != _sprites.end(); ++_i) {
			_i->setPos(MainGame::frameCount % 100, 0);
		}
	}*/

	for (_starI = _stars.begin(); _starI != _stars.end(); ++_starI) {
		_starI->twinkle();
	}

	for (_cometI = _comets.begin(); _cometI != _comets.end(); ++_cometI) {
		_cometI->moveComet();
	}

	if (MainGame::frameCount % Constants::COMET_SPAWN_RATE == 0) {
		makeComet();
		//std::cout << _comets.size() << std::endl;
		//std::cout << "Frame: " << MainGame::frameCount << std::endl;
	}
}

void MainGame::fixCollision() {
	for (int k = 0; k < _players.size(); k++) {
		for (int i = 0; i < _comets.size(); i++) {
			if (_comets[i].isColliding(&_players[k])) {
				_players[k].resolveCollision();
			}
			for (int j = i + 1; j < _comets.size(); j++) {
				if (_comets[i].isColliding(&_comets[j])) {
					_comets[i].resolveCollision(&_comets[j]);
				}
			}
		}
	}
	
}

void MainGame::cleanComets() {
	for (_cometI = _comets.begin(); _cometI != _comets.end(); /*++_cometI*/) {
		if (!_cometI->isAlive()) {
			_cometI = _comets.erase(_cometI);
		} else {
			++_cometI;
		}
	}
	// std::cout << _comets.size() << std::endl;
}

void MainGame::makeComet() {
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

bool MainGame::checkPlayers() {
	for (_playerI = _players.begin(); _playerI != _players.end(); /*++_cometI*/) {
		//std::cout << _playerI->isAlive() << std::endl;
		if (!_playerI->isAlive()) {
			_playerI = _players.erase(_playerI);
		}
		else {
			++_playerI;
		}
	}
	if (_players.size() < 1) {
		return false;
	}
	return true;
}
