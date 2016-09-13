/* Copyright (C) 2016 Matthew Pipie
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
		void moveStuff();
		void makeComets();
		void makeStars();
		void loadTextures();
		void fixCollision();
		void cleanComets();
		void makeComet();

		SDL_Window *_window;
		SDL_Renderer *_renderer;
		int _maxFPS;
		GameState _gameState;
		std::vector<Comet> _comets;
		std::vector<Comet>::iterator _cometI;
		std::vector<Star> _stars;
		std::vector<Star>::iterator _starI;
		// std::vector<Sprite> _sprites;
		// std::vector<Sprite>::iterator _spriteI;
};
