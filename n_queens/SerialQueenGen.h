/*
@file	- SerialQueenGen.h
@author	- Jonathon Roscoe | Seattle University | CS4600 Fall 2018
@summary- Serial Soluion generator to the N-Queens Problem
*/

#include "IQueenGen.h"
#ifndef SERIALQUEENGEN_H
#define SERIALQUEENGEN_G
class SerialQueenGen : public IQueenGen
{
public:
	/*
	@param numberOfQueens - The desired number of queens, as well as the dimensions
		of the board.
	*/
	SerialQueenGen(int numberOfQueens);

	/*
	Generates all distinct solutions for a board size, returns number of solutions generated
	*/
	unsigned int GenerateSolutions() override;

private:
	/*
	Recursively generates and stores valid board states in solutions vector
	@param board - board containing either initial or previous board state
	@param row - current row queen will be inserted on
	*/
	void recursiveGenerate(Board board, int row);

	/*
	Checks if given position is a valid spot to place a queen
	given the current board state. No queens should lie in the
	same row, column or diagonals.
	*/
	bool isValidPosition(Board board, int xPos, int yPos) override;
};
#endif

