/*
@file	- IQueenGen.h
@author	- Jonathon Roscoe | Seattle University | CS4600 Fall 2018
@summary- Interface for a solution generator to the N-Queens problem
*/

#include <vector>
#include <chrono>
#include <limits>
#include "Board.h"

#ifndef IQUEENGEN_H
#define IQUEENGEN_H
class IQueenGen
{
public:
	/*
	@param numberOfQueens - The desired number of queens, as well as the dimensions
		of the board. Uses DEFAULT_NUM if nothing is provided
	*/
	IQueenGen(int numberOfQueens) : N(numberOfQueens) {}

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
		auto start = std::chrono::high_resolution_clock::now();
		int count = GenerateSolutions();
		auto end = std::chrono::high_resolution_clock::now();
		milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		return count;
	}

	/*
	Prints all generated solutions
	@param out - stream to print to
	@param upToCount - optional param to print the first N solutions
	*/
	virtual void PrintSolutions(std::ostream& out, unsigned int upToCount = std::numeric_limits<unsigned int>::max())
	{
		if (upToCount <= 0 || solutions.size() == 0)
		{
			out << "No solutions availible at this time." << std::endl;
			return;
		}
		else
		{
			if (upToCount > solutions.size()) upToCount = solutions.size();
			for (int i = 0; i < upToCount; i++)
			{
				solutions[i]->PrintBoard(out);
			}
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
	std::vector<Board*> solutions;
};
#endif