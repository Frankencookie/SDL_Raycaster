#include "GameManager_UI.h"

GameManager_UI::GameManager_UI()
{
	Renderer_ptr = Renderer_Interface::RendererInterfacePtr;

	UiSprite = SpriteLoader::SpriteLoaderPtr->LoadSprite("Assets/UI.png", "UI");

	UiLocation.X = (Renderer_ptr->GetScreenWidth() / 2) - (UiSprite->SpriteWidth / 2);
	UiLocation.Y = (Renderer_ptr->GetMidpoint() * 2) - (UiSprite->SpriteHeight);

	FpsLocation.X = UiLocation.X + 20;
	FpsLocation.Y = UiLocation.Y + 80;

	TimeLocation.X = UiLocation.X + 350;
	TimeLocation.Y = FpsLocation.Y;


	Looper_ptr = EntityLooper::EntityLoopSelfPtr;
}

void GameManager_UI::DrawUI()
{
	Renderer_ptr->DrawSprite(UiSprite, 1, UiLocation);

	//Work out fps
	Fps = 1 / Looper_ptr->DeltaTime;
	
	if (Looper_ptr->DeltaTime < 1)
	{
		GameTime += (Looper_ptr->DeltaTime);
	}

	Renderer_ptr->DrawText(std::to_string(Fps), FpsLocation, 0.4f);

	int GameTimeToDisplay = floor(GameTime);
	Renderer_ptr->DrawText(std::to_string(GameTimeToDisplay), TimeLocation, 0.4f);
}

