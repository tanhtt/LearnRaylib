#include "Grid.h"
#include <iostream>
#include "Color.h"

Grid::Grid()
{
	numRows = 20;
	numColumns = 10;
	cellSize = 30;
	Initialize();
	colors = GetCellsColor();
}

void Grid::Initialize() {
	for (int row = 0; row < numRows; row++) {
		for (int column = 0; column < numColumns; column++) {
			grid[row][column] = 0;
		}
	}
}

void Grid::Print()
{
	for (int row = 0; row < numRows; row++) {
		for (int column = 0; column < numColumns; column++) {
			std::cout << grid[row][column] << " ";
		}
		std::cout << std::endl;
	}
}

void Grid::Draw()
{
	for (int row = 0; row < numRows; row++) {
		for (int column = 0; column < numColumns; column++) {
			int cellColor = grid[row][column];
			DrawRectangle(column * cellSize + 1, row * cellSize + 1, cellSize - 1, cellSize - 1, colors[cellColor]);
		}
	}
}