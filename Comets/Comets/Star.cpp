/* Copyright (C) 2016 Matthew Giordano
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#include <string>
#include "stdafx.h"
#include "Star.h"
#include "Constants.h"
#include "MainGame.h"
#include "Errors.h"

SDL_Texture *Star::starTexture = nullptr;

Star::Star() : Sprite(Constants::STAR_TEXTURE), _isTwinkling(false), _actionFrame(-1) {}

Star::~Star() {}

void Star::initStarTexture(SDL_Renderer *rend) {
	starTexture = IMG_LoadTexture(rend, Constants::STAR_TEXTURE);
	/* std::cout << "Star image has been loaded: " << std::endl; */
	if (starTexture == nullptr) {
		// SDL_DestroyTexture(texture);
		fatalError("Failed to load image (star)!  SDL_Error: " + std::string(SDL_GetError()));
	}
}

void Star::initStar(SDL_Renderer *rend) {
	makeNewActionFrame();
	setAttributes(static_cast<double>(rand() % 101),
		static_cast<double>(rand() % 101),
		static_cast<double>(Constants::STAR_SIZE),
		static_cast<double>(Constants::STAR_SIZE));
	// initTexture(rend);
	/* std::cout << "New star created!  X:" << getX() << " Y: " << getY() << " W: " << getW() << " H: " << getH() << std::endl; */
}

void Star::twinkle() {
	if (MainGame::frameCount >= _actionFrame) {
		if (_isTwinkling) {
			setSize(static_cast<double>(Constants::STAR_SIZE),
					static_cast<double>(Constants::STAR_SIZE));
			_isTwinkling = false;
			makeNewActionFrame();
		} else {
			setSize(static_cast<double>(Constants::STAR_SIZE_TWINKLE),
					static_cast<double>(Constants::STAR_SIZE_TWINKLE));
			_isTwinkling = true;
			_actionFrame = Constants::STAR_TWINKLE_TIME + MainGame::frameCount;
		}
	}
}

void Star::makeNewActionFrame() {
	_actionFrame = (rand() % Constants::STAR_MAX_NONTWINKLE_TIME) + MainGame::frameCount;
}
