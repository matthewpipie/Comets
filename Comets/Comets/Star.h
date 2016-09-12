#pragma once
#include "Sprite.h"
class Star :
	public Sprite
{
public:
	Star();
	~Star();
	void twinkle();
	void initStar(SDL_Renderer *rend);
	static SDL_Texture *starTexture;
	static void initStarTexture(SDL_Renderer *rend);
private:
	void makeNewActionFrame();
	int _actionFrame;
	bool _isTwinkling;
};

