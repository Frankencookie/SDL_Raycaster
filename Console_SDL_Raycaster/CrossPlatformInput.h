#pragma once
#include "InputManager.h"
#include "InputBase.h"

class CrossPlatformInput
{
public:
	CrossPlatformInput();
	~CrossPlatformInput();
private:
	bool ControllerButtonsDown[CB_NUMBER];
	float ControllerAxisValues[CA_NUMBER];
	bool ControllerConnected = false;

	//SHOULD WE USE PS4 STUFF OR SDL2?
	const bool PS4 = false;

	InputBase* InputBoi;

public:
	//Data
	static CrossPlatformInput* InputPtr;
	float GetAxisValue(ControllerAxis axis);
	bool GetButtonDown(ControllerButtons button);
	bool GetControllerConnected();

	//Call every frame
	void UpdateInputBoi();
};