#include <raylib.h>
#include "Dino.h"
#include "Obstacle.h"

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Dino Never Stop");
	SetTargetFPS(60);

	Texture2D dinoTexture = LoadTexture("Graphics/DinoSprites - doux.png");

	Dino dino(50, screenHeight - 100, 64, 64, dinoTexture, 24, 4, 8);
	Obstacle obstacle(screenWidth, screenHeight - 50, 30, 50);

	int score = 0;
	bool gameOver = false;

	while (!WindowShouldClose()) {

		if (!gameOver) {
			dino.Update();
			obstacle.Update();

			if (obstacle.GetCollisionBox().x + obstacle.GetCollisionBox().width < 0) {
				obstacle.Reset();
				score++;
			}

			if (CheckCollisionRecs(dino.GetCollisionBox(), obstacle.GetCollisionBox())) {
				gameOver = true;
			}
		}

		BeginDrawing();
		ClearBackground(BLACK);

		if (!gameOver) {
			dino.Draw();
			obstacle.Draw();
			DrawText(TextFormat("Score: %i", score), 10, 10, 20, GRAY);
		}
		else {
			DrawText("Game Over!", screenWidth / 2 - 100, screenHeight / 2 - 20, 40, RED);
			DrawText(TextFormat("Final Score: %i", score), screenWidth / 2 - 100, screenHeight / 2 + 30, 20, GRAY);
			DrawText("Press R to Restart", screenWidth / 2 - 100, screenHeight / 2 + 60, 20, GRAY);

			// Reset game
			if (IsKeyPressed(KEY_R)) {
				dino.Reset(50, screenHeight - 100); // Reset khủng long
				obstacle.Reset();
				score = 0;
				gameOver = false;
			}
		}
		EndDrawing();
	}

	return 0;
}