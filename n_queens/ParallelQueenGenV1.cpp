#include "ParallelQueenGenV1.h"

ParallelQueenGenV1::ParallelQueenGenV1(int numberOfQueens = DEFAULT_NUM) :
	IQueenGen(numberOfQueens) { }

unsigned int ParallelQueenGenV1::GenerateSolutions()
{
	clearSolutionList();
	future<void>* handles = new future<void>[N];
	Board board(N);
	for (int col = 0; col < N; col++)
	{
		board(0, col, true);
		handles[col] = async(launch::async, &ParallelQueenGenV1::recursiveGenerate, this, board, 1);
		board(0, col, false);
	}

	for (int i = 0; i < N; i++)
	{
		handles[i].wait();
	}

	delete[] handles;
	return (unsigned int) solutions.size();
}


void ParallelQueenGenV1::recursiveGenerate(Board board, int row)
{
	// If current row is equal to size, board has been filled
	if (row == N)
	{
		solutionLock.lock();
		solutions.push_back(new Board(board));
		solutionLock.unlock();
		return;
	}
	// For each column in the row, if possible - 
	// push a queen and recursively generate solutions for the new position.
	for (int col = 0; col < N; col++)
	{
		if (isValidPosition(board, row, col))
		{
			board(row, col, true);
			recursiveGenerate(board, row + 1);
			board(row, col, false);
		}
	}
}

bool ParallelQueenGenV1::isValidPosition(Board board, int xPos, int yPos)
{
	// Because boards are generated from top row down, we can assume that
	// no queens will be placed in the same row. We also only have to
	// check diagonals beneath the current position.

	// Checks if any other queens exist in the column
	for (int x = 0; x < xPos; x++)
		if (board(x, yPos)) return false;

	// Checks if any other queens exist in both diagonals
	for (int x = xPos, yd = yPos, yu = yPos; x >= 0; x--)
	{
		if (yd >= 0 && board(x, yd--)) return false;
		if (yu < N && board(x, yu++)) return false;
	}
	return true;
}


