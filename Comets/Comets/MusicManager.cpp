#include "MusicManager.h"
#include "Errors.h"


MusicManager::MusicManager() :
	_menu(nullptr),
	_easy(nullptr),
	_medium(nullptr),
	_hard(nullptr),
	_crazy(nullptr),
	_insane(nullptr),
	_actuallyImpossible(nullptr) {
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
	_easy = Mix_LoadMUS(Constants::MUSIC_EASY);
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

void MusicManager::startMusic(int difficulty) {
	Mix_HaltMusic();
	Mix_Music **musicPointer = difficultyToMusic(difficulty);
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

Mix_Music **MusicManager::difficultyToMusic(int difficulty) {
	switch (difficulty) {
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
		fatalError("Difficulty could not be found!  Difficulty: " + difficulty);
	}
}