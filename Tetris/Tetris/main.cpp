#include <raylib.h>
#include "Grid.h"
#include "Blocks.cpp";

int main()
{
	Color darkBlue = { 44,44,127,255 };
	const int screenWidth = 300;
	const int screenHeight = 600;
	InitWindow(screenWidth, screenHeight, "Tetris");
	SetTargetFPS(60);

	Grid grid = Grid();
	grid.Print();

	ZBlock block = ZBlock();
	
	// Game Loop
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(darkBlue);
		grid.Draw();
		block.Draw();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}