#pragma once
#include "raylib.h"
#include <vector>

class Grid
{
public:
	Grid();
	void Initialize();
	void Print();
	void Draw();
	int grid[20][10];
private:
	std::vector<Color> GetCellsColor();
	int numRows;
	int numColumns;
	int cellSize;
	std::vector<Color> colors;
};
