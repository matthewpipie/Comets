/* Copyright (C) 2016 Matthew Giordano
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#pragma once
#include <vector>
#include "Constants.h"
#include "GameState.h"
#include "Sprite.h"
#include "Comet.h"
#include "Star.h"
#include "Player.h"
#include "MenuManager.h"
#include "MusicManager.h"
#include "InputManager.h"

class MainGame {
	public:
		MainGame();
		~MainGame();
		void run();
		static int frameCount;

	private:
		void gameLoop();
		void processInput();
		void drawGame();
		void initSDL();
		void initFont();
		void initMusic();
		void makeWindow();
		void makeRenderer();
		void makeMenus();
		void moveComets();
		void movePlayers();
		void makeComets();
		void makeStars();
		void makePlayers();
		void loadTextures();
		void loadMusic();
		void fixCollision();
		void cleanComets();
		void makeComet();
		bool checkPlayers();
		void startGame(int difficulty); // 1-6
		void restartGame();
		void pauseGame();
		void resumeGame();
		void endGame();
		bool isInGame();

		MenuManager _menuManager;
		MusicManager _musicManager;
		InputManager _inputManager;
		SDLManager _sdlManager;
		ResourceManager _resourceManager;
		
		int _score;
		int _gameStart;
		int _maxFPS;
		GameState _gameState;
		// std::vector<Sprite> _sprites;
		// std::vector<Sprite>::iterator _spriteI;
};
