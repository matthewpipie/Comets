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
#include "Constants.h"
#include "Errors.h"
#include "RNGCalculator.h"
#include "CollisionCalculator.h"

SDL_Texture *Comet::cometTexture = nullptr;

Comet::Comet() :
	Sprite(),
	_initDegree(0),
	_speed(1) {}


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
	double initPos = RNGCalculator::randomDouble(0, 100);

	_speed = RNGCalculator::randomDouble(Constants::COMET_SPEED_MULTIPLIER_MAX, Constants::COMET_SPEED_MULTIPLIER_MIN);
	//_speed = RNGCalculator(0.5, 1.5);
	// switch
	/* if side is 0, setPos(_initPos, 0)
	if 1, setPos(100, _initPos)
	if 2, setPos(_initPos, 100)
	if 3, setPos(0, _initPos)*/

	double xMovement = 0;
	double yMovement = 0;

	switch (rand() % 4) {
		case 0:
			setPos(initPos, 100.0);
			_initDegree = RNGCalculator::randomDouble(180.0, 360.0);
			yMovement = (0.6 * getH())
				/ (.01 * static_cast<double>(Constants::SCREEN_HEIGHT_CALC));
			break;
		case 1:
			setPos(100.0, initPos);
			_initDegree = RNGCalculator::randomDouble(90.0, 270.0);
			xMovement = (0.6 * getW())
				/ (.01 * static_cast<double>(Constants::SCREEN_WIDTH_CALC));
			break;
		case 2:
			setPos(initPos, 0.0);
			_initDegree = RNGCalculator::randomDouble(0.0, 180.0);
			yMovement = (-0.6 * getH())
				/ (.01 * static_cast<double>(Constants::SCREEN_HEIGHT_CALC));
			break;
		case 3:
			setPos(0.0, initPos);
			_initDegree = RNGCalculator::randomDouble(270.0, 450.0);
			xMovement = (-0.6 * getW())
				/ (.01 * static_cast<double>(Constants::SCREEN_WIDTH_CALC));
			break;
		default:
			fatalError("Failed to set position!");
	}
	move(xMovement, yMovement);
}

void Comet::moveComet() {
	double xMovement;
	double yMovement;

		/*if (_isOut && (_x < 0 || _x > Constants::SCREEN_WIDTH || _y < 0 || _y > Constants::SCREEN_HEIGHT)) { // IS TRIGGERING AND IT SHUDNT BE
			isAlive = false;
			return;
		}
		if (!_isOut && (_x > 0 && _x < Constants::SCREEN_WIDTH && _y > 0 && _y < Constants::SCREEN_HEIGHT)) {
			_isOut = true;
		}*/
		if (getX() < -getW() || getX() > Constants::SCREEN_WIDTH + getW() || getY() < -getH() || getY() > Constants::SCREEN_HEIGHT + getH()) {
			setAlive(false);
			return;
		}
		xMovement = static_cast<double>(Constants::COMET_SPEED) * getXSpeed() * getSpeed();
		yMovement = static_cast<double>(Constants::COMET_SPEED) * getYSpeed() * getSpeed();

	move(xMovement, yMovement);

	/*if (isBack) {
		std::cout << "init: moving comet x:" << _x << " y: " << _y << std::endl;

	}*/
}

void Comet::resolveCollision(Comet *resolveComet) {

	double totalSpeed = getSpeed() + resolveComet->getSpeed();
	double xDist = getPercentX() - resolveComet->getPercentX();
	double yDist = getPercentY() - resolveComet->getPercentY();
	double distance = std::sqrt(std::pow(xDist, 2.0) + std::pow(yDist, 2.0));
	CollisionCalculator tempColl(this, resolveComet);
	double collisionAngle = tempColl.getCollisionAngle();

	double intersectingSpace = getR() + resolveComet->getR() - distance;
	double xTotalIntersect = intersectingSpace * std::cos(collisionAngle);
	double yTotalIntersect = intersectingSpace * std::sin(collisionAngle);
	//TODO: determine which one to move negative?
	//move(-xDist * (getSpeed() / totalSpeed), 3.0);

	Comet temp = *this;

	setCollision(this, resolveComet);

	resolveComet->setCollision(resolveComet, &temp);


	//while (isColliding(resolveComet)) { //TODO: make this not make comets move a lot more than they should when they collide badly
		moveComet();
		resolveComet->moveComet();
	//}

}

void Comet::setCollision(Comet *comet1, Comet *comet2) {
	CollisionCalculator collision(comet1, comet2);
	//std::cout << "oldspeed: " << getSpeed() << " oldangle: " << _initDegree << std::endl;
	setSpeed(collision.getFinalSpeed());
	setAngle(collision.getFinalAngle() * 180.0 / M_PI);
	//std::cout << "newspeed: " << getSpeed() << " newangle: " << _initDegree << std::endl;

}


void Comet::setSpeed(double newSpeed) {
	_speed = newSpeed;
	// std::cout << "setting speed to " << newMP << std::endl;
}

double Comet::getSpeed() {
	return _speed;
}

void Comet::modifyTrueAngle(double xSpeed, double ySpeed, double collisionAngle, double initSpeed, double altSpeed) { // OLD
	double angle = atan(ySpeed / xSpeed) * 180.0 / M_PI;

	// std::cout << altSpeed << " " << collisionAngle << "/" << collisionAngle * 180.0 / M_PI << " " << initSpeed << std::endl;

	_initDegree = 180.0 - angle;
	setSpeed(std::pow(std::sin(collisionAngle), 2) * initSpeed + std::pow(std::cos(collisionAngle), 2) * altSpeed);
}

double Comet::getXSpeed() {
	return std::cos(static_cast<double>(_initDegree) * M_PI / 180.0);
}

double Comet::getYSpeed() {
	return std::sin(static_cast<double>(_initDegree) * M_PI / 180.0);
}

double Comet::getRadAngle() {
	return _initDegree * M_PI / 180;
}

double Comet::getFrameSpeed() {
	return sqrt(std::pow(getXSpeed(), 2.0) + std::pow(getYSpeed(), 2.0));
}

void Comet::setAngle(double angle) {
	//std::cout << "setting angle to " << angle << std::endl;
	_initDegree = angle;
}