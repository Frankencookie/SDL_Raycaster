#pragma once
#include <string>
#include "Helpers.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "EntityLooper.h"
#include "Player.h"

struct Level
{
	std::vector<std::vector<int>> Map;
	std::vector<std::vector<int>> StartMap;
	std::string Name;

	bool Loaded = false;
};

class LevelManager
{
public:
	LevelManager();
private:
	int LevelNumber = 0;
	std::vector<Level*> LevelList;
	Level* CurrentLevel;


public:
	bool IsMoveValid(Vector2D inputVector);
	bool IsMoveValid(float xIn, float yIn);
	static LevelManager* LevelPtr;

	Level* LoadLevelFromFile(std::string Address, std::string NewName);

	Level* OpenLevel(int LevelIntToLoad, bool reset = true);
	
	bool CompleteLevel();

};