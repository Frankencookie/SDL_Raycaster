#include "GameManager_UI.h"

GameManager_UI::GameManager_UI()
{
	RendererBoi = Renderer_Interface::RendererInterfacePtr;

	UiSprite = SpriteLoader::SpriteLoaderPtr->LoadSprite("Assets/UI.png", "UI");

	UiLocation.X = (RendererBoi->GetScreenWidth() / 2) - (UiSprite->SpriteWidth / 2);
	UiLocation.Y = (RendererBoi->GetMidpoint() * 2) - (UiSprite->SpriteHeight);

	FpsLocation.X = UiLocation.X + 20;
	FpsLocation.Y = UiLocation.Y + 80;

	TimeLocation.X = UiLocation.X + 350;
	TimeLocation.Y = FpsLocation.Y;


	LooperBoi = EntityLooper::EntityLoopSelfPtr;
}

void GameManager_UI::DrawUI()
{
	RendererBoi->DrawSprite(UiSprite, 1, UiLocation);

	//Work out fps
	Fps = 1 / LooperBoi->DeltaTime;
	
	if (LooperBoi->DeltaTime < 1)
	{
		GameTime += (LooperBoi->DeltaTime);
	}

	RendererBoi->DrawText(std::to_string(Fps), FpsLocation, 0.4f);

	int GameTimeToDisplay = floor(GameTime);
	RendererBoi->DrawText(std::to_string(GameTimeToDisplay), TimeLocation, 0.4f);
}

