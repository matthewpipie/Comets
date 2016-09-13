/* Copyright (C) 2016 Matthew Giordano
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#include <string>
#include "stdafx.h"
#include "Errors.h"

// Prints out an error message and exits the game
void fatalError(std::string errorString) {
	/* std::cout << errorString << std::endl; */
	/* std::cout << "Enter any key to quit..."; */
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(69);
}
