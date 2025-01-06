#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "raylib.h"

class Obstacle
{
private:
	Rectangle obstacleRect;
	float moveSpeed;
public:
	Obstacle(float x, float y, float width, float height);
	void Update();
	void Draw();
	Rectangle GetCollisionBox();
	void Reset();
};

#endif // !OBSTACLE_H

