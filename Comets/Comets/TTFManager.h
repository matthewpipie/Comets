#pragma once
#include "stdafx.h"
class TTFManager
{
public:
	TTFManager();
	~TTFManager();

	void init();
	void resetFont();

	void getTextureFromText(char *cStr, SDL_Color textColor, SDL_Renderer *renderer, SDL_Texture *textureToBeFilled, SDL_Rect *textRectToBeFilled);

	void quit();

private:
	SDL_Surface *getSurfaceFromText(char *cStr, SDL_Color textColor);

	TTF_Font *_mainFont;
};

