#include "Renderer_Interface.h"

Renderer_Interface* Renderer_Interface::RendererInterfacePtr;

Renderer_Interface::Renderer_Interface()
{
	Midpoint = initWindowHeight / 2;
	RendererInterfacePtr = this;

	LineHeights.resize(initWindowWidth);

}

Renderer_Interface::~Renderer_Interface()
{

}

int Renderer_Interface::CalculateHeight(int lineNumber)
{
	int height = (initWindowHeight / LineHeights[lineNumber]);
	if (height < 1)
	{
		height = initWindowHeight;
	}
	return height;
}

void Renderer_Interface::PrintToScreen()
{
}

void Renderer_Interface::DrawSprite(Sprite* spriteToDraw, float SpriteScale, Vector2D destRectPos, float spriteNumber)
{
}

void Renderer_Interface::DrawBackground()
{
}

void Renderer_Interface::SetCameraData(std::vector<float>& heights)
{
	LineHeights = heights;
}

void Renderer_Interface::DrawText(std::string Text, Vector2D TextPosition, float TextRectScale)
{

}
