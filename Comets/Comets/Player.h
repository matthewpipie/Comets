/* Copyright (C) 2016 Matthew Giordano
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#pragma once
#include "Sprite.h"
#include "Comet.h"

class Player :
	public Sprite {
		public:
			Player();
			~Player();
			void initPos();
			void resolveCollision();
			void movePlayer(double x, double y);
			int playerNumber;
			static SDL_Texture *playerTexture;
			static void initPlayerTexture(SDL_Renderer *rend);
		private:
	};
