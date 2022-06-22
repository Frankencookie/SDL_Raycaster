#include "Entity.h"

Entity::Entity()
{
	//LevelPtr = LevelManager::LevelPtr;
}

void Entity::Update(float Delta)
{
	
}

void Entity::SetPosition(Vector2D Pos)
{
	CurrentPosition = Pos;
}
