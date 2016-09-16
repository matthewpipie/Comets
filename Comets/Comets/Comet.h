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
			void setSpeed(double newSpeed);
			double getSpeed();
			bool isColliding(Comet *testComet);
			void resolveCollision(Comet *resolveComet);
			double getR();
			double getXSpeed();
			double getYSpeed();
			double getFrameSpeed();
			int getRealAngle();

			static SDL_Texture *cometTexture;
			static void initCometTexture(SDL_Renderer *rend);

		private:
			int _initDegree;  // 0-359
			double _speed;
			Side _initSide;
			double _initPos;
	};
