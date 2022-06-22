#include "CrossPlatformInput.h"

CrossPlatformInput* CrossPlatformInput::InputPtr;

CrossPlatformInput::CrossPlatformInput()
{
#if _PS4
	InputBoi = new PS4_InputManager;
#else
	InputBoi = new InputManager;
#endif

	InputPtr = this;
}

CrossPlatformInput::~CrossPlatformInput()
{
	delete InputBoi;
}

float CrossPlatformInput::GetAxisValue(ControllerAxis axis)
{
	return InputBoi->GetAxisValue(axis);
}

bool CrossPlatformInput::GetButtonDown(ControllerButtons button)
{
	return InputBoi->GetButtonDown(button);
}

bool CrossPlatformInput::GetControllerConnected()
{
	return InputBoi->IsController();
}

void CrossPlatformInput::UpdateInputBoi()
{
	InputBoi->UpdateInput();
}
