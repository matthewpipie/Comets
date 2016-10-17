#pragma once
#include "stdafx.h"
#include "FontManager.h"
#include "InputManager.h"
#include "MusicManager.h"
#include "ResourceManager.h"
class SDLManager
{
public:
	SDLManager();
	~SDLManager();
	static int totalFrames;
	void init();

	Uint32 getCurrentFrame();
	void sleep(Uint32 ms);
	void toggleFullScreen();
	void drawGame();

	void quit();

private:

	void initSDL();
	void initWindow();
	void initRenderer();
	void loadTextures();
	void loadMusic();

	SDL_Window *_mainWindow;
	SDL_Renderer *_mainRenderer;
	FontManager _fontManager;
	InputManager _inputManager;
	MusicManager _musicManager;
	ResourceManager _resourceManager;
	
	int _fullscreenMode;
};

