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
	/* Default Board size if none supplied */
	static const int DEFAULT_NUM = 8;

	/*
	@param numberOfQueens - The desired number of queens, as well as the dimensions
		of the board. Uses DEFAULT_NUM if nothing is provided
	*/
	IQueenGen(int numberOfQueens = DEFAULT_NUM) : N(numberOfQueens) {}

	virtual ~IQueenGen() { clearSolutionList(); }

	/*
	Should generate all distinct solutions for a board size and return number generated
	Should clear the solution list prior to generation
	*/
	virtual unsigned int GenerateSolutions() = 0;

	/*
	Tight timer around GenerateSolutions. Returns number of solutions
	@param milliseconds - Will be set to time elapsed during generation
	*/
	virtual unsigned int TimedGenerateSolutons(long long& milliseconds)
	{
		auto start = chrono::high_resolution_clock::now();
		int count = GenerateSolutions();
		auto end = chrono::high_resolution_clock::now();
		milliseconds = chrono::duration_cast<chrono::milliseconds>(end - start).count();
		return count;
	}

	/*
	Prints all generated solutions
	@param out - stream to print to
	*/
	virtual void PrintSolutions(ostream& out)
	{
		if (solutions.size() == 0)
		{
			out << "No solutions availible at this time." << endl;
			return;
		}
		else
			for (int i = 0; i < solutions.size(); i++)
			{
				solutions[i]->PrintBoard(out);
			}
	}

protected:

	/*
	Empties and deallocates all Board objects in solutions
	*/
	virtual void clearSolutionList()
	{
		for (int i = 0; i < solutions.size(); i++)
			delete solutions[i];
		solutions.clear();
	}

	/*
	Should check if given position is a valid spot to place a queen
	given the current board state. No queens should lie in the
	same row, column or diagonals.
	@param board - current board state
	@param xPos - target x position
	@param yPos - target y position
	*/
	virtual bool isValidPosition(Board board, int xPos, int yPos) = 0;

	/* Board size */
	const int N;
	/* Holds generated solutions */
	vector<Board*> solutions;
};
#endif