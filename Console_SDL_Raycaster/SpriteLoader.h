#pragma once
#if !_PS4
#include <SDL.h>
#include <SDL_image.h>
#include "Renderer_SDL.h"
#endif

#include <vector>
#include <string>
#include "Helpers.h"

class SpriteLoader
{
public:
	SpriteLoader();
	~SpriteLoader();
private:
	std::vector<Sprite*> SpriteList;

public:
	//Load sprite from hdd and add to list
	Sprite* LoadSprite(std::string address = "Assets/missingTexture.bmp", std::string SName = "Unnamed", bool sheet = false);

	//Retrieve sprite from list
	Sprite* GetSprite(std::string textureToGet = "Unnamed", bool IsAddress = false);

	//Static Pointer
	static SpriteLoader* SpriteLoaderPtr;
};
