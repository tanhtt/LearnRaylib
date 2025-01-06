#include "Dino.h"

Dino::Dino(float x, float y, float width, float height, Texture2D spriteSheet, int totalFrames, int runStart, int runEnd)
	: dinoRect{x,y,width,height}, speedY(0), isJumping(false), gravity(1000.0f), jumpForce(-500.0f),
		texture(spriteSheet), frameCount(totalFrames), currentFrame(0),
		frameTime(0.1f), timer(0.0f), runStartFrame(runStart), runEndFrame(runEnd) { }

Dino::~Dino()
{
	UnloadTexture(texture);
}

void Dino::Update() {
	if (IsKeyPressed(KEY_SPACE) && !isJumping) {
		speedY = jumpForce;
		isJumping = true;
	}

	// Apply gravity
	speedY += gravity * GetFrameTime();
	dinoRect.y += speedY * GetFrameTime();

	if (dinoRect.y >= GetScreenHeight() - dinoRect.height) {
		dinoRect.y = GetScreenHeight() - dinoRect.height;
		isJumping = false;
	}

	timer += GetFrameTime();
	if (timer >= frameTime)
	{
		timer = 0.0f;
		currentFrame++;
		if (currentFrame > runEndFrame)
			currentFrame = runStartFrame;
	}
}

void Dino::Draw()
{
	int frameWidth = texture.width / frameCount;

	Rectangle sourceRect = {
		frameWidth * currentFrame, // Vị trí X của frame hiện tại
		0,                         // Vị trí Y (hàng đầu tiên)
		(float)frameWidth,         // Chiều rộng khung hình
		(float)texture.height      // Chiều cao khung hình
	};

	DrawTexturePro(texture, sourceRect, dinoRect, Vector2{ 0, 0 }, 0.0f, WHITE);
}

Rectangle Dino::GetCollisionBox()
{
	return dinoRect;
}

void Dino::Reset(float x, float y)
{
	dinoRect.x = x;
	dinoRect.y = y;
	speedY = 0;
	isJumping = false;
	currentFrame = 0;
	timer = 0.0f;
}