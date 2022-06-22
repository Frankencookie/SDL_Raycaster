#include "Camera.h"

Camera::Camera()
{
	lineBois.resize(960);
	CameraPlaneA = MultiplyVector(Direction, CameraPlaneOffset);
	CameraPlaneA.X = -CameraPlaneOffset;

	//RayMarchScreenStep = (CameraPlaneOffset + CameraPlaneOffset) / ScreenWidth;
	CameraPlaneChangeVector.X = RayMarchScreenStep;
	CameraPlaneChangeVector.Y = 0;
}

Camera::~Camera()
{

}

void Camera::TurnCamera(float speed)
{
	float oldX = CameraPlaneA.X;
	CameraPlaneA.X = CameraPlaneA.X * cos(speed) - CameraPlaneA.Y * sin(speed);
	CameraPlaneA.Y = oldX * sin(speed) + CameraPlaneA.Y * cos(speed);
	//ChangeVector
	oldX = CameraPlaneChangeVector.X;
	CameraPlaneChangeVector.X = CameraPlaneChangeVector.X * cos(speed) - CameraPlaneChangeVector.Y * sin(speed);
	CameraPlaneChangeVector.Y = oldX * sin(speed) + CameraPlaneChangeVector.Y * cos(speed);
	//Right Direction
	oldX = RightDirection.X;
	RightDirection.X = RightDirection.X * cos(speed) - RightDirection.Y * sin(speed);
	RightDirection.Y = oldX * sin(speed) + RightDirection.Y * cos(speed);
}

void Camera::UpdateCamera()
{
	if (!Parent)
	{
		printf("Camera Does not have a parent");
		return;
	}

	Vector2D RayDirection = CameraPlaneA;
	for (int i = 0; i < lineBois.size(); i++)
	{
		bool Hit = false;
		float distance = 0;
		Vector2D RayPos = Parent->GetPosition();
		//Vector2D CameraPlanePos = RayDirection;

		while (!Hit)
		{
			RayPos = AddVectors(MultiplyVector(RayDirection, RayMarchStep), RayPos);
			if (!LevelBoi->IsMoveValid(RayPos) || distance > MaxDistance)
			{
				//lineBois[i] = distance;
				//Vector2D Dif = SubtractVectors(RayPos, RayDirection)
				float angle = DotProduct(RayDirection, Direction);
				//angle = angle * 0.8;
				//float distance = VectorMagnitude(SubtractVectors(RayPos, CurrentPosition));
				lineBois[i] = (sin(angle) * distance);

				Hit = true;
				RayDirection = AddVectors(RayDirection, CameraPlaneChangeVector);
				break;
			}
			else
			{
				distance += RayMarchStep;
			}
		}
	}

	//RenderBoi->SetCameraData(lineBois);
}

void Camera::SetParent(Entity* newparent)
{
	Parent = newparent;
}
