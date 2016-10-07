#pragma once
#include "stdafx.h"
#include <SDL_mixer.h>
#include "Constants.h"
class MusicManager
{
public:
	MusicManager();
	~MusicManager();
	void initMusic(); //start
	void loadMusic(); //call at loading
	void unloadMusic(); //call at death of game
	void quitMusic(); //end

	void startMusic(int difficulty); //pass in 0-6, use only when loading from main menu, 0=main menu
	void pauseMusic(); //use on death
	void resumeMusic(); //use on restart
	void stopMusic(); //use on back to main menu

private:
	Mix_Music **difficultyToMusic(int difficulty);

	Mix_Music *_menu;
	Mix_Music *_easy;
	Mix_Music *_medium;
	Mix_Music *_hard;
	Mix_Music *_crazy;
	Mix_Music *_insane;
	Mix_Music *_actuallyImpossible;

};

