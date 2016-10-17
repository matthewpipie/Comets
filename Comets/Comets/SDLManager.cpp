#include "SDLManager.h"
#include "Errors.h"


SDLManager::SDLManager() :
	_mainWindow(nullptr),
	_mainRenderer(nullptr),
	_fullscreenMode(0) {

}


SDLManager::~SDLManager()
{
}

void SDLManager::start() {
	initSDL();
	initWindow();
	initRenderer();
	loadTextures();
	loadMusic();
}

void SDLManager::initSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fatalError("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
	}
	SDL_GL_SetSwapInterval(0); //Disable V-Sync
	SDL_ShowCursor(0);
	_fontManager.init();
	//_inputManager.init();
	_musicManager.init();
	_resourceManager.init();
}

void SDLManager::initWindow() {
	const char *title = Constants::GAME_NAME + std::string(" v").c_str + Constants::GAME_VERSION;
	_mainWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (_mainWindow == nullptr) {
		fatalError("SDL Window could not initialize! SDL_Error: " + std::string(SDL_GetError()));
	}
}

void SDLManager::initRenderer() {
	_mainRenderer = SDL_CreateRenderer(_mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (_mainRenderer == nullptr) {
		SDL_DestroyWindow(_mainWindow);
		fatalError("SDL Renderer could not initialize! SDL_Error: " + std::string(SDL_GetError()));
	}
	SDL_SetRenderDrawColor(_mainRenderer, 0, 0, 0, 255);
}

void SDLManager::loadTextures() {
	_resourceManager.loadTextures();
}
void SDLManager::loadMusic() {
	_musicManager.loadMusic();
}