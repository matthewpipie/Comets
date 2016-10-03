/* Copyright (C) 2016 Matthew Giordano
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#include <utility>
#include <string>
#include "stdafx.h"
#include "Sprite.h"
#include "Constants.h"
#include "Errors.h"

Sprite::Sprite() : _texture(nullptr), _x(0.0), _y(0.0), _w(0.0), _h(0.0) {
	_rect.x = 0;
	_rect.y = 0;
	_rect.w = 0;
	_rect.h = 0;
}
Sprite::Sprite(const char *path) {
	Sprite();
	_path = path;
}

Sprite::~Sprite() {
	if (_texture != nullptr) {
		SDL_DestroyTexture(_texture);
	}
}

void Sprite::initTexture(SDL_Renderer *rend) {
	_texture = IMG_LoadTexture(rend, _path);
	/* std::cout << "Sprite has been created: " << _path << std::endl; */
	if (_texture == nullptr) {
		// SDL_DestroyTexture(texture);
		fatalError("Failed to load image!  SDL_Error: " + std::string(SDL_GetError()));
	}
}

void Sprite::querySize() {
	SDL_QueryTexture(_texture, NULL, NULL, &_rect.w, &_rect.h);
}

void Sprite::setAttributes(double x, double y, double w, double h) {
	setPixelAttributes(x * .01
	* static_cast<double>(Constants::SCREEN_WIDTH_CALC), y * .01
	* static_cast<double>(Constants::SCREEN_HEIGHT_CALC), w * .01
	* static_cast<double>(Constants::SCREEN_HEIGHT_CALC), h * .01
	* static_cast<double>(Constants::SCREEN_HEIGHT_CALC));
}

void Sprite::setPixelAttributes(double x, double y, double w, double h) {
	_x = x;
	_y = y;
	_w = w;
	_h = h;
}

void Sprite::setPixelPos(double x, double y) {
	// std::cout << "Setting stuff to x:" << x << " y: " << y << std::endl;
	setPixelAttributes(x, y, getW(), getH());
}

void Sprite::setMiddlePixelPos(double x, double y) {
	setPixelPos(x - getW() / 2, y - getH() / 2);
}

void Sprite::movePixel(double x, double y) {
	setPixelPos(x + getX(), y + getY());
}

void Sprite::move(double x, double y) {
	setPixelPos(x * .01 * static_cast<double>(Constants::SCREEN_WIDTH_CALC)
	+ getX(), y * .01 * static_cast<double>(Constants::SCREEN_HEIGHT_CALC) + getY());
}

void Sprite::setPos(double x, double y) {
	setPixelPos(x * .01 * static_cast<double>(Constants::SCREEN_WIDTH_CALC), y
	* .01 * static_cast<double>(Constants::SCREEN_HEIGHT_CALC));
}
void Sprite::setPercentX(double x) {
	setPos(x, getPercentY());
}
void Sprite::setPercentY(double y) {
	setPos(getPercentX(), y);
}

void Sprite::setSize(double w, double h) {
	setPixelAttributes(getX(), getY(), w * .01
	* static_cast<double>(Constants::SCREEN_HEIGHT_CALC), h * .01
	* static_cast<double>(Constants::SCREEN_HEIGHT_CALC));
}

void Sprite::fixRect() {
	_rect.x = getX() - getW() / 2.0;
	_rect.y = static_cast<double>(Constants::SCREEN_HEIGHT_CALC) - (getY() + getH() / 2.0);
	_rect.h = getH();
	_rect.w = getW();
}

SDL_Rect Sprite::getRect() {
	return _rect;
}

SDL_Texture *Sprite::getTexture() {
	return _texture;
}

double Sprite::getX() {
	return _x;
}
double Sprite::getPercentX() {
	return _x / (.01 * static_cast<double>(Constants::SCREEN_WIDTH_CALC));
}

double Sprite::getY() {
	return _y;
}
double Sprite::getPercentY() {
	return _y / (.01 * static_cast<double>(Constants::SCREEN_HEIGHT_CALC));
}

double Sprite::getW() {
	return _w;
}

double Sprite::getH() {
	return _h;
}

double Sprite::getR() {
	return (getW() + getH()) / 4.0;
}

bool Sprite::isAlive() {
	return _alive;
}
void Sprite::setAlive(bool newAlive) {
	_alive = newAlive;
	//std::cout << "set dedaefasdf" << std::endl;
	//std::cout << newAlive << std::endl;

}

SDL_Rect Sprite::getFixedRect() {
	fixRect();
	return getRect();
}

bool Sprite::isColliding(Sprite *testComet) {

	if (!isAlive() || !testComet->isAlive()) {
		return false;
	}

	double distanceBetweenCometsSquared = std::pow(getX() - testComet->getX(), 2.0) + std::pow(getY() - testComet->getY(), 2.0);
	double maxCollisionDistanceSquared = std::pow(getR() + testComet->getR(), 2.0);

	//std::cout << maxCollisionDistanceSquared << " " << distanceBetweenCometsSquared << std::endl;

	bool areColliding = distanceBetweenCometsSquared <= maxCollisionDistanceSquared;

	if (areColliding) {
		//std::cout << "collision!" << std::endl;
		return true;
	}
	return false;
}