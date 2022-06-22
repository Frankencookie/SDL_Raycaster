#pragma once
#include <SDL.h>
#include <stdio.h>
#include "MessageWindow.h"
#include "InputBase.h"

class InputManager : public InputBase
{
public:
	InputManager();
	~InputManager();

protected:
	SDL_GameController* MainGamepad = NULL;
	SDL_Event InputEvent;

public:
	void UpdateInput();

	bool GetControllerConnected();
	

	//static InputManager* InputPtr;
};

