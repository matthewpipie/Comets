/* Copyright (C) 2016 Matthew Giordano
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#pragma once
enum class GameState {
	EXIT                      = 0,
	MENU_MAIN                 = -1,
	MENU_DIFFICULTIES         = -2,
	MENU_OPTIONS              = -3,
	MENU_CREDITS              = -4,
	EASY                      = 1, 
	MEDIUM, //2
	HARD, //3
	CRAZY, //4
	INSANE, //5
	ACTUALLY_IMPOSSIBLE, //6
	EASY_PAUSE                = 11,
	MEDIUM_PAUSE, //12
	HARD_PAUSE, //13
	CRAZY_PAUSE, //14
	INSANE_PAUSE, //15
	ACTUALLY_IMPOSSIBLE_PAUSE //16
};
