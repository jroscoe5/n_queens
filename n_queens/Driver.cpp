#include <iostream>
#include <vector>
#include "SerialQueenGen.h"
#include "ParallelQueenGenV1.h"
#include "ParallelQueenGenV2.h"
using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "Please supply desired board size and queen count 'N' as a single cmd line arg." << endl;
		return 1;
	}
	int N = argv[1][0] - '0';
	if (N < 1)
	{
		cout << "Please supply a positive integer for board size and queen count 'N'" << endl;
		return 1;
	}

	ParallelQueenGenV1 test(N);
	SerialQueenGen test2(N);
	long long time = 0;
	cout << time << " " << test.TimedGenerateSolutons(time) << endl;
	cout << time << " " << test2.TimedGenerateSolutons(time) << endl;
	cin.get();
	test.PrintSolutions(cout, N);
	cin.get();
	return 0;
}