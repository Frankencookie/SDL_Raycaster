#pragma once
#include "Helpers.h"
#include <vector>
#include "Entity.h"
#include "LevelManager.h"

class Camera
{
public:
	Camera();
	~Camera();
private:
	float RayMarchStep = 0.08;
	float MaxDistance = 28;
	float RayMarchScreenStep;
	const float CameraPlaneOffset = 0.5f;

	Vector2D Direction = { 0,1 };
	Vector2D CameraPlaneA;
	Vector2D RightDirection = { 1,0 };
	Vector2D CameraPlaneChangeVector;

	float screenMidPoint;
	Entity* Parent;
	LevelManager* LevelBoi;

public:
	void TurnCamera(float speed);
	void UpdateCamera();
	void SetParent(Entity* newparent);
	std::vector<float> lineBois;

};

