#pragma once

#include "CrossPlatformRenderManager.h"
#include "Helpers.h"
#include "Entity.h"
#include "Player.h"
#include "EntityLooper.h"
#include "InputManager.h"
#include "CrossPlatformInput.h"
#include "MessageWindow.h"
#include "SpriteLoader.h"
#include "GameManager_UI.h"

class APP_RendererTest
{
public:
	void Start();

protected:
	bool Running = false;
	bool levelSwitchDown = false;

	void CloseGame();
};
