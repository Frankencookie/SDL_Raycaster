#pragma once
#include <math.h>
#include <string>
#include <vector>

#define AssertBoi(f) {if(!(f)) {printf("Something Went Wrong"); exit(EXIT_FAILURE);}}

class Helpers
{
public:

};

struct Sprite
{
	void* Image;
	std::string Name;
	std::string Address;

	bool Spritesheet = false;
	int NumberOfSprites;
	int SpriteHeight;
	int SpriteWidth;
};

struct Vector2D
{
	float X;
	float Y;
};

Vector2D MultiplyVector(Vector2D A, Vector2D B);
Vector2D MultiplyVector(Vector2D A, float B);
Vector2D AddVectors(Vector2D A, Vector2D B);
Vector2D SubtractVectors(Vector2D A, Vector2D B);
float lerpValueByAdditionSmooth(float a, float b, float add);
float DotProduct(Vector2D A, Vector2D B);
float VectorMagnitude(Vector2D A);