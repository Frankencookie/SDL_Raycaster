#include "CrossPlatformRenderManager.h"

CrossPlatformRenderManager::CrossPlatformRenderManager()
{
	//If Not PS4 mode, create sdl renderer
#if !_PS4
	Renderer = new Renderer_SDL;
#else
	Renderer = //PS4 renderer here
#endif
}

CrossPlatformRenderManager::~CrossPlatformRenderManager()
{
	delete Renderer;
	Renderer = nullptr;
}
