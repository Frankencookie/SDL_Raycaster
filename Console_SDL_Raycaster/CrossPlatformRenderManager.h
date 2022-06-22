#pragma once
#include "Renderer_Interface.h"

//If not PS4 mode, load sdl renderer
#if !_PS4
#include "Renderer_SDL.h"
#else
//PS4 Renderer Here
#endif

class CrossPlatformRenderManager
{
public:
	CrossPlatformRenderManager();
	~CrossPlatformRenderManager();
	Renderer_Interface* Renderer;
};

