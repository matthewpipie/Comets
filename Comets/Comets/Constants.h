/* Copyright (C) 2016 Matthew Giordano
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#pragma once
class Constants {
	public:
		// Screen dimension constants
		static const int SCREEN_WIDTH;
		static const int SCREEN_HEIGHT;
		static const int SCREEN_WIDTH_CALC;
		static const int SCREEN_HEIGHT_CALC;

		// Multipliers
		static const double COMET_SPEED_MULTIPLIER_MAX;
		static const double COMET_SPEED_MULTIPLIER_MIN;

		// Counts
		static const int STAR_COUNT;
		static const int COMET_COUNT;
		static const int PLAYER_COUNT;

		// Time stuffs
		static const int STAR_MAX_NONTWINKLE_TIME;  // Frames
		static const int STAR_TWINKLE_TIME;  // Frames

		// Comet size
		static const int COMET_SIZE;
		static const int STAR_SIZE;
		static const int STAR_SIZE_TWINKLE;
		static const int PLAYER_SIZE;

		// Speed
		static const int COMET_SPEED;

		// Files
		static const char *COMET_TEXTURE;
		static const char *STAR_TEXTURE;
		static const char *PLAYER_TEXTURE;
};
