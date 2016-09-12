#pragma once
#include "Sprite.h"
#include "Side.h"

class Comet :
	public Sprite
{
public:
	Comet();
	~Comet();
	void initPos();
	void moveComet(bool isBack = false);
	bool isAlive;
	void modifyTrueAngle(double xSpeed, double ySpeed);
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
	int _initPos; //0-100
	int _initDegree; //1-179
	double _speedMultiplier;
	Side _initSide;
};

