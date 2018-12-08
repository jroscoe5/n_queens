

#include "IQueenGen.h"
#include <future>
#ifndef PARALLELQUEENGENV2_H
#define PARALLELQUEENGENV2_H
struct Node
{
	Board board;
	Node *prev, *next;
	Node(Board clone, Node* prev) : board(clone)
	{
		this->prev = prev;
	}
};
struct ThreadPacket
{
	Node *head, *tail;
	ThreadPacket()
	{
		head = tail = nullptr;
	}
};
class ParallelQueenGenV2 : public IQueenGen
{
public:
	ParallelQueenGenV2(int numberOfQueens);

	unsigned int GenerateSolutions() override;

private:

	void recursiveGenerate(ThreadPacket* packet, Board board, int row);

	Node* solutionList;
};
#endif

