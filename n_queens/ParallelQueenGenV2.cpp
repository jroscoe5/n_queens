#include "ParallelQueenGenV2.h"



ParallelQueenGenV2::ParallelQueenGenV2(int numberOfQueens) : 
	IQueenGen(numberOfQueens)
{
	solutionList = nullptr;
}

unsigned int ParallelQueenGenV2::GenerateSolutions()
{
	// clear solution list


	Board board(N);
	future<void>* handles = new future<void>[N];
	ThreadPacket* packets = new ThreadPacket[N];

	for (int col = 0; col < N; col++)
	{
		board(0, col, true);
		handles[col] = async(launch::async, &ParallelQueenGenV2::recursiveGenerate, this, &packets[col], board, 1);
		board(0, col, false);
	}

	for (int i = 0; i < N; i++)
	{
		handles[i].wait();
	}

	delete[] packets;
	delete[] handles;
	return 0;
}
void ParallelQueenGenV2::recursiveGenerate(ThreadPacket* packet, Board board, int row)
{

}