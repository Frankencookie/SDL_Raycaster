#include "InputBase.h"

bool InputBase::GetButtonDown(ControllerButtons Button)
{
	return ControllerButtonsDown[Button];
}

float InputBase::GetAxisValue(ControllerAxis Axis)
{
	return ControllerAxisValues[Axis];
}

void InputBase::UpdateInput()
{
	
}

bool InputBase::IsController()
{
	return Connected;
}
