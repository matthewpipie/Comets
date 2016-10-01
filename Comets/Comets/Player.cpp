/* Copyright (C) 2016 Matthew Giordano
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#include "stdafx.h"
#include "Player.h"
#include "Constants.h"
#include "Errors.h"

SDL_Texture *Player::playerTexture = nullptr;

Player::Player() : Sprite() {}

Player::~Player() {}

void Player::initPlayerTexture(SDL_Renderer *rend) { // Static method
	playerTexture = IMG_LoadTexture(rend, Constants::PLAYER_TEXTURE);
	std::cout << "Comet image has been loaded: " << std::endl;
	if (playerTexture == nullptr) {
		// SDL_DestroyTexture(texture);
		fatalError("Failed to load image (comet)!  SDL_Error: " + std::string(SDL_GetError()));
	}
}

void Player::initPos() {
	setSize(Constants::PLAYER_SIZE, Constants::PLAYER_SIZE);
}

void Player::movePlayer(double x, double y) {
	setPixelPos(x, y);
}
void Player::resolveCollision() {
	setAlive(false);
	std::cout << "set ded" << std::endl;
}