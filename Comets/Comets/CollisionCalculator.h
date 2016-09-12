#pragma once
#include "Comet.h"
class CollisionCalculator
{
public:
	CollisionCalculator(Comet *comet1, Comet *comet2);
	~CollisionCalculator();
	double getFinalX();
	double getFinalY();
	double getSwappedX();
	double getSwappedY();
private:
	double calculate(Comet *comet1, Comet *comet2, std::function<double(double)> func);
	Comet *_comet1;
	Comet *_comet2;
};

