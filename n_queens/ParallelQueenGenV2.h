

#include "IQueenGen.h"
#include <future>
#ifndef PARALLELQUEENGENV2_H
#define PARALLELQUEENGENV2_H
class ParallelQueenGenV2 : public IQueenGen
{
public:
	ParallelQueenGenV2(int numberOfQueens);

	unsigned int GenerateSolutions() override;

private:

	struct Node
	{
		Board* board;
		Node* prev;
		Node* next;
		Node(){}
	};

	struct ThreadPacket
	{
		Node* head, tail;
	};

};
#endif

