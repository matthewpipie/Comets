#pragma once
#include "stdafx.h"
#include "FontManager.h"
class SDLManager
{
public:
	SDLManager();
	~SDLManager();
	static int totalFrames;
	SDL_Window *mainWindow;
	SDL_Renderer *mainRenderer;
	FontManager fontManager;
	InputManager inputManager;
	
private:
	int fullscreenMode;
};

