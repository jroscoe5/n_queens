/*
@file	- ParallelQueenGenV2.h
@author	- Jonathon Roscoe | Seattle University | CS4600 Fall 2018
@summary- Parallel Solution Generator for the N-Queens Problem, allows
		  specification of desired number of threads and computes all
		  solutions locally before linking them together.
*/

#include "IQueenGen.h"
#include <future>
#ifndef PARALLELQUEENGENV2_H
#define PARALLELQUEENGENV2_H
class ParallelQueenGenV2 : public IQueenGen
{
public:
	/*
	@param numberOfQueens - The desired number of queens, as well as the dimensions
		of the board.
	@param threads - The desired number of threads used to compute solutions. Will only
		be set as high as the numberOfQueens
	*/
	ParallelQueenGenV2(int numberOfQueens, int threads);

	~ParallelQueenGenV2();

	/*
	Generates all distinct solutions for a board size, returns number of solutions generated
	*/
	unsigned int GenerateSolutions() override;

	/*
	Prints all generated solutions
	@param out - stream to print to
	@param upToCount - optional param to print the first N solutions
	*/
	void PrintSolutions(ostream& out, unsigned int upToCount = UINT_MAX) override;

private:
	
	/*
	Deallocates all Nodes from the solutionList
	*/
	void clearSolutionList() override;

	/*
	Run by each individual thread to generate a portion of all possible distinct solutions
	@param colStart - starting column in row 0 that the thread is responsible for generating all
		distinct solutions for
	@param colEnd - non-inclusive column in row 0 that signifies the last column the thread is 
		responsible for.
	*/
	ThreadPacket threadGenerate(int colStart, int colEnd);

	/*
	Recursively generates and stores valid board states in a linked list of 
	Node objects
	@param packet - calling thread's packet that keeps track of the list of Nodes
	@param board - board containing either initial or previous board state
	@param row - current row queen will be inserted on
	*/
	void recursiveGenerate(ThreadPacket& packet, Board board, int row);

	/*
	Checks if given position is a valid spot to place a queen
	given the current board state. No queens should lie in the
	same row, column or diagonals.
	@param board - current board state
	@param xPos - target x position
	@param yPos - target y position
	*/
	bool isValidPosition(Board board, int xPos, int yPos);

	/* Max number of threads specified at construction */
	int threads;
	/* Pointer to the list of all generated solutions */
	Node* solutionList;
};

/*
Holds a board with a valid solution and a pointer to the next solution
in the list. Each thread computes its section of solutions and creates
a linked list of Node objects to store them.
*/
struct Node
{
	Board board;
	Node *next;
	Node(Board clone) : board(clone)
	{
		next = nullptr;
	}
};

/*
Returned by a thread when it has generated its section of solutions
Contains a count of solutions, as well as ptrs to the head and tail 
Nodes in its list of solutions for easy combination in the main thread.
*/
struct ThreadPacket
{
	Node *head, *tail;
	int count;
	ThreadPacket()
	{
		count = 0;
		head = tail = nullptr;
	}
};
#endif

