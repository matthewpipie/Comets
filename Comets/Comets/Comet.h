/* Copyright (C) 2016 Matthew Giordano
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#pragma once
#include "Sprite.h"
#include "Side.h"

class Comet :
	public Sprite {
		public:
			Comet();
			~Comet();
			void initPos();
			void moveComet(bool isBack = false);
			bool isAlive;
			void modifyTrueAngle(double xSpeed, double ySpeed, double collisionAngle, double initSpeed, double altSpeed);
			void setSpeedMP(double newMP);
			double getSpeedMP();
			bool isColliding(Comet *testComet);
			void resolveCollision(Comet *resolveComet);
			double getR();
			double getXSpeed();
			double getYSpeed();
			double getSpeed();
			int getRealAngle();

			static SDL_Texture *cometTexture;
			static void initCometTexture(SDL_Renderer *rend);

		private:
			int _initPos;  // 0-100
			int _initDegree;  // 1-179
			double _speedMultiplier;
			Side _initSide;
	};
