#include "APP_RendererTest.h"

void APP_RendererTest::Start()
{
	Running = true;
	//Renderer_SDL* Renderer = new Renderer_SDL;
	//Renderer_Interface* Renderer = new Renderer_Interface;
	CrossPlatformRenderManager* RenderManager = new CrossPlatformRenderManager;
	Renderer_Interface* Renderer = RenderManager->Renderer;
	EntityLooper* EntityLoop = new EntityLooper;

	//InputManager* InputBoi = new InputManager;
	CrossPlatformInput* InputBoi = new CrossPlatformInput;
	LevelManager* LevelManagerBoi = new LevelManager;
	SpriteLoader* SpriteLoadBoi = new SpriteLoader;
	Player* PlayerBoi = EntityLoop->SpawnEntity<Player>();
	PlayerBoi->SetPosition(Vector2D{6,6});

	//UI And Game Manager
	GameManager_UI* GameManager = new GameManager_UI;

	//SpriteSheetTest
	//SpriteLoadBoi->LoadSprite("Assets/SheetTest.png", "SheetTest", true);
	//Invalid sprite sheet test
	SpriteLoadBoi->LoadSprite("Assets/SheetTestInvalid.png", "SheetTest", true);

	while (Running)
	{
		InputBoi->UpdateInputBoi();
		if (InputBoi->GetButtonDown(CB_TOP)&& ! levelSwitchDown)
		{
			levelSwitchDown = true;
			if (LevelManagerBoi->CompleteLevel())
			{
				PlayerBoi->SetPosition(Vector2D{ 6,6 });
			}
			else
			{
				CloseGame();
			}
			
		}
		if (!InputBoi->GetButtonDown(CB_TOP))
		{
			levelSwitchDown = false;
		}
		if (InputBoi->GetButtonDown(CB_START))
		{
			CloseGame();
		}
		Renderer->DrawBackground();
		EntityLoop->UpdateEntities();
		if (InputBoi->GetButtonDown(CB_BOTTOM))
		{
			Renderer->DrawText("The Game", Vector2D{ 0,0 }, 1);
			//Renderer->DrawSprite(SpriteLoadBoi->GetSprite(), 1, Vector2D{ 500, 0 });
			//Renderer->DrawSprite(SpriteLoadBoi->GetSprite("SheetTest"), 1, Vector2D{ 0, 200 }, 1);
		}
		
		GameManager->DrawUI();
		Renderer->PrintToScreen();
	}

	delete SpriteLoadBoi;
	delete InputBoi;
	delete EntityLoop;
	delete LevelManagerBoi;
	delete Renderer;

	SDL_Quit();

	printf("Exited \n");
	getchar();
}

void APP_RendererTest::CloseGame()
{
	Running = false;
	MessageWindow::GameClosed();
}
