#include <raylib.h>
#include "Grid.h"

int main()
{
	Color darkBlue = { 44,44,127,255 };
	const int screenWidth = 300;
	const int screenHeight = 600;
	InitWindow(screenWidth, screenHeight, "Tetris");
	SetTargetFPS(60);

	Grid grid = Grid();
	grid.Print();
	
	// Game Loop
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(darkBlue);
		grid.Draw();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}