// MegaMetro.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MainGame.h"



int main(int argc, char *args[]) {
	srand(time(NULL));
	MainGame mainGame;
	mainGame.run();
	return 0;
}

