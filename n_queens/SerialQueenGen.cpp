/*
@file	- SerialQueenGen.cpp
@author	- Jonathon Roscoe | Seattle University | CS4600 Fall 2018
@summary- Function definitions of SerialQueenGen.h
*/

#include "SerialQueenGen.h"

SerialQueenGen::SerialQueenGen(int numberOfQueens) : 
	IQueenGen(numberOfQueens) {}

unsigned int SerialQueenGen::GenerateSolutions()
{
	clearSolutionList();
	Board board(N);
	recursiveGenerate(board, 0);
	return (unsigned int) solutions.size();
}

void SerialQueenGen::recursiveGenerate(Board board, int row)
{
	// If current row is equal to size, board has been filled
	if (row == N)
	{
		solutions.push_back(new Board(board));
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

bool SerialQueenGen::isValidPosition(Board board, int xPos, int yPos)
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


