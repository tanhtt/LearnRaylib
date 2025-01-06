#ifndef DINO_H
#define DINO_H

#include <raylib.h>

class Dino
{
private:
	Rectangle dinoRect;
	float speedY;
	bool isJumping;
	const float gravity;
	const float jumpForce;
	Texture2D texture;
	int frameCount;
	int currentFrame;
	float frameTime;
	float timer;
	int runStartFrame;
	int runEndFrame;

public:
	Dino(float x, float y, float width, float height, Texture2D spriteSheet, int frameCount, int runStart, int runEnd );
	~Dino();
	void Update();
	void Draw();
	Rectangle GetCollisionBox();
	void Reset(float x, float y);
};

#endif // !DINO_H

