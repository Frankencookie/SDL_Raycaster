#include "Renderer_SDL.h"

Renderer_SDL* Renderer_SDL::RendererSDLPtr;

Renderer_SDL::Renderer_SDL()
{
	Window_Ptr = nullptr;
	Renderer_Ptr = nullptr;

	SDL_GetCurrentDisplayMode(0, &displayMode);

	SDL_Init(SDL_INIT_VIDEO);

	//Create Window
	Window_Ptr = SDL_CreateWindow(
		"Shooty Shooty",	//Title
		initX,				//Initial X Position
		initY,				//initial Y Position
		initWindowWidth,	//Starting Width
		initWindowHeight,	//Starting Height
		0
	);

	AssertBoi(Window_Ptr);

	//Create Renderer
	Renderer_Ptr = SDL_CreateRenderer(
		Window_Ptr,					//Window To Render To
		-1,							//Rendering Driver (-1 is default)
		SDL_RENDERER_PRESENTVSYNC	//Behaviour Flags
	);

	AssertBoi(Renderer_Ptr);

	//Render Red by Default
	int result = SDL_SetRenderDrawColor(
		Renderer_Ptr,	//Renderer
		20,				//r
		50,				//g
		30,				//b
		1				//a
	);

	//Clear screen to RenderDrawColour
	SDL_RenderClear(Renderer_Ptr);

	//Print To Screen
	SDL_RenderPresent(Renderer_Ptr);

	int flag = IMG_INIT_PNG;
	int initted = IMG_Init(flag);
	if ((initted & flag) != flag)
	{
		printf("Oh no, PNG Failed. Big F \n");
		printf("IMG_Init: %s\n", IMG_GetError());
	}

	//Load Icon
	WindowIcon = IMG_Load("Assets/Penta.png");

	//Set Icon
	SDL_SetWindowIcon(Window_Ptr, WindowIcon);

	//All done
	printf("Renderer Startup Complete \n");

	

	//Midpoint = initWindowHeight / 2;
	//LineHeights.resize(initWindowWidth);

	//Set static pointer
	RendererSDLPtr = this;

	//Set ground rect values
	groundColour.x = 0;
	groundColour.y = Midpoint;
	groundColour.w = initWindowWidth;
	groundColour.h = Midpoint;

	//ScreenHeight = initWindowHeight;
	//ScreenWidth = initWindowWidth;


	//Initialise Font Lib
	if (TTF_Init() == -1)
	{
		printf("font died");
	}

	//Open default font
	AssertBoi(DefaultFont = TTF_OpenFont("Assets/OpenSans-Regular.ttf", 72));
}

Renderer_SDL::~Renderer_SDL()
{
	if (Renderer_Ptr)
	{
		SDL_DestroyRenderer(Renderer_Ptr);
		Renderer_Ptr = nullptr;
	}

	if (Window_Ptr)
	{
		SDL_DestroyWindow(Window_Ptr);
		Window_Ptr = nullptr;
	}

	SDL_FreeSurface(WindowIcon);
	IMG_Quit();

	TTF_CloseFont(DefaultFont);
	TTF_Quit();

	SDL_Quit();
}

void Renderer_SDL::PrintToScreen()
{
	
	SDL_RenderPresent(Renderer_Ptr);

}

void Renderer_SDL::DrawBackground()
{
	//RunAway();
	SDL_SetRenderDrawColor(
		Renderer_Ptr,	//Renderer
		20,				//r
		50,				//g
		50,				//b
		1				//a
	);
	SDL_RenderClear(Renderer_Ptr);

	SDL_SetRenderDrawColor(
		Renderer_Ptr,	//Renderer
		5,				//r
		100,			//g
		5,				//b
		1				//a
	);


	//SDL_RenderDrawRect(Renderer_Ptr, &groundColour);
	SDL_RenderFillRect(Renderer_Ptr, &groundColour);

	/*
	if (!CameraBoi)
	{
		printf("No Camera Set \n");
		return;
	}
	*/

	for (int i = 0; i < LineHeights.size(); i++)
	{
		/*
		int height = (initWindowHeight / LineHeights[i]);
		if (height < 1)
		{
			height = initWindowHeight;
		}
		*/
		int height = CalculateHeight(i);

		SDL_SetRenderDrawColor(
			Renderer_Ptr,				//Renderer
			255 - (LineHeights[i] * 16), //r
			LineHeights[i] * 3,			//g
			LineHeights[i] * 3,			//b
			1							//a
		);

		int bottom = -height / 2 + Midpoint;
		int top = height / 2 + Midpoint;
		SDL_RenderDrawLine(Renderer_Ptr, i, top, i, bottom);
	}
}

void Renderer_SDL::DrawSprite(Sprite* spriteToDraw, float SpriteScale, Vector2D destRectPos, float spriteNumber)
{
	//Set up render rect
	SDL_Rect screenLocation;
	screenLocation.x = destRectPos.X;
	screenLocation.y = destRectPos.Y;
	screenLocation.h = spriteToDraw->SpriteHeight * SpriteScale;

	//Source rect, for the part of the sprite/sheet to render
	SDL_Rect sourceRect;
	sourceRect.h = spriteToDraw->SpriteHeight;
	sourceRect.y = 0;

	//Spritesheet calculation
	if (spriteToDraw->Spritesheet)
	{
		if (spriteNumber > spriteToDraw->NumberOfSprites - 1)
		{
			printf("Sprite number out of bounds, drawing nothing. \n");
			return;
		}
		screenLocation.w = screenLocation.h;
		sourceRect.w = spriteToDraw->SpriteHeight;
		sourceRect.x = spriteToDraw->SpriteHeight * spriteNumber;
	}
	else
	{
		screenLocation.w = spriteToDraw->SpriteWidth * SpriteScale;

		sourceRect.x = 0;
		sourceRect.w = spriteToDraw->SpriteWidth;
	}
	SDL_RenderCopy(Renderer_Ptr, static_cast<SDL_Texture*>(spriteToDraw->Image), &sourceRect, &screenLocation);
}


void Renderer_SDL::DrawText(std::string Text, Vector2D TextPosition, float TextRectScale)
{
	
	SDL_Surface* MessageSurf = TTF_RenderText_Solid(DefaultFont, Text.c_str(), Black);
	SDL_Texture* MessageTex = SDL_CreateTextureFromSurface(Renderer_Ptr, MessageSurf);

	SDL_Rect MessageRect;
	MessageRect.x = TextPosition.X;
	MessageRect.y = TextPosition.Y;
	MessageRect.w = MessageSurf->w * TextRectScale;
	MessageRect.h = MessageSurf->h * TextRectScale;

	SDL_FreeSurface(MessageSurf);
	SDL_RenderCopy(Renderer_Ptr, MessageTex, NULL, &MessageRect);

	SDL_DestroyTexture(MessageTex);
	
}


/*
void Renderer_SDL::SetCameraData(std::vector<float> &heights)
{
	LineHeights = heights;
}
*/


void Renderer_SDL::RunAway()
{
	//VV Fun test to make the window run away

	int posX;
	int posY;
	int* posXptr = &posX;
	int* posYptr = &posY;
	SDL_GetWindowPosition(Window_Ptr, posXptr, posYptr);
	SDL_SetWindowPosition(Window_Ptr, posX, posY + 2);
}
