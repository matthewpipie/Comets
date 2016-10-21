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
			void moveComet();
			void modifyTrueAngle(double xSpeed, double ySpeed, double collisionAngle, double initSpeed, double altSpeed); // OLD
			void setSpeed(double newSpeed);
			double getSpeed();
			void resolveCollision(Comet &resolveComet);
			double getXSpeed();
			double getYSpeed();
			double getFrameSpeed();
			double getRadAngle();
			void setAngle(double angle);

			static SDL_Texture *cometTexture;
			static void initCometTexture(SDL_Renderer *rend);

		private:
			void setCollision(Comet *comet1, Comet *comet2);
			double _initDegree;  // 0-359
			double _speed;
	};
