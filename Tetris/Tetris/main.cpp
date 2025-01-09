#include <raylib.h>
#include "Game.h"

int main()
{
	Color darkBlue = { 44,44,127,255 };
	const int screenWidth = 300;
	const int screenHeight = 600;
	InitWindow(screenWidth, screenHeight, "Tetris");
	SetTargetFPS(60);
	
	Game game = Game();

	// Game Loop
	while (!WindowShouldClose())
	{
		BeginDrawing();

		game.Update();

		ClearBackground(darkBlue);
		game.Draw();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}