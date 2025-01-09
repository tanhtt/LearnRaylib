#pragma once

#include "Grid.h"
#include "Blocks.cpp"

class Game
{
public:
	Game();
	Block GetRandomBlock();
	std::vector<Block> GetAllBlocks();
	void Draw();
	void Update();
	void HandleInput();
	void MoveBlockLeft();
	void MoveBlockRight();
	void MoveBlockDown();
	bool IsBlockOutside();
	Grid grid;
private:
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
};
