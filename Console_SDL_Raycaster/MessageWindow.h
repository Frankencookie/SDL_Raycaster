#pragma once
#include <SDL.h>
#include <string>

class MessageWindow
{
public:
	static void ControllerUnplugged();
	static void ControllerNotFound();
	static void GameClosed();
	static void CustomWarningMessage(std::string message = "Hehe");
};

