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

class MainGame {
	public:
		MainGame();
		~MainGame();
		void run();
		static int frameCount;
		bool pause;

	private:
		void gameLoop();
		void processInput();
		void drawGame();
		void initSDL();
		void makeWindow();
		void makeRenderer();
		void moveComets();
		void movePlayers();
		void makeComets();
		void makeStars();
		void makePlayers();
		void loadTextures();
		void fixCollision();
		void cleanComets();
		void makeComet();
		bool checkPlayers();
		void restartGame();

		bool _keysPressed[323];
		int _mouseX;
		int _mouseY;
		SDL_Window *_window;
		SDL_Renderer *_renderer;
		int _maxFPS;
		GameState _gameState;
		std::vector<Player> _players;
		std::vector<Player>::iterator _playerI;
		std::vector<Comet> _comets;
		std::vector<Comet>::iterator _cometI;
		std::vector<Star> _stars;
		std::vector<Star>::iterator _starI;
		int fullscreenMode;
		// std::vector<Sprite> _sprites;
		// std::vector<Sprite>::iterator _spriteI;
};
