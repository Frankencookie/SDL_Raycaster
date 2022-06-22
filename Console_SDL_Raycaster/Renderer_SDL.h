#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <assert.h>
#include <stdio.h>
#include <vector>
#include "Helpers.h"
#include "Renderer_Interface.h"

class Renderer_SDL : public Renderer_Interface
{
public:
	Renderer_SDL();
	~Renderer_SDL();

protected:
	///Variables for rendering
	//Middle of the screen, on Y axis.
	//int Midpoint;

	/*
	//How tall to draw each line
	std::vector<float> LineHeights;
	*/

	SDL_DisplayMode displayMode;

	///Window And Renderer Pointers
	SDL_Window*		Window_Ptr;		//Pointer to main window
	SDL_Renderer*	Renderer_Ptr;	//Pointer to SDL's Renderer

	//Icon
	SDL_Surface* WindowIcon;

	//The Ground
	SDL_Rect groundColour;

	//Default Font
	TTF_Font* DefaultFont;

	//Colours
	SDL_Color White = { 255,255,255 };
	SDL_Color Black = { 0,0,0 };
	SDL_Color Red = { 255, 0, 0 };

public:
	///Functions to return window and renderer pointers
	SDL_Window*		GetWindowPtr()		{ return Window_Ptr; }
	SDL_Renderer*	GetRendererPtr()	{ return Renderer_Ptr; }

	//Functions for Rendering
	//Draw to screen
	void PrintToScreen() override;

	//Draw Background
	void DrawBackground() override;

	//Draw Sprite
	void DrawSprite(Sprite* spriteToDraw, float SpriteScale, Vector2D destRectPos, float spriteNumber = 0) override;
	//Draw text at location
	void DrawText(std::string Text, Vector2D TextPosition, float TextRectScale) override;

	/*
	//Get Distance Information
	void SetCameraData(std::vector<float> &heights);
	int GetScreenWidth()	{ return initWindowWidth; }
	int GetMidpoint()		{ return Midpoint; }
	*/

	//Static pointer to this
	static Renderer_SDL* RendererSDLPtr;

	//For giggles
	void RunAway();

};

