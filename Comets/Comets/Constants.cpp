/* Copyright (C) 2016 Matthew Giordano
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#include "stdafx.h"
#include "Constants.h"

 //SDL weirdness
const int Constants::CONSTANT_SDL_CONTROL_NUMBER = 1073741753;

// Screen dimension constants
int Constants::SCREEN_WIDTH = 1024;
int Constants::SCREEN_HEIGHT = 576;
int Constants::SCREEN_WIDTH_CALC = SCREEN_WIDTH - 1;
int Constants::SCREEN_HEIGHT_CALC = SCREEN_HEIGHT - 1;

// Colors
Uint8 Constants::SHIP_COLORS[][3] = {
	{ 220, 0, 255 }, //player 1
	{ 0, 0, 255 }, //player 2
	{ 0, 255, 0 }, //player 3
	{ 255, 0, 0 } //player 4
};
const Uint8 Constants::TEXT_COLOR[] = { 255, 255, 255 };
const Uint8 Constants::DIM_COLOR_MENU = 105;
const Uint8 Constants::DIM_COLOR_LOSE = 105;

// Comet specific stuff
const double Constants::COMET_SPEED_MULTIPLIER_MAX = 1.4;
const double Constants::COMET_SPEED_MULTIPLIER_MIN = 0.6;
const int Constants::COMET_SPAWN_RATE = 6; //every COMET_SPAWN_RATE frames a comet will spawn

// Counts
const int Constants::STAR_COUNT = 30;
const int Constants::COMET_COUNT = 10;
int Constants::PLAYER_COUNT = 2;

// Time stuffs
const int Constants::STAR_MAX_NONTWINKLE_TIME = 5 * 60;  // Frames
const int Constants::STAR_TWINKLE_TIME = 20;  // Frames

// Comet size
const int Constants::COMET_SIZE = 9;
const int Constants::STAR_SIZE = 2;
const int Constants::STAR_SIZE_TWINKLE = 3;
const int Constants::PLAYER_SIZE = 4;

// Speed
const int Constants::COMET_SPEED = 1;  // pix-units

// Texture files
const char *Constants::COMET_TEXTURE = "resources/comet.bmp";
const char *Constants::STAR_TEXTURE = "resources/star.bmp";
const char *Constants::FONT_PATH = "resources/open-sans/OpenSans-Regular.ttf";

// Font files
const char *Constants::PLAYER_TEXTURE = "resources/bettership4.bmp";

// Music files
const char *Constants::MUSIC_MENU = "";
const char *Constants::MUSIC_EASY = "resources/music/easy.wav";
const char *Constants::MUSIC_MEDIUM = "";
const char *Constants::MUSIC_HARD = "";
const char *Constants::MUSIC_CRAZY = "";
const char *Constants::MUSIC_INSANE = "";
const char *Constants::MUSIC_ACTUALLY_IMPOSSIBLE = "";

//Controls
const int Constants::CONTROL_UP[] = { -1, SDLK_w, SDLK_j, SDLK_UP - CONSTANT_SDL_CONTROL_NUMBER };
const int Constants::CONTROL_LEFT[] = { -1, SDLK_a, SDLK_k, SDLK_LEFT - CONSTANT_SDL_CONTROL_NUMBER };
const int Constants::CONTROL_DOWN[] = { -1, SDLK_s, SDLK_h, SDLK_DOWN - CONSTANT_SDL_CONTROL_NUMBER };
const int Constants::CONTROL_RIGHT[] = { -1, SDLK_d, SDLK_l, SDLK_RIGHT - CONSTANT_SDL_CONTROL_NUMBER };
int Constants::PLAYER_CONTROLS[] = { 0, 1, 3, 2 }; // Player 2 gets WASD, player 3 gets arrows, player 4 gets hjkl

//Size thingo
const double Constants::STATIC_FONT_SIZE = 50000.0;
double Constants::FONT_SIZE = STATIC_FONT_SIZE / SCREEN_HEIGHT;

void Constants::setScreenSize(int w, int h) {
	SCREEN_WIDTH = w;
	SCREEN_WIDTH_CALC = SCREEN_WIDTH - 1;
	SCREEN_HEIGHT = h;
	SCREEN_HEIGHT_CALC = SCREEN_HEIGHT - 1;
	FONT_SIZE = STATIC_FONT_SIZE / static_cast<double>(SCREEN_HEIGHT);
}
void Constants::changeShipColors(int ship, int rgb, int newColor) {
	SHIP_COLORS[ship][rgb] = newColor;
}
void Constants::changeNumberOfPlayers(int newNumber) {
	PLAYER_COUNT = newNumber;
}
void Constants::changeControls(int player, int newControls) {
	//i want player player to have controls newControls
	int i;
	for (i = 0; i < 4; i++) {
		if (PLAYER_CONTROLS[i] == newControls) { 
			break;
		}
	}
	int temp = PLAYER_CONTROLS[player];
	PLAYER_CONTROLS[player] = newControls;
	PLAYER_CONTROLS[i] = temp;
}
