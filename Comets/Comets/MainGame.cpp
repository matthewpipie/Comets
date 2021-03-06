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
	_renderer(nullptr),
	_textFont(nullptr),
	_maxFPS(60.0f), 
	_gameState(GameState::MENU_MAIN), 
	fullscreenMode(0),
	_mouseX(0),
	_mouseY(0) {
}

MainGame::~MainGame() {
}

void MainGame::run() {
	initSDL();
	initFont();
	initMusic();
	makeWindow();
	makeRenderer();
	loadTextures();
	loadMusic();
	
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
	/*_sprites[0].rect.x = 0;
	_sprites[0].rect.y = 0;
	_sprites[0].rect.w = 100;
	_sprites[0].rect.h = 100;*/

	gameLoop();
}


void MainGame::makeMenus() {
	

}

void MainGame::loadTextures() {
	Comet::initCometTexture(_renderer);
	Star::initStarTexture(_renderer);
	Player::initPlayerTexture(_renderer);
}

void MainGame::startGame(int difficulty) {
	_gameState = (GameState)difficulty;
	resumeGame();
}
void MainGame::resumeGame() {
	if ((int)_gameState > 10) {
		_gameState = (GameState)((int)_gameState - 10);
	}
	_score = 0;
	_gameStart = MainGame::frameCount;
	makeComets();
	makeStars();
	makePlayers();
}
void MainGame::endGame() {
	_gameState = GameState::MENU_DIFFICULTIES;
}

bool MainGame::isInGame() {
	if ((int)_gameState > 0 && (int)_gameState < 11) {
		return true;
	}
	return false;
}

