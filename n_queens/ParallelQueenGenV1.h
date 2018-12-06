
#include "IQueenGen.h"
#include <future>
#ifndef PARALLELQUEENGENV1_H
#define PARALLELQUEENGENV1_H
class ParallelQueenGenV1 :public IQueenGen
{
public:

	ParallelQueenGenV1(int numberOfQueens);

	unsigned int GenerateSolutions() override;

private:
	/*
	Checks if given position is a valid spot to place a queen
	given the current board state. No queens should lie in the
	same row, column or diagonals.
	*/
	bool isValidPosition(Board board, int xPos, int yPos) override;

	void recursiveGenerate(Board board, int row);

	mutex solutionLock;
};
#endif