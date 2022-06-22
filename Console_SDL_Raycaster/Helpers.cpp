#include "Helpers.h"


Vector2D MultiplyVector(Vector2D A, Vector2D B)
{
	Vector2D ReturnVec;
	ReturnVec.X = A.X * B.X;
	ReturnVec.Y = A.Y * B.Y;
	return ReturnVec;
}

Vector2D MultiplyVector(Vector2D A, float B)
{
	Vector2D ReturnVec;
	ReturnVec.X = A.X * B;
	ReturnVec.Y = A.Y * B;
	return ReturnVec;
}

Vector2D AddVectors(Vector2D A, Vector2D B)
{
	Vector2D ReturnVec;
	ReturnVec.X = A.X + B.X;
	ReturnVec.Y = A.Y + B.Y;
	return ReturnVec;
}

Vector2D SubtractVectors(Vector2D A, Vector2D B)
{
	Vector2D ReturnVec;
	ReturnVec.X = A.X - B.X;
	ReturnVec.Y = A.Y - B.Y;
	return ReturnVec;
}

float lerpValueByAdditionSmooth(float a, float b, float add)
{
	return a + add * (b - a);
}

float DotProduct(Vector2D A, Vector2D B)
{
	return (A.X * B.X) + (A.Y * B.Y);
}

float VectorMagnitude(Vector2D A)
{
	float F = (A.X * A.X) + (A.Y * A.Y);
	return sqrtf(F);
}
