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
	bool IsCellOutside(int row, int column);
	int grid[20][10];
private:
	int numRows;
	int numColumns;
	int cellSize;
	std::vector<Color> colors;
};
