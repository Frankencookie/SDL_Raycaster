#include "CrossPlatformInput.h"

CrossPlatformInput* CrossPlatformInput::InputPtr;

CrossPlatformInput::CrossPlatformInput()
{
#if _PS4
	Input = new PS4_InputManager;
#else
	Input = new InputManager;
#endif

	InputPtr = this;
}

CrossPlatformInput::~CrossPlatformInput()
{
	delete Input;
}

float CrossPlatformInput::GetAxisValue(ControllerAxis axis)
{
	return Input->GetAxisValue(axis);
}

bool CrossPlatformInput::GetButtonDown(ControllerButtons button)
{
	return Input->GetButtonDown(button);
}

bool CrossPlatformInput::GetControllerConnected()
{
	return Input->IsController();
}

void CrossPlatformInput::UpdateInput()
{
	Input->UpdateInput();
}
