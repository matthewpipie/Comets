#include "MusicManager.h"
#include "Errors.h"


MusicManager::MusicManager() :
	_menu(nullptr),
	_easy(nullptr),
	_medium(nullptr),
	_hard(nullptr),
	_crazy(nullptr),
	_insane(nullptr),
	_actuallyImpossible(nullptr),
	_currentlyPlaying(nullptr) {
}


MusicManager::~MusicManager() {
	quitMusic();
}

void MusicManager::initMusic() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		fatalError("SDL_mixer could not initialize! SDL_mixer Error: " + std::string(Mix_GetError()));
	}
}

void MusicManager::loadMusic() {
	_menu = Mix_LoadMUS(Constants::MUSIC_MENU);
	_easy = Mix_LoadMUS(Constants::MUSIC_EASY);
	_medium = Mix_LoadMUS(Constants::MUSIC_MEDIUM);
	_hard = Mix_LoadMUS(Constants::MUSIC_HARD);
	_crazy = Mix_LoadMUS(Constants::MUSIC_CRAZY);
	_insane = Mix_LoadMUS(Constants::MUSIC_INSANE);
	_actuallyImpossible = Mix_LoadMUS(Constants::MUSIC_ACTUALLY_IMPOSSIBLE);
}

void MusicManager::unloadMusic() {
	if (_menu != nullptr) {
		Mix_FreeMusic(_menu);
		_menu = nullptr;
	}
	if (_easy != nullptr) {
		Mix_FreeMusic(_easy);
		_easy = nullptr;
	}
	if (_medium != nullptr) {
		Mix_FreeMusic(_medium);
		_medium = nullptr;
	}
	if (_hard != nullptr) {
		Mix_FreeMusic(_hard);
		_hard = nullptr;
	}
	if (_crazy != nullptr) {
		Mix_FreeMusic(_crazy);
		_crazy = nullptr;
	}
	if (_insane != nullptr) {
		Mix_FreeMusic(_insane);
		_insane = nullptr;
	}
	if (_actuallyImpossible != nullptr) {
		Mix_FreeMusic(_actuallyImpossible);
		_actuallyImpossible = nullptr;
	}
}

void MusicManager::quitMusic() {
	Mix_Quit();
}

void MusicManager::startMusic(int gameState, bool forceRestart) {
	if (forceRestart) {
		Mix_HaltMusic();
	}
	//setCurrentlyPlaying(gameState);

	Mix_Music **musicPointer = gameStateToMusic(gameState);

	if ((musicPointer == _currentlyPlaying && !forceRestart && musicPointer != nullptr)) {
		return;
	}
	_currentlyPlaying = musicPointer;
	Mix_PlayMusic(*musicPointer, -1);
}

void MusicManager::pauseMusic() {
	Mix_PauseMusic();
}

void MusicManager::resumeMusic() {
	Mix_ResumeMusic();
}

void MusicManager::stopMusic() {
	Mix_HaltMusic();
}

Mix_Music **MusicManager::gameStateToMusic(GameState gameState) {
	auto errorOut = [](GameState gameState) {fatalError("gameState could not be found by MusicManager!  gameState: " + gameState); };
	int newState = (int)gameState;
	if (gameState == GameState::EXIT) {
		errorOut(gameState);
	}
	else if ((int)gameState < 0) { // In menu
		newState = 0;
	}
	else if (gameState > 10) { //paused
		newState -= 10;
	}

	switch (newState) {
	case 0:
		return &_menu;
		break;
	case 1:
		return &_easy;
		break;
	case 2:
		return &_medium;
		break;
	case 3:
		return &_hard;
		break;
	case 4:
		return &_crazy;
		break;
	case 5:
		return &_insane;
		break;
	case 6:
		return &_actuallyImpossible;
		break;
	default:
		errorOut(gameState);
	}
}
