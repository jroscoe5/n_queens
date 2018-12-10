/*
@file	- ParallelQueenGenV2.cpp
@author	- Jonathon Roscoe | Seattle University | CS4600 Fall 2018
@summary- Function definitions of ParallelQueenGenV2.h
*/

#include "ParallelQueenGenV2.h"

ParallelQueenGenV2::ParallelQueenGenV2(int numberOfQueens, int threads) :
	IQueenGen(numberOfQueens), threads(threads)
{
	solutionList = nullptr;
	// Not allowed to have more threads than there are columns
	if (threads > N) threads = N;
}

ParallelQueenGenV2::~ParallelQueenGenV2()
{
	clearSolutionList();
}

unsigned int ParallelQueenGenV2::GenerateSolutions()
{
	clearSolutionList();

	future<ThreadPacket>* handles = new future<ThreadPacket>[threads];

	// Calculate the initial queen positions each thread is responsible for
	int colPerThread = N / threads;
	int currCol = 0;
	// Launch threads
	for (int i = 0; i < threads; i++)
	{
		if (i != threads - 1)
		{
			handles[i] = async(launch::async, &ParallelQueenGenV2::threadGenerate, this, currCol, currCol + colPerThread);
			currCol += colPerThread;
		}
		else
		{
			handles[i] = async(launch::async, &ParallelQueenGenV2::threadGenerate, this, currCol, N);
		}
	}


	Node* tail = nullptr;
	unsigned int count = 0;
	// Get results from the threads, link up results into solutionList
	for (int i = 0; i < threads; i++)
	{
		ThreadPacket packet = handles[i].get();
		count += packet.count;
		if (solutionList == nullptr && packet.count > 0)
		{
			solutionList = packet.head;
			tail = packet.tail;
		}
		else if (packet.count > 0)
		{
			tail->next = packet.head;
			tail = packet.tail;
		}
	}

	delete[] handles;
	return count;
}

void ParallelQueenGenV2::PrintSolutions(ostream& out, unsigned int upToCount)
{
	Node* curr = solutionList;
	unsigned int count = 0;
	if (curr == nullptr)
	{
		out << "No solutions availible at this time." << endl;
		return;
	}
	// Traverse through list and call each board's print function
	while (curr != nullptr && count < upToCount)
	{
		curr->board.PrintBoard(out);
		curr = curr->next;
		count++;
	}
}

void ParallelQueenGenV2::clearSolutionList()
{
	Node *curr, *next;
	curr = solutionList;
	while (curr != nullptr)
	{
		next = curr->next;
		delete curr;
		curr = next;
	}
	solutionList = nullptr;
}

ThreadPacket ParallelQueenGenV2::threadGenerate(int colStart, int colStop)
{
	Board board(N);
	ThreadPacket packet;
	// For each column in row 0 that the thread is responsible for,
	// place a Queen and recursively calculate all solutions stemming
	// from that initial position
	for (int col = colStart; col < colStop; col++)
	{
		board(0, col, true);
		recursiveGenerate(packet, board, 1);
		board(0, col, false);
	}

	return packet;
}

void ParallelQueenGenV2::recursiveGenerate(ThreadPacket& packet, Board board, int row)
{
	if (row == N)
	{
		// Solution found, add it to the list managed by packet
		Node* node = new Node(board);
		if (packet.head == nullptr)
		{
			packet.head = packet.tail = node;
		}
		else
		{
			packet.tail->next = node;
			packet.tail = node;
		}
		packet.count++;
		return;
	}
	for (int col = 0; col < N; col++)
	{
		if (isValidPosition(board, row, col))
		{
			board(row, col, true);
			recursiveGenerate(packet, board, row + 1);
			board(row, col, false);
		}
	}
}

bool ParallelQueenGenV2::isValidPosition(Board board, int xPos, int yPos)
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