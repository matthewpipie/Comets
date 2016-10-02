/* Copyright (C) 2016 Matthew Giordano
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#include "stdafx.h"
#include "Constants.h"

// Screen dimension constants
int Constants::SCREEN_WIDTH = 1024;
int Constants::SCREEN_HEIGHT = 576;
int Constants::SCREEN_WIDTH_CALC = SCREEN_WIDTH - 1;
int Constants::SCREEN_HEIGHT_CALC = SCREEN_HEIGHT - 1;

// Comet specific stuff
const double Constants::COMET_SPEED_MULTIPLIER_MAX = 1.4;
const double Constants::COMET_SPEED_MULTIPLIER_MIN = 0.6;
const int Constants::COMET_SPAWN_RATE = 4; //every COMET_SPAWN_RATE frames a comet will spawn

// Cou qnts
const int Constants::STAR_COUNT = 30;
const int Constants::COMET_COUNT = 20;
const int Constants::PLAYER_COUNT = 1;

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

// Files
const char *Constants::COMET_TEXTURE = "resources/comet.bmp";
const char *Constants::STAR_TEXTURE = "resources/star.bmp";
const char *Constants::PLAYER_TEXTURE = "resources/ship.bmp";
