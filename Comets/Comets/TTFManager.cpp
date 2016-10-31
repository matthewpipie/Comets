#include "TTFManager.h"
#include "Errors.h"
#include "Constants.h"

TTFManager::TTFManager() : _mainFont(nullptr)
{
}


TTFManager::~TTFManager()
{
}

void TTFManager::init() {
	if (TTF_Init() < 0) {
		fatalError("SDL TTF could not initialize! TTF_Error: " + std::string(TTF_GetError()));
	}
	resetFont();
}

void TTFManager::resetFont() {
	if (_mainFont != nullptr) {
		TTF_CloseFont(_mainFont);
	}
	_mainFont = TTF_OpenFont(Constants::FONT_PATH, Constants::FONT_SIZE);
	if (_mainFont == nullptr) {
		fatalError("SDL TTF could not find the font! TTF_Error: " + std::string(TTF_GetError()));
	}
}

void TTFManager::getTextureFromText(char *cStr, SDL_Color textColor, SDL_Renderer *renderer, SDL_Texture *textureToBeFilled, SDL_Rect *textRectToBeFilled) {
	SDL_Surface *textSurface = getSurfaceFromText(cStr, textColor);
	textRectToBeFilled->w = textSurface->w;
	textRectToBeFilled->h = textSurface->h;

	textureToBeFilled = nullptr;
	textureToBeFilled = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (textureToBeFilled == nullptr) {
		fatalError("SDL could not load score texture! SDL_Error: " + std::string(SDL_GetError()));
	}
	SDL_FreeSurface(textSurface);
}


void TTFManager::quit() {
	if (_mainFont != nullptr) {
		TTF_CloseFont(_mainFont);
	}
	TTF_Quit();
}

SDL_Surface *TTFManager::getSurfaceFromText(char *cStr, SDL_Color textColor) {
	SDL_Surface *textSurface = nullptr;
	textSurface = TTF_RenderText_Solid(_mainFont, cStr, textColor);
	if (textSurface == nullptr) {
		fatalError("SDL could not load text surface! SDL_Error: " + std::string(SDL_GetError()));
	}
}