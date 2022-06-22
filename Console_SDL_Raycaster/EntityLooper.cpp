#include "EntityLooper.h"

EntityLooper* EntityLooper::EntityLoopSelfPtr;

EntityLooper::EntityLooper()
{
	//thisFrameTime = SDL_GetTicks();
	thisFrame = std::chrono::steady_clock::now();
	EntityLoopSelfPtr = this;
}

EntityLooper::~EntityLooper()
{
	for (Entity* i : UpdateEntityList)
	{
		delete i;
	}
}

void EntityLooper::UpdateEntities()
{
	//thisFrameTime = SDL_GetTicks();
	//DeltaTime = thisFrameTime - lastFrameTime;

	thisFrame = std::chrono::steady_clock::now();
	DeltaTime = std::chrono::duration<float, std::milli>(thisFrame - lastFrame).count();
	DeltaTime = DeltaTime / 1000;

	for (Entity* i : UpdateEntityList)
	{
		i->Update(DeltaTime);
	}
	lastFrame = thisFrame;
}
