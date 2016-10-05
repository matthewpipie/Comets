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
		//SDL weirdness
		static const int CONSTANT_SDL_CONTROL_NUMBER;
		
		// Screen dimension "constants"
		static int SCREEN_WIDTH;
		static int SCREEN_HEIGHT;
		static int SCREEN_WIDTH_CALC;
		static int SCREEN_HEIGHT_CALC;

		// Colors
		static Uint8 SHIP_COLORS[4][3];
		static const Uint8 TEXT_COLOR[3];
		static const Uint8 DIM_COLOR_MENU;
		static const Uint8 DIM_COLOR_LOSE;

		// Multipliers
		static const double COMET_SPEED_MULTIPLIER_MAX;
		static const double COMET_SPEED_MULTIPLIER_MIN;
		static const int COMET_SPAWN_RATE;

		// Counts
		static const int STAR_COUNT;
		static const int COMET_COUNT;
		static int PLAYER_COUNT;

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
		static const char *FONT_PATH;

		//Controls
		static const int CONTROL_UP[4];
		static const int CONTROL_LEFT[4];
		static const int CONTROL_DOWN[4];
		static const int CONTROL_RIGHT[4];
		static int PLAYER_CONTROLS[4];

		//Size thingo
		static const double STATIC_FONT_SIZE;
		static double FONT_SIZE;
		
		static void setScreenSize(int w, int h);
		static void changeShipColors(int ship, int rgb, int newColor);
		static void changeNumberOfPlayers(int newNumber);
		static void changeControls(int player, int newControls);
};
