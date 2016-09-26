/* Copyright (C) 2016 Matthew Giordano
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#include "stdafx.h"
#include "MainGame.h"

int main(int argc, char *args[]) {
	//srand(time(NULL));
	srand(0);
	MainGame mainGame;
	mainGame.run();
	return 0;
}
