#include "Obstacle.h"

Obstacle::Obstacle(float x, float y, float width, float height)
	: obstacleRect{x,y,width,height}, moveSpeed(250.0f) { }

void Obstacle::Update()
{
	obstacleRect.x -= moveSpeed * GetFrameTime();
}

void Obstacle::Draw()
{
	DrawRectangleRec(obstacleRect, GRAY);
}

Rectangle Obstacle::GetCollisionBox()
{
	return obstacleRect;
}

void Obstacle::Reset()
{
	obstacleRect.x = GetScreenWidth();
}