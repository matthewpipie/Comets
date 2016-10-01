/* Copyright (C) 2016 Matthew Giordano
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#pragma once
#include "Sprite.h"
class Star :
	public Sprite {
		public:
			Star();
			~Star();
			void twinkle();
			void initStar();
			static SDL_Texture *starTexture;
			static void initStarTexture(SDL_Renderer *rend);
		private:
			void makeNewActionFrame();
			int _actionFrame;
			bool _isTwinkling;
	};
