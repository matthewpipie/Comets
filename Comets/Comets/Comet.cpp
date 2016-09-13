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

SDL_Texture *Comet::cometTexture = nullptr;

Comet::Comet() :
	Sprite(Constants::STAR_TEXTURE),
	_initPos(0),
	_initDegree(0),
	_speedMultiplier(1),
	_initSide(Side::TOP),
	isAlive(true) {}


Comet::~Comet() {}

void Comet::initCometTexture(SDL_Renderer *rend) {
	cometTexture = IMG_LoadTexture(rend, Constants::COMET_TEXTURE);
	std::cout << "Comet image has been loaded: " << std::endl;
	if (cometTexture == nullptr) {
		// SDL_DestroyTexture(texture);
		fatalError("Failed to load image (comet)!  SDL_Error: " + std::string(SDL_GetError()));
	}
}

void Comet::initPos() {
	setSize(Constants::COMET_SIZE, Constants::COMET_SIZE);
	isAlive = true;
	_initPos = static_cast<double>(rand() % 101);
	_initDegree = (rand() % 179) + 1;
	_initSide = (Side)(rand() % 4);
	_speedMultiplier = (Constants::COMET_SPEED_MULTIPLIER_MAX
		- Constants::COMET_SPEED_MULTIPLIER_MIN)
		* (static_cast<double>(rand()) / static_cast<double>(RAND_MAX))
		+ Constants::COMET_SPEED_MULTIPLIER_MIN;

	// switch
	/* if side is 0, setPos(_initPos, 0)
	if 1, setPos(100, _initPos)
	if 2, setPos(_initPos, 100)
	if 3, setPos(0, _initPos)*/

	switch (static_cast<int>(_initSide)) {
		case 0:
			setPos(_initPos, 0.0);
			break;
		case 1:
			setPos(100.0, _initPos);
			break;
		case 2:
			setPos(_initPos, 100.0);
			break;
		case 3:
			setPos(0, _initPos);
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
		xMovement = static_cast<double>(Constants::COMET_SPEED) * getXSpeed() * getSpeedMP();
		yMovement = static_cast<double>(Constants::COMET_SPEED) * getYSpeed() * getSpeedMP();
	} else {
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
	double distanceBetweenCometsSquared = pow(getX() - testComet->getX(), 2.0) + pow(getY() - testComet->getY(), 2.0);
	double maxCollisionDistanceSquared = pow(getR() + testComet->getR(), 2.0);

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
	double speedMP1 = getSpeedMP();
	double speedMP2 = resolveComet->getSpeedMP();
	double angle = collision.getCollisionAngle();

	modifyTrueAngle(finalX1, finalY1, angle, speedMP1, speedMP2);
	resolveComet->modifyTrueAngle(finalX2, finalY2, angle, speedMP2, speedMP1);

	/*double tempMP = resolveComet->getSpeedMP();
	resolveComet->setSpeedMP(getSpeedMP());
	setSpeedMP(tempMP);*/
}

void Comet::setSpeedMP(double newMP) {
	_speedMultiplier = newMP;
	std::cout << "setting speed to " << newMP << std::endl;
}

double Comet::getSpeedMP() {
	return _speedMultiplier;
}

void Comet::modifyTrueAngle(double xSpeed, double ySpeed, double collisionAngle, double initSpeed, double altSpeed) {
	double angle = atan(ySpeed / xSpeed) * 180.0 / M_PI;
	if (angle < 180) {
		_initSide = Side::BOTTOM;
	} else {
		_initSide = Side::TOP;
	}

	std::cout << altSpeed << " " << collisionAngle * 180.0 / M_PI << " " << initSpeed << std::endl;

	_initDegree = 180.0 - angle;
	setSpeedMP(abs(std::sin(collisionAngle) * initSpeed) + abs(std::cos(collisionAngle) * altSpeed));
}

double Comet::getR() {
	return (getW() + getH()) / 4.0;
}

double Comet::getXSpeed() {
	double xSpeed;
	switch (_initSide) {
	case Side::TOP:
		xSpeed = std::cos(static_cast<double>(_initDegree) * M_PI / 180.0);
		break;
	case Side::RIGHT:
		xSpeed = -1.0 * std::sin(static_cast<double>(_initDegree) * M_PI / 180.0);
		break;
	case Side::BOTTOM:
		xSpeed = -1.0 * std::cos(static_cast<double>(_initDegree) * M_PI / 180.0);
		break;
	case Side::LEFT:
		xSpeed = std::sin(static_cast<double>(_initDegree) * M_PI / 180.0);
		break;
	default:
		fatalError("Failed to read position!");
	}
	return xSpeed;
}

double Comet::getYSpeed() {
	double ySpeed;
	switch(_initSide) {
	case Side::TOP:
		ySpeed = std::sin(static_cast<double>(_initDegree) * M_PI / 180.0);
		break;
	case Side::RIGHT:
		ySpeed = std::cos(static_cast<double>(_initDegree) * M_PI / 180.0);
		break;
	case Side::BOTTOM:
		ySpeed = -1.0 * std::sin(static_cast<double>(_initDegree) * M_PI / 180.0);
		break;
	case Side::LEFT:
		ySpeed = -1.0 * std::cos(static_cast<double>(_initDegree) * M_PI / 180.0);
		break;
	default:
		fatalError("Failed to read position!");
	}
	return ySpeed;
}

int Comet::getRealAngle() {
	int degree = 0;
	switch (_initSide) {
	case Side::TOP:
		degree = -_initDegree;
		break;
	case Side::RIGHT:
		degree = 270 - _initDegree;
		break;
	case Side::BOTTOM:
		degree = 180 - _initDegree;
		break;
	case Side::LEFT:
		degree = 90 - _initDegree;
		break;
	default:
		fatalError("Failed to read position!");
	}
	return degree;
}

double Comet::getSpeed() {
	return sqrt(pow(getXSpeed(), 2.0) + pow(getYSpeed(), 2.0));
}
