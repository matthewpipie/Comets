/* Copyright (C) 2016 Matthew Pipie
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#include "stdafx.h"
#include "Constants.h"

// Screen dimension constants
const int Constants::SCREEN_WIDTH = 1024;
const int Constants::SCREEN_HEIGHT = 768;
const int Constants::SCREEN_WIDTH_CALC = SCREEN_WIDTH - 1;
const int Constants::SCREEN_HEIGHT_CALC = SCREEN_HEIGHT - 1;

// Multipliers
const double Constants::COMET_SPEED_MULTIPLIER_MAX = 1.3;
const double Constants::COMET_SPEED_MULTIPLIER_MIN = 0.6;

// Cou qnts
const int Constants::STAR_COUNT = 30;
const int Constants::COMET_COUNT = 30;

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
