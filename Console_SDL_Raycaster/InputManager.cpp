#include "InputManager.h"

//InputManager* InputManager::InputPtr;

InputManager::InputManager()
{
	SDL_Init(SDL_INIT_GAMECONTROLLER);

	for (int i = 0; i < SDL_NumJoysticks(); ++i)
	{
		if (SDL_IsGameController(i))
		{
			MainGamepad = SDL_GameControllerOpen(i);
			if (MainGamepad) 
			{
				printf("Gamepad Found :) \n");
				Connected = true;
				break;
			}
			else 
			{
				printf("Gamepad failed to open. Error: %s\n", SDL_GetError());
			}
		}
	}

	if (MainGamepad)
	{
		for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++)
		{
			ControllerButtonsDown[i] = NULL;
		}
	}
	else
	{
		MessageWindow::ControllerNotFound();
	}
	//InputPtr = this;
}

InputManager::~InputManager()
{
	SDL_GameControllerClose(MainGamepad);
}

void InputManager::UpdateInput()
{
	while (SDL_PollEvent(&InputEvent))
	{
		switch (InputEvent.type)
		{
			//Is it Keyboard?
			case SDL_KEYDOWN:
				break;
			//Controller button down?
			case SDL_CONTROLLERBUTTONDOWN:
				ControllerButtonsDown[InputEvent.cbutton.button] = true;
				break;
			//Controller Button Released?
			case SDL_CONTROLLERBUTTONUP:
				ControllerButtonsDown[InputEvent.cbutton.button] = false;
				break;

			//Controller Stick Moved?
			case SDL_CONTROLLERAXISMOTION:
				ControllerAxisValues[InputEvent.caxis.axis] = InputEvent.caxis.value;
				break;

			//Controller Removed?
			case SDL_CONTROLLERDEVICEREMOVED:
				printf("Controller Removed \n");
				SDL_GameControllerClose(MainGamepad);
				MainGamepad = NULL;
				Connected = false;

				//Display Warning
				MessageWindow::ControllerUnplugged();
				break;

			//Controller Plugged in? Ignore if there's already a controller.
			case SDL_CONTROLLERDEVICEADDED:
				if (!MainGamepad)
				{
					MainGamepad = SDL_GameControllerOpen(InputEvent.cdevice.which);
					printf("Controller Plugged In \n");
					Connected = true;
				}
				break;
		}
	}
}
