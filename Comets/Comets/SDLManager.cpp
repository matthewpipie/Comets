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

void SDLManager::init() {
	initSDL();
	initWindow();
	initRenderer();
	loadTextures();
	loadMusic();
}

Uint32 SDLManager::getCurrentFrame() {
	return SDL_GetTicks();
}

void SDLManager::sleep(Uint32 ms) {
	SDL_Delay(ms);
}

void SDLManager::toggleFullScreen() {
	_fullscreenMode = !_fullscreenMode;
	SDL_SetWindowFullscreen(_mainWindow, _fullscreenMode == 0 ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
	SDL_RenderPresent(_mainRenderer);
	int h, w;
	SDL_GetRendererOutputSize(_mainRenderer, &w, &h);
	//std::cout << w << " " << h << std::endl;
	Constants::setScreenSize(w, h);
	_fontManager.resetFontSize();
}

void SDLManager::quit() {
	_resourceManager.quit(); //free textures and IMG_Quit()
	_fontManager.quit(); //TTF_Quit() & closefont
	if (_mainRenderer != nullptr) {
		SDL_DestroyRenderer(_mainRenderer);
	}
	if (_mainWindow != nullptr) {
		SDL_DestroyWindow(_mainWindow);
	}
	SDL_Quit();
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

