#pragma once
#include "stdafx.h"

enum class KeyState {KEY_UP, KEY_DOWN, KEY_JUST_DOWN};
const int numberOfKeys = 323;

class InputManager
{
public:
	InputManager();
	~InputManager();
	bool isKeyDown(int key);
	bool isKeyJustDown(int key);
	bool isMouseDown();
	bool isMouseJustDown();
	int getMouseX();
	int getMouseY();
	void pollInput();
	bool shouldQuit();
private:

	bool _quit;
	int _mouseX;
	int _mouseY;
	KeyState _mouseDown;
	KeyState _keysDown[numberOfKeys];

	int rectifyKey(int &key);
	void setButtonsDown();
};

