#include "InputManager.h"
#include "Constants.h"


InputManager::InputManager() :
	_quit(false),
	_mouseX(0),
	_mouseY(0),
	_mouseDown(KeyState::KEY_UP) {
	std::fill(_keysDown, _keysDown + sizeof(_keysDown), 0);
}


InputManager::~InputManager()
{
}

bool InputManager::isKeyDown(int key) {
	rectifyKey(key);
	if ((bool)_keysDown[key]) {
		return true;
	}
	return false;
}

bool InputManager::isKeyJustDown(int key) {
	rectifyKey(key);
	if (_keysDown[key] == KeyState::KEY_JUST_DOWN) {
		return true;
	}
	return false;
}

void InputManager::pollInput() {
	setButtonsDown();

	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_quit = true;
			break;
		case SDL_KEYDOWN:
			int key = evnt.key.keysym.sym;
			rectifyKey(key);
			if (_keysDown[key] == KeyState::KEY_UP) {
				_keysDown[key] = KeyState::KEY_JUST_DOWN;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (_mouseDown == KeyState::KEY_UP) {
				_mouseDown = KeyState::KEY_JUST_DOWN;
			}
			break;
		case SDL_KEYUP:
			int key = evnt.key.keysym.sym;
			rectifyKey(key);
			_keysDown[key] = KeyState::KEY_UP;
			break;
		case SDL_MOUSEMOTION:
			_mouseX = evnt.motion.x;
			_mouseY = evnt.motion.y;
			break;
		}
	}
}

int InputManager::rectifyKey(int &key) {
	if (key > 127) {
		key -= Constants::CONSTANT_SDL_CONTROL_NUMBER;
	}
}

void InputManager::setButtonsDown() {
	for (int i = 0; i < numberOfKeys; ++i) {
		if (_keysDown[i] == KeyState::KEY_JUST_DOWN) {
			_keysDown[i] = KeyState::KEY_DOWN;
		}
	}
	if (_mouseDown == KeyState::KEY_JUST_DOWN) {
		_mouseDown = KeyState::KEY_DOWN;
	}
}

bool InputManager::isMouseDown() {
	if ((bool)_mouseDown) {
		return true;
	}
	return false;
}

bool InputManager::isMouseJustDown() {
	if (_mouseDown == KeyState::KEY_JUST_DOWN) {
		return true;
	}
	return false;
}

int InputManager::getMouseX() {
	return _mouseX;
}
int InputManager::getMouseY() {
	return _mouseY;
}
bool InputManager::shouldQuit() {
	return _quit;
}