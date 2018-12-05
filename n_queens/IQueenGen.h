/*
@file	- IQueenGen.h
@author	- Jonathon Roscoe | Seattle University | CS4600 Fall 2018
@summary- Interface for a solution generator to the N-Queens problem
*/
#include <vector>
#include <chrono>
#include "Board.h"
using namespace std;

#ifndef IQUEENGEN_H
#define IQUEENGEN_H
class IQueenGen
{
public:
	/*
	*	@param numberOfQueens - The desired number of queens, as well as the dimensions
	*		of the board. Uses DEFAULT_NUM if nothing is provided.
	*/
	IQueenGen(int numberOfQueens = DEFAULT_NUM) : N(numberOfQueens) {}

	~IQueenGen() { clearSolutionList(); }

	virtual unsigned int GenerateSolutions() = 0;

	virtual unsigned int TimedGenerateSolutons(double& time)
	{
		auto start = chrono::high_resolution_clock::now();
		int count = GenerateSolutions();
		auto end = chrono::high_resolution_clock::now();
		time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
		return count;
	}

	virtual void PrintSolutions(ostream& out)
	{
		for (int i = 0; i < solutions.size(); i++)
		{
			solutions[i]->PrintBoard(out);
		}
	}

protected:

	void clearSolutionList()
	{
		for (int i = 0; i < solutions.size(); i++)
			delete solutions[i];
		solutions.clear();
	}

	virtual bool isValidPosition(char** board, int xPos, int yPos)
	{
		// Checks if any other queens exist in the column
		for (int x = 0; x < xPos; x++)
			if (board[x][yPos]) return false;

		// Checks if any other queens exist in both diagonals
		for (int x = xPos, yd = yPos, yu = yPos; x >= 0; x--)
		{
			if (yd >= 0 && board[x][yd--]) return false;
			if (yu < N && board[x][yu++]) return false;
		}
		return true;
	}

	static const int DEFAULT_NUM = 8;
	const int N;
	vector<Board*> solutions;
};
#endif