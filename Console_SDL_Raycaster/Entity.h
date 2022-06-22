#pragma once
#include "Helpers.h"
//#include "LevelManager.h"

class LevelManager;

class Entity
{
public:
	Entity();
protected:
	Vector2D CurrentPosition;
	//LevelManager* LevelPtr;

public:
	virtual void Update(float Delta);
	void SetPosition(Vector2D Pos);
	//void SetLevelPtr(LevelManager* newptr);

	Vector2D GetPosition() { return CurrentPosition; }
};
