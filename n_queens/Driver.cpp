#include <iostream>
#include <vector>
#include "SerialQueenGen.h"
#include "ParallelQueenGenV1.h"
#include "ParallelQueenGenV2.h"
using namespace std;

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		cout << "Please supply desired board size and queen count 'N' as the first argument." << endl 
			 << "Please supply the desired number of threads for ParallelQueenGenv2 as the second argument" << endl;
		return 1;
	}
	string arg1(argv[1]), arg2(argv[2]);
	int N = stoi(arg1);
	int threads = stoi(arg2);
	if (N < 1 || threads < 0)
	{
		cout << "Please supply a positive integer for board size and thread count" << endl;
		return 1;
	}

	ParallelQueenGenV1 test(N);
	SerialQueenGen test2(N);
	ParallelQueenGenV2 test3(N, threads);
	long long time = 0;
	cout << time << " " << test.TimedGenerateSolutons(time) << endl;
	cout << time << " " << test2.TimedGenerateSolutons(time) << endl;
	cout << time << " " << test3.TimedGenerateSolutons(time) << endl;
	cout << time << " " << test3.TimedGenerateSolutons(time) << endl;
	cin.get();
	test3.PrintSolutions(cout, 1);
	cin.get();
	return 0;
}