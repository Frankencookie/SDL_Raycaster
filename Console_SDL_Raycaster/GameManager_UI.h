#pragma once
#include "Helpers.h"
#include "Renderer_Interface.h"
#include "SpriteLoader.h"
#include "EntityLooper.h"

class GameManager_UI
{
public:
	GameManager_UI();
private:
	Renderer_Interface* RendererBoi;
	//SpriteLoader* SpriteLoadBoi;
	Sprite* UiSprite;

	int PlayerHealth = 100;
	int PlayerScore = 0;
	float GameTime = 0;
	int Fps = 0;

	Vector2D UiLocation;
	Vector2D FpsLocation;
	Vector2D TimeLocation;

	EntityLooper* LooperBoi;

public:
	void DrawUI();
};

