#pragma once
#include "Helpers.h"
#include <vector>

class Renderer_Interface
{
public:
	Renderer_Interface();
	~Renderer_Interface();

protected:
	///WINDOW PROPERTIES
	const int initX = 100;			//Initial Window X Position
	const int initY = 100;			//Initial Window Y Position

	const int initWindowWidth = 960;	//Initial Window Width
	const int initWindowHeight = 720;	//Initial Window Height

	int Midpoint;

	//How Tall to draw each line
	std::vector<float> LineHeights;

	//Calculate Height From Distance
	int CalculateHeight(int lineNumber);

public:
	//Print buffer to screen
	virtual void PrintToScreen();
	//Render Sprite at location
	virtual void DrawSprite(Sprite* spriteToDraw, float SpriteScale, Vector2D destRectPos, float spriteNumber = 0);
	//Draw Text To Screen
	virtual void DrawText(std::string Text, Vector2D TextPosition, float TextRectScale);
	//Draw World
	virtual void DrawBackground();

	//Get Distance Information
	void SetCameraData(std::vector<float>& heights);
	int GetScreenWidth() { return initWindowWidth; }
	int GetMidpoint() { return Midpoint; }

	

	static Renderer_Interface* RendererInterfacePtr;
};
