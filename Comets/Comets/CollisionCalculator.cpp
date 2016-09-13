/* Copyright (C) 2016 Matthew Pipie
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#include "stdafx.h"
#include "CollisionCalculator.h"

CollisionCalculator::CollisionCalculator(Comet *comet1, Comet *comet2) {
	_comet1 = comet1;
	_comet2 = comet2;
}


CollisionCalculator::~CollisionCalculator() {}

double CollisionCalculator::getFinalX() {
	return calculate(_comet1, _comet2, [](double d) {return cos(d); });
}
double CollisionCalculator::getFinalY() {
	return calculate(_comet1, _comet2, [](double d) {return sin(d); });
}
double CollisionCalculator::getSwappedX() {
	return calculate(_comet2, _comet1, [](double d) {return cos(d); });
}
double CollisionCalculator::getSwappedY() {
	return calculate(_comet2, _comet1, [](double d) {return sin(d); });
}

double CollisionCalculator::getCollisionAngle() {
	return atan((_comet1->getY() - _comet2->getY())
		/ (_comet1->getX() - _comet2->getX()));
}

double CollisionCalculator::calculate(Comet *comet1, Comet *comet2, std::function<double(double)> func) {
	double comet1XSpeedInit = comet1->getXSpeed();
	double comet1YSpeedInit = comet1->getYSpeed();
	double comet1ScalarSpeed = comet1->getSpeed();
	double comet1Mass = comet1->getR();
	int comet1Angle = comet1->getRealAngle();
	double comet2XSpeedInit = comet2->getXSpeed();
	double comet2YSpeedInit = comet2->getYSpeed();
	double comet2ScalarSpeed = comet2->getSpeed();
	double comet2Mass = comet2->getR();
	int comet2Angle = comet2->getRealAngle();

	//double collisionPointX = ((getX() * resolveComet->getR()) + (resolveComet->getX() * getR())) / (getR() + resolveComet->getR());
	//double collisionPointY = ((getY() * resolveComet->getR()) + (resolveComet->getY() * getR())) / (getR() + resolveComet->getR());

	double collisionAngle = getCollisionAngle();

	return ((comet1ScalarSpeed
			* cos(static_cast<double>(comet1Angle) - collisionAngle)
			* (comet1Mass - comet2Mass) + (2 * comet2Mass * comet2ScalarSpeed
			* cos(static_cast<double>(comet2Angle) - collisionAngle)))
			/ (comet1Mass + comet2Mass)) * func(collisionAngle)
			+ (comet1ScalarSpeed * sin(static_cast<double>(comet1Angle)
			- collisionAngle) * func(static_cast<double>(collisionAngle) + M_PI / 2));
}
