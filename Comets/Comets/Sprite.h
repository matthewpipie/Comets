/* Copyright (C) 2016 Matthew Giordano
 * You may use, distribute, and modify this code under the
 * terms of the GPL license.
 *
 * You should have recieved a copy of the GPL license with
 * this file. If not, please visit https://github.com/matthewpipie/Comets
 */
#pragma once
#include <SDL2/SDL_image.h>
#include <utility>

class Sprite {
	public:
		explicit Sprite(const char *path);
		Sprite();
		~Sprite();
		void initTexture(SDL_Renderer *rend);
		void setAttributes(double x, double y, double w, double h);
		void setPixelAttributes(double x, double y, double w, double h);
		void setPixelPos(double x, double y);
		void setMiddlePixelPos(double x, double y);
		void movePixel(double x, double y);
		void move(double x, double y);  // relative move
		void setPos(double x, double y);  // absolute move
		void setSize(double w, double h);
		void fixRect();
		void querySize();
		SDL_Rect getRect();
		SDL_Texture *getTexture();
		double getX();
		double getY();
		double getW();
		double getH();

	private:
		SDL_Texture *_texture;
		SDL_Rect _rect;
		double _x;
		double _y;
		double _w;
		double _h;
		const char *_path;
};
