#include "APP_RendererTest.h"

void APP_RendererTest::Start()
{
	Running = true;
	//Renderer_SDL* Renderer = new Renderer_SDL;
	//Renderer_Interface* Renderer = new Renderer_Interface;
	CrossPlatformRenderManager* RenderManager_ptr = new CrossPlatformRenderManager;
	Renderer_Interface* Renderer_ptr = RenderManager_ptr->Renderer;
	EntityLooper* EntityLoop_ptr = new EntityLooper;

	//InputManager* InputBoi = new InputManager;
	CrossPlatformInput* Input_ptr = new CrossPlatformInput;
	LevelManager* LevelManager_ptr = new LevelManager;
	SpriteLoader* SpriteLoad_ptr = new SpriteLoader;
	Player* Player_ptr = EntityLoop_ptr->SpawnEntity<Player>();
	Player_ptr->SetPosition(Vector2D{6,6});

	//UI And Game Manager
	GameManager_UI* GameManager_ptr = new GameManager_UI;

	//SpriteSheetTest
	//SpriteLoadBoi->LoadSprite("Assets/SheetTest.png", "SheetTest", true);
	//Invalid sprite sheet test
	SpriteLoad_ptr->LoadSprite("Assets/SheetTestInvalid.png", "SheetTest", true);

	while (Running)
	{
		Input_ptr->UpdateInput();
		if (Input_ptr->GetButtonDown(CB_TOP)&& ! levelSwitchDown)
		{
			levelSwitchDown = true;
			if (LevelManager_ptr->CompleteLevel())
			{
				Player_ptr->SetPosition(Vector2D{ 6,6 });
			}
			else
			{
				CloseGame();
			}
			
		}
		if (!Input_ptr->GetButtonDown(CB_TOP))
		{
			levelSwitchDown = false;
		}
		if (Input_ptr->GetButtonDown(CB_START))
		{
			CloseGame();
		}
		Renderer_ptr->DrawBackground();
		EntityLoop_ptr->UpdateEntities();
		if (Input_ptr->GetButtonDown(CB_BOTTOM))
		{
			Renderer_ptr->DrawText("The Game", Vector2D{ 0,0 }, 1);
			//Renderer->DrawSprite(SpriteLoadBoi->GetSprite(), 1, Vector2D{ 500, 0 });
			//Renderer->DrawSprite(SpriteLoadBoi->GetSprite("SheetTest"), 1, Vector2D{ 0, 200 }, 1);
		}
		
		GameManager_ptr->DrawUI();
		Renderer_ptr->PrintToScreen();
	}

	delete SpriteLoad_ptr;
	delete Input_ptr;
	delete EntityLoop_ptr;
	delete LevelManager_ptr;
	delete Renderer_ptr;

	SDL_Quit();

	printf("Exited \n");
	getchar();
}

void APP_RendererTest::CloseGame()
{
	Running = false;
	MessageWindow::GameClosed();
}
