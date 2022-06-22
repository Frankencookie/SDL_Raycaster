#include "MessageWindow.h"


void MessageWindow::ControllerUnplugged()
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Well this is awkward", "Controller Unplugged", NULL);
}

void MessageWindow::ControllerNotFound()
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Well this is awkward", "Controller Not Found", NULL);
}

void MessageWindow::GameClosed()
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, ":(", "Bye Bye", NULL);
}

void MessageWindow::CustomWarningMessage(std::string message)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Warning", message.c_str(), NULL);
}

