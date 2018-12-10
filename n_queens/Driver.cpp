/*
@file	- Driver.cpp
@author	- Jonathon Roscoe | Seattle University | CS4600 Fall 2018
@summary- Function definitions of ParallelQueenGenV1.h
*/

#include "SerialQueenGen.h"
#include "ParallelQueenGenV1.h"
#include "ParallelQueenGenV2.h"
using namespace std;

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		cout << "Please supply desired board size and queen count 'N' as the first argument. "
			 << "Please supply the desired number of threads for ParallelQueenGenv2 as the second argument"
			 << endl;
		return 1;
	}
	string arg1(argv[1]), arg2(argv[2]);
	int N = stoi(arg1);
	int threads = stoi(arg2);
	if (N < 1 || threads < 0)
	{
		cout << "Please supply positive integers for board size and thread count" << endl;
		return 1;
	}
	
	SerialQueenGen serial(N);
	ParallelQueenGenV1 parv1(N);
	ParallelQueenGenV2 parv2(N, threads);
	long long time = 0;
	if (threads > N) threads = N;
	cout << "Queens: " << N << endl;
	cout << "Serial time: " << time << " milliseconds | number of solutions: " << serial.TimedGenerateSolutons(time) << endl;
	cout << "Parallel v1 (" << N << " threads) time: " << time << " milliseconds | number of solutions: " << parv1.TimedGenerateSolutons(time) << endl;
	cout << "Parallel v2 (" << threads << " threads) time: " << time << " milliseconds | number of solutions: " << parv2.TimedGenerateSolutons(time) << endl;
	cout << "One solution: " << endl;
	parv2.PrintSolutions(cout, 1);
	return 0;
}