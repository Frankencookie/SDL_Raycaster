#pragma once
#include <list>
//#include <SDL.h>
#include <chrono>
#include "Entity.h"

class Entity;

class EntityLooper
{
public:
	EntityLooper();
	~EntityLooper();

protected:
	std::list<Entity*> UpdateEntityList;
	float lastFrameTime = 0;
	float thisFrameTime = 0;
	std::chrono::time_point<std::chrono::high_resolution_clock> thisFrame;
	std::chrono::time_point<std::chrono::high_resolution_clock> lastFrame;

public:

	float DeltaTime = 0;
	template<class T>
	T* SpawnEntity();

	void UpdateEntities();
	static EntityLooper* EntityLoopSelfPtr;
};

template<class T>
T* EntityLooper::SpawnEntity()
{
	T* newEntity = new T;
	UpdateEntityList.push_back(newEntity);

	return newEntity;
}