void MainGame::makeComets() { // INTO _entityManager.initResources
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

void MainGame::makeStars() {// INTO _entityManager.initResources
	_stars.resize(0);
	for (int i = 0; i < Constants::STAR_COUNT; i++) {
		_stars.push_back(Star());
		_stars[i].initStar();
	}
}

void MainGame::makePlayers() {// INTO _entityManager.initResources
	_players.resize(0);
	for (int i = 0; i < Constants::PLAYER_COUNT; i++) {
		_players.push_back(Player());
		_players[i].playerNumber = i;
		_players[i].initPos();
	}
}

void MainGame::gameLoop() {
	bool shouldContinue = true;
	_musicManager.startMusic(1);
	while (_gameState != GameState::EXIT) {
		float startTicks = _sdlManager.getCurrentFrame();

		processInput();
		if (_gameState > 0) { // In game, dead or alive
			shouldContinue = true;
			if (_gameState < 11) {
				moveComets();
				movePlayers();
				fixCollision();
				shouldContinue = checkPlayers();
				cleanComets();
			}
			drawGame();
			if (isInGame() && !shouldContinue) {//ded
				_gameState = (GameState)((int)_gameState + 10);//bad
			}

			if (isInGame() && MainGame::frameCount % 6 == (_gameStart + 1) % 6) {
				_score++;
			}
		}
		else if (_gameState < 0) { // If in menu
			_score = -1;
			moveComets();
			fixCollision();
			cleanComets();
			drawGame();
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
	SDL_DestroyTexture(Player::playerTexture);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	TTF_CloseFont(_textFont);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	exit(0);
}

void MainGame::processInput() {
	_inputManager.pollInput();
	if (_inputManager.isKeyJustDown(SDLK_f)) {
		_sdlManager.toggleFullScreen();
		restartGame();
	}
	if (_inputManager.isKeyJustDown(SDLK_1)) {
		Constants::PLAYER_COUNT = 1;
		restartGame();
	}
	if (_inputManager.isKeyJustDown(SDLK_2)) {
		Constants::PLAYER_COUNT = 2;
		restartGame();
	}
	if (_inputManager.isKeyJustDown(SDLK_3)) {
		Constants::PLAYER_COUNT = 3;
		restartGame();
	}
	if (_inputManager.isKeyJustDown(SDLK_4)) {
		Constants::PLAYER_COUNT = 4;
		restartGame();
	}

	if (_inputManager.isKeyJustDown(SDLK_ESCAPE)) {
		_gameState = GameState::MENU; // TODO: POP STACK
	}
	else if (evnt.key.keysym.sym == SDLK_ESCAPE && _gameState == GameState::MENU) {
		_gameState = GameState::EXIT;
	}

				break;
			case SDL_MOUSEBUTTONDOWN:
				if (pause) {
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

	

	if (_keysPressed[SDLK_SPACE]) {
		if (pause) {
			restartGame();
		}
	}
	if (_keysPressed[SDLK_RETURN]) {
		_gameState = GameState::PLAY;
	}
}

void MainGame::drawGame() {
	/*Get window surface
	SDL_Surface *screenSurface = SDL_GetWindowSurface(_window);

	// Fill the surface white
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

	// Update the surface
	SDL_UpdateWindowSurface(_window);*/

	Uint8 dimColor = 255;
	if (static_cast<bool>(_gameState)) {
		dimColor = Constants::DIM_COLOR_MENU;
	}
	else if (pause) {
		dimColor = Constants::DIM_COLOR_LOSE;
	}
	SDL_SetTextureColorMod(Star::starTexture, dimColor, dimColor, dimColor);
	SDL_SetTextureColorMod(Comet::cometTexture, dimColor, dimColor, dimColor);

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
		SDL_SetTextureColorMod(Player::playerTexture, Constants::SHIP_COLORS[playerNumber][0], Constants::SHIP_COLORS[playerNumber][1], Constants::SHIP_COLORS[playerNumber][2]);
		SDL_Rect temprect = _playerI->getFixedRect();
		SDL_RenderCopy(_renderer, Player::playerTexture, NULL, &temprect);
	}

	//Score
	if (_score != -1) {
		SDL_Rect scoreRect;
		char scoreCStr[20]; //TODO maybe make this smarter?
							//itoa(_score, scoreCStr, 10);
		sprintf(scoreCStr, "%u", _score);
		SDL_Color textColor;
		textColor.a = 255;
		textColor.r = Constants::TEXT_COLOR[0];
		textColor.g = Constants::TEXT_COLOR[1];
		textColor.b = Constants::TEXT_COLOR[2];
		/*SDL_Surface *textSurface = TTF_RenderText_Solid(_textFont, scoreCStr, textColor);
		if (scoreSurface == nullptr) {
			fatalError("SDL could not load score surface! SDL_Error: " + std::string(SDL_GetError()));
		}
		SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(_renderer, scoreSurface);
		if (scoreTexture == nullptr) {
			fatalError("SDL could not load score texture! SDL_Error: " + std::string(SDL_GetError()));
		}
		scoreRect.w = scoreSurface->w;
		scoreRect.h = scoreSurface->h; DONE BY TTFMANAGER */ 
		
		if (!pause) {
			scoreRect.y = 0;
			scoreRect.x = Constants::SCREEN_WIDTH_CALC - scoreRect.w;
		}
		else { //Center on death
			scoreRect.y = (Constants::SCREEN_HEIGHT_CALC - scoreRect.h) / 2.0;
			scoreRect.x = (Constants::SCREEN_WIDTH_CALC - scoreRect.w) / 2.0;
		}
		
		//SDL_FreeSurface(scoreSurface); DONE BY TTFMANAGER
		SDL_RenderCopy(_renderer, scoreTexture, NULL, &scoreRect);
	}
	else {
		//Menu options:
		//Play:
			//Easy

	}
	
	//std::cout << scoreRect.h << " " << Constants::FONT_SIZE << std::endl;

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
		if (Constants::PLAYER_CONTROLS[playerNumber] != 0) {
			int currentLenX = xMovements.size();
			int currentLenY = yMovements.size();
			if (_keysPressed[Constants::CONTROL_UP[Constants::PLAYER_CONTROLS[playerNumber]]]) {
				yMovements.push_back(1);
			}
			else if (_keysPressed[Constants::CONTROL_DOWN[Constants::PLAYER_CONTROLS[playerNumber]]]) {
				yMovements.push_back(-1);
			}

			if (_keysPressed[Constants::CONTROL_LEFT[Constants::PLAYER_CONTROLS[playerNumber]]]) {
				xMovements.push_back(-1);
			}
			else if (_keysPressed[Constants::CONTROL_RIGHT[Constants::PLAYER_CONTROLS[playerNumber]]]) {
				xMovements.push_back(1);
			}
			if (currentLenX == xMovements.size()) {
				xMovements.push_back(0);
			}
			if (currentLenY == yMovements.size()) {
				yMovements.push_back(0);
			}
		}
		else {
			_playerI->setPixelPos(_mouseX, Constants::SCREEN_HEIGHT_CALC - _mouseY);
			xMovements.push_back(0); //failsafe (should never happen)
			yMovements.push_back(0); //failsafe (should never happen)
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

