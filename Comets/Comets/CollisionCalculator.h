/* Copyright (C) 2016 Matthew Pipie
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#pragma once
#include "Comet.h"
class CollisionCalculator {
	public:
		CollisionCalculator(Comet *comet1, Comet *comet2);
		~CollisionCalculator();
		double getFinalX();
		double getFinalY();
		double getSwappedX();
		double getSwappedY();
		double getCollisionAngle();
	private:
		double calculate(Comet *comet1, Comet *comet2, std::function<double(double)> func);
		Comet *_comet1;
		Comet *_comet2;
};
