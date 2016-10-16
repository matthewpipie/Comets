#pragma once
#include "stdafx.h"
#include "FontManager.h"
#include "InputManager.h"
class SDLManager
{
public:
	SDLManager();
	~SDLManager();
	static int totalFrames;

private:
	SDL_Window *_mainWindow;
	SDL_Renderer *_mainRenderer;
	FontManager _fontManager;
	InputManager _inputManager;
	
	int _fullscreenMode;
};

