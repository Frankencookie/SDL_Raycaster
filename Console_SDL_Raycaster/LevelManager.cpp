#include "LevelManager.h"

LevelManager* LevelManager::LevelPtr;

LevelManager::LevelManager()
{
	LevelPtr = this;
	LoadLevelFromFile("Assets/Level1.txt", "Test");
	LoadLevelFromFile("Assets/Level2.txt", "Test2");
	OpenLevel(LevelNumber);
}

bool LevelManager::IsMoveValid(Vector2D inputVector)
{
	int fX = floor(inputVector.X);
	int fY = floor(inputVector.Y);

	if (CurrentLevel->Map[fX][fY] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LevelManager::IsMoveValid(float xIn, float yIn)
{
	int fX = floor(xIn);
	int fY = floor(yIn);

	if (CurrentLevel->Map[fX][fY] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}

Level* LevelManager::LoadLevelFromFile(std::string Address, std::string NewName)
{
	std::ifstream File;
	File.open(Address);

	unsigned int Value = 0;

	if (File.is_open())
	{
		Level* newBoi = new Level;
		newBoi->Name = NewName;

		int row = 0;
		printf("Level File opened \n");

		std::vector<int> col;
		newBoi->StartMap.push_back(col);

		while (File >> Value)
		{
			if (Value != 9)
			{
				newBoi->StartMap.at(row).push_back(Value);
			}
			else
			{
				++row;
				std::vector<int> col;
				newBoi->StartMap.push_back(col);
			}

		}

		File.close();
		printf("File Closed \n");
		LevelList.push_back(newBoi);
	}
	else
	{
		printf("Failed to open level file \n");
	}

	return nullptr;
}

Level* LevelManager::OpenLevel(int LevelIntToLoad, bool reset)
{
	Level* loadBoi = LevelList[LevelIntToLoad];
	if (reset || !loadBoi->Loaded)
	{
		loadBoi->Map = loadBoi->StartMap;

		for (int i = 0; i < loadBoi->Map.size(); i++)
		{
			for (int u = 0; u < loadBoi->Map.at(i).size(); u++)
			{
				//if(loadBoi->Map.at(i)[u] == 2)
				switch (loadBoi->Map.at(i)[u])
				{
				case 2:
					//EntityLooper::EntityLoopSelfPtr->SpawnEntity<Player>();
					//playerBoi->SetPosition(Vector2D{ 7,7 });
					//printf("Player Spawned \n");
					break;
				default:
					break;
				}
			}
		}
	}
	CurrentLevel = loadBoi;
	return loadBoi;
}

bool LevelManager::CompleteLevel()
{
	++LevelNumber;
	if ((LevelNumber + 1) > LevelList.size())
	{
		return false;
	}
	OpenLevel(LevelNumber);
	return true;
}
