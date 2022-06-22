#include "Player.h"

Player::Player()
{
	InputBoi = CrossPlatformInput::InputPtr;
	RenderBoi = Renderer_Interface::RendererInterfacePtr;
	//RenderBoi->SetCameraData(lineBois);
	screenLines.resize(RenderBoi->GetScreenWidth());

	CameraPlaneA = MultiplyVector(Direction, CameraPlaneOffset);
	CameraPlaneA.X = -CameraPlaneOffset;

	RayMarchScreenStep = (CameraPlaneOffset + CameraPlaneOffset) / RenderBoi->GetScreenWidth();
	CameraPlaneChangeVector.X = RayMarchScreenStep;
	CameraPlaneChangeVector.Y = 0;

	screenMidPoint = RenderBoi->GetMidpoint();
	Test = SpriteLoader::SpriteLoaderPtr->GetSprite();
	//SpriteRect.h = 128;
	//SpriteRect.w = 128;
	//SpriteRect.x = 0;
	//SpriteRect.y = 0;

	LevelPtr = LevelManager::LevelPtr;
}

Player::~Player()
{
	screenLines.clear();
}

void Player::Update(float Delta)
{
	float TempSpeed = PlayerSpeed * Delta;
	float TempRotationSpeed = RotationSpeed * Delta;

	Velocity = { 0,0 };

	//Movement By Axis
	//Forward
	if (InputBoi->GetAxisValue(CA_LEFTY))
	{
		float value = -InputBoi->GetAxisValue(CA_LEFTY) / 32767;
		if (std::abs(value) > MovementDeadzone)
		{
			MoveForward_Axis(value, TempSpeed);
		}
	}
	//Right
	if (InputBoi->GetAxisValue(CA_LEFTX))
	{
		float value = InputBoi->GetAxisValue(CA_LEFTX) / 32767;
		if (std::abs(value) > MovementDeadzone)
		{
			MoveRight_Axis(value, TempSpeed);
		}
	}

	//Rotation By Axis
	if (InputBoi->GetAxisValue(CA_RIGHTX))
	{
		float value = -InputBoi->GetAxisValue(CA_RIGHTX) / 32767;
		if (std::abs(value) > MovementDeadzone)
		{
			Turn(value, TempRotationSpeed);
		}
	}

	Move();

	CalculateCamera();
	//CameraBoi->UpdateCamera();

	//SDL_RenderCopy(Renderer_SDL::RendererSDLPtr->GetRendererPtr(), static_cast<SDL_Texture*>(Test->Image), NULL, &SpriteRect);
}

void Player::MoveForward_Axis(float Speed, float DeltaSpeed)
{
	float ForwardSpeed = DeltaSpeed * Speed;
	Vector2D newPos;
	{
		newPos = MultiplyVector(Direction, ForwardSpeed);
		Velocity = AddVectors(Velocity, newPos);
	}
}

void Player::MoveRight_Axis(float Speed, float DeltaSpeed)
{
	float RightSpeed = DeltaSpeed * Speed;
	Vector2D newPos;
	{
		newPos = MultiplyVector(RightDirection, RightSpeed);
		Velocity = AddVectors(Velocity, newPos);
	}
}

void Player::Move()
{
	Vector2D newPos = CurrentPosition;
	newPos = AddVectors(newPos, Velocity);
	if (LevelPtr->IsMoveValid(newPos))
	{
		CurrentPosition = newPos;
	}
	else
	{
		printf("WALL COLLISION \n");
	}
}

void Player::Turn(float speed, float DeltaSpeed)
{
	float turnSpeed = DeltaSpeed * speed;
	//Character
	float oldX = Direction.X;
	Direction.X = Direction.X * cos(turnSpeed) - Direction.Y * sin(turnSpeed);
	Direction.Y = oldX * sin(turnSpeed) + Direction.Y * cos(turnSpeed);
	
	//Plane A
	oldX = CameraPlaneA.X;
	CameraPlaneA.X = CameraPlaneA.X * cos(turnSpeed) - CameraPlaneA.Y * sin(turnSpeed);
	CameraPlaneA.Y = oldX * sin(turnSpeed) + CameraPlaneA.Y * cos(turnSpeed);
	//ChangeVector
	oldX = CameraPlaneChangeVector.X;
	CameraPlaneChangeVector.X = CameraPlaneChangeVector.X * cos(turnSpeed) - CameraPlaneChangeVector.Y * sin(turnSpeed);
	CameraPlaneChangeVector.Y = oldX * sin(turnSpeed) + CameraPlaneChangeVector.Y * cos(turnSpeed);
	//Right Direction
	oldX = RightDirection.X;
	RightDirection.X = RightDirection.X * cos(turnSpeed) - RightDirection.Y * sin(turnSpeed);
	RightDirection.Y = oldX * sin(turnSpeed) + RightDirection.Y * cos(turnSpeed);
	
}


void Player::CalculateCamera()
{
	Vector2D RayDirection = CameraPlaneA;
	for (int x = 0; x < screenLines.size(); x++)
	{
		//Replace all of this with DDA Algorithm
		bool Hit = false;
		float distance = 0;
		Vector2D RayPos = CurrentPosition;
		//Vector2D CameraPlanePos = RayDirection;
		float RayMarchStepTemp = RayMarchStep;

		//While not touching a wall, keep moving forward
		while (!Hit)
		{
			RayPos = AddVectors(MultiplyVector(RayDirection, RayMarchStepTemp), RayPos);

			if (!LevelPtr->IsMoveValid(RayPos) || distance > MaxDistance)
			{
				float angle = DotProduct(RayDirection, Direction);
				screenLines[x] = (sin(angle) * distance);

				Hit = true;
				RayDirection = AddVectors(RayDirection, CameraPlaneChangeVector);
				break;
			}
			else
			{
				distance += RayMarchStepTemp;
				RayMarchStepTemp += 0.002;
			}
		}
	}

	RenderBoi->SetCameraData(screenLines);
	
}
