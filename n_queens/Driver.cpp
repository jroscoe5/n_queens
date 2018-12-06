#include <iostream>
#include <vector>
#include "SerialQueenGen.h"
#include "ParallelQueenGenV1.h"
using namespace std;

int main(int argc, char** argv)
{
	ParallelQueenGenV1 test(8);
	SerialQueenGen test2(8);
	long long time = 0;
	cout << time << " " << test.TimedGenerateSolutons(time) << endl;
	cout << time << " " << test2.TimedGenerateSolutons(time) << endl;
	cin.get();
	test.PrintSolutions(cout, 4);
	cin.get();
	return 0;
}