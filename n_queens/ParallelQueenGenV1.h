/*
@file	- ParallelQueenGenV1.h
@author	- Jonathon Roscoe | Seattle University | CS4600 Fall 2018
@summary- Parallel Solution Generator for the N-Queens Problem
*/

#include "IQueenGen.h"
#include <future>
#ifndef PARALLELQUEENGENV1_H
#define PARALLELQUEENGENV1_H
class ParallelQueenGenV1 : public IQueenGen
{
public:
	/*
	@param numberOfQueens - The desired number of queens, as well as the dimensions
	of the board.
	*/
	ParallelQueenGenV1(int numberOfQueens);

	/*
	Generates all distinct solutions for a board size and return number generated
	*/
	unsigned int GenerateSolutions() override;

private:
	/*
	Checks if given position is a valid spot to place a queen
	given the current board state. No queens should lie in the
	same row, column or diagonals.
	*/
	bool isValidPosition(Board board, int xPos, int yPos) override;

	/*
	Recursively generates and stores valid board states in solutions vector
	@param board - board containing either initial or previous board state
	@param row - current row queen will be inserted on
	*/
	void recursiveGenerate(Board board, int row);

	/* Lock for solutions vector */
	mutex solutionLock;
};
#endif