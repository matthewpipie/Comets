/* Copyright (C) 2016 Matthew Giordano
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#include <string>
#include <utility>
#include "stdafx.h"
#include "Comet.h"
#include "CollisionCalculator.h"
#include "Constants.h"
#include "Errors.h"
#include "RNGCalculator.h"

SDL_Texture *Comet::cometTexture = nullptr;

Comet::Comet() :
	Sprite(),
	_initDegree(0),
	_speed(1),
	isAlive(true) {}


Comet::~Comet() {}

void Comet::initCometTexture(SDL_Renderer *rend) { // Static method
	cometTexture = IMG_LoadTexture(rend, Constants::COMET_TEXTURE);
	std::cout << "Comet image has been loaded: " << std::endl;
	if (cometTexture == nullptr) {
		// SDL_DestroyTexture(texture);
		fatalError("Failed to load image (comet)!  SDL_Error: " + std::string(SDL_GetError()));
	}
}

void Comet::initPos() {
	setSize(Constants::COMET_SIZE, Constants::COMET_SIZE);
	_initPos = RNGCalculator::randomDouble(0, 100);
	//TODO: Make _initPos a scope variable
	// _initDegree = (rand() % 179) + 1;
	_initSide = (Side)(rand() % 4);

	_speed = RNGCalculator::randomDouble(Constants::COMET_SPEED_MULTIPLIER_MAX, Constants::COMET_SPEED_MULTIPLIER_MIN);
	//_speed = RNGCalculator(0.5, 1.5);
	// switch
	/* if side is 0, setPos(_initPos, 0)
	if 1, setPos(100, _initPos)
	if 2, setPos(_initPos, 100)
	if 3, setPos(0, _initPos)*/

	switch ((int)_initSide) {
		case 0:
			setPos(_initPos, 100.0);
			_initDegree = RNGCalculator::randomDouble(180.0, 360.0);
			break;
		case 1:
			setPos(100.0, _initPos);
			_initDegree = RNGCalculator::randomDouble(90.0, 270.0);
			break;
		case 2:
			setPos(_initPos, 0.0);
			_initDegree = RNGCalculator::randomDouble(0.0, 180.0);
			break;
		case 3:
			setPos(0.0, _initPos);
			_initDegree = RNGCalculator::randomDouble(270.0, 450.0);
			break;
		default:
			fatalError("Failed to set position!");
	}
}

void Comet::moveComet(bool isBack) {
	double xMovement;
	double yMovement;

	if (!isBack) {
		/*if (_isOut && (_x < 0 || _x > Constants::SCREEN_WIDTH || _y < 0 || _y > Constants::SCREEN_HEIGHT)) { // IS TRIGGERING AND IT SHUDNT BE
			isAlive = false;
			return;
		}
		if (!_isOut && (_x > 0 && _x < Constants::SCREEN_WIDTH && _y > 0 && _y < Constants::SCREEN_HEIGHT)) {
			_isOut = true;
		}*/
		if (getX() < -getW() || getX() > Constants::SCREEN_WIDTH + getW() || getY() < -getH() || getY() > Constants::SCREEN_HEIGHT + getH()) {
			isAlive = false;
			return;
		}
		xMovement = static_cast<double>(Constants::COMET_SPEED) * getXSpeed() * getSpeed();
		yMovement = static_cast<double>(Constants::COMET_SPEED) * getYSpeed() * getSpeed();
	} else {
		//TODO
		// std::cout << "initial thigo!" << std::endl;
		switch (_initSide) {
		case Side::TOP:
			xMovement = 0;
			yMovement = (-0.6 * getW())
				/ (.01 * static_cast<double>(Constants::SCREEN_HEIGHT_CALC));
			break;
		case Side::RIGHT:
			xMovement = (0.6 * getH())
				/ (.01 * static_cast<double>(Constants::SCREEN_WIDTH_CALC));
			yMovement = 0;
			break;
		case Side::BOTTOM:
			xMovement = 0;
			yMovement = (0.6 * getW())
				/ (.01 * static_cast<double>(Constants::SCREEN_HEIGHT_CALC));
			break;
		case Side::LEFT:
			xMovement = (-0.6 * getH())
				/ (.01 * static_cast<double>(Constants::SCREEN_WIDTH_CALC));
			yMovement = 0;
			break;
		default:
			fatalError("Failed to read position!");
		}
	}

	move(xMovement, yMovement);

	/*if (isBack) {
		std::cout << "init: moving comet x:" << _x << " y: " << _y << std::endl;

	}*/
}

bool Comet::isColliding(Comet *testComet) {



	double distanceBetweenCometsSquared = std::pow(getX() - testComet->getX(), 2.0) + std::pow(getY() - testComet->getY(), 2.0);
	double maxCollisionDistanceSquared = std::pow(getR() + testComet->getR(), 2.0);

	// std::cout << maxCollisionDistanceSquared << " " << distanceBetweenCometsSquared << std::endl;

	if (distanceBetweenCometsSquared <= maxCollisionDistanceSquared) {
		return true;
	}
	return false;
}

void Comet::resolveCollision(Comet *resolveComet) {
	CollisionCalculator collision(this, resolveComet);
	double finalX1 = collision.getFinalX();
	double finalY1 = collision.getFinalY();
	double finalX2 = collision.getSwappedX();
	double finalY2 = collision.getSwappedY();
	double speedMP1 = getSpeed();
	double speedMP2 = resolveComet->getSpeed();
	double angle = collision.getCollisionAngle();

	// std::cout << speedMP1 << " " << speedMP2 << std::endl;

	modifyTrueAngle(finalX1, finalY1, angle, speedMP1, speedMP2);
	resolveComet->modifyTrueAngle(finalX2, finalY2, angle, speedMP2, speedMP1);

	/*double tempMP = resolveComet->getSpeed();
	resolveComet->setSpeed(getSpeed());
	setSpeed(tempMP);*/
}

void Comet::setSpeed(double newSpeed) {
	_speed = newSpeed;
	// std::cout << "setting speed to " << newMP << std::endl;
}

double Comet::getSpeed() {
	return _speed;
}

void Comet::modifyTrueAngle(double xSpeed, double ySpeed, double collisionAngle, double initSpeed, double altSpeed) {
	double angle = atan(ySpeed / xSpeed) * 180.0 / M_PI;
	if (angle < 180) {
		_initSide = Side::BOTTOM;
	} else {
		_initSide = Side::TOP;
	}

	// std::cout << altSpeed << " " << collisionAngle << "/" << collisionAngle * 180.0 / M_PI << " " << initSpeed << std::endl;

	_initDegree = 180.0 - angle;
	setSpeed(std::pow(std::sin(collisionAngle), 2) * initSpeed + std::pow(std::cos(collisionAngle), 2) * altSpeed);
}

double Comet::getR() {
	return (getW() + getH()) / 4.0;
}

double Comet::getXSpeed() {
	return std::cos(static_cast<double>(_initDegree) * M_PI / 180.0);
}

double Comet::getYSpeed() {
	return std::sin(static_cast<double>(_initDegree) * M_PI / 180.0);
}

int Comet::getRealAngle() {
	return _initDegree;
}

double Comet::getFrameSpeed() {
	return sqrt(std::pow(getXSpeed(), 2.0) + std::pow(getYSpeed(), 2.0));
}
