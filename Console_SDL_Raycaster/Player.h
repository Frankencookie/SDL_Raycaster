#pragma once
#include "Entity.h"
#include "CrossPlatformInput.h"
#include "Renderer_Interface.h"
#include "SpriteLoader.h"
#include "Helpers.h"
#include "LevelManager.h"
#include <cstdlib>;

class Player :
	public Entity
{
public:
	Player();
	~Player();
protected:
	CrossPlatformInput* InputBoi;
	Renderer_Interface* RenderBoi;

	float RayMarchStep = 0.01;
	float MaxDistance = 28;
	float RayMarchScreenStep;
	const float CameraPlaneOffset = 0.5f;
	float PlayerSpeed = 3.5f;
	float RotationSpeed = 3;
	float MovementDeadzone = 0.1f;
	float screenMidPoint;


	Vector2D Direction = { 0,1 };
	
	Vector2D CameraPlaneA;
	Vector2D RightDirection = { 1,0 };
	Vector2D CameraPlaneChangeVector;
	

	Vector2D Velocity = { 0,0 };

	LevelManager* LevelPtr;


	void CalculateCamera();
	std::vector<float> screenLines;

	//Sprite Stuff
	Sprite* Test;
	//SDL_Rect SpriteRect;

public:
	//void SetRefs(Renderer_SDL* RenderInput);

	//Movement
	void MoveForward_Axis(float Speed, float DeltaSpeed);
	void MoveRight_Axis(float Speed, float DeltaSpeed);
	void Move();
	void Turn(float speed, float DeltaSpeed);

	void Update(float Delta);
};
