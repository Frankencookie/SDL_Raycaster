#pragma once

enum ControllerButtons
{
	CB_INVALID = -1,
	CB_BOTTOM,
	CB_RIGHT,
	CB_LEFT,
	CB_TOP,
	CB_BACK,
	CB_GUIDE,
	CB_START,
	CB_LEFTSTICK,
	CB_RIGHTSTICK,
	CB_LEFTSHOULDER,
	CB_RIGHTSHOULDER,
	CB_DPAD_UP,
	CB_DPAD_DOWN,
	CB_DPAD_LEFT,
	CB_DPAD_RIGHT,
	CB_NUMBER
};

enum ControllerAxis
{
	CA_INVALID = -1,
	CA_LEFTX,
	CA_LEFTY,
	CA_RIGHTX,
	CA_RIGHTY,
	CA_TRIGGERLEFT,
	CA_TRIGGERRIGHT,
	CA_NUMBER
};

class InputBase
{
protected:
	bool ControllerButtonsDown[CB_NUMBER];
	float ControllerAxisValues[CA_NUMBER];

	bool Connected = false;

public:
	bool GetButtonDown(ControllerButtons Button);
	float GetAxisValue(ControllerAxis Axis);

	virtual void UpdateInput();

	bool IsController();
};