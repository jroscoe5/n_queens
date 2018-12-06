#include <iostream>
#include <vector>
#include "SerialQueenGen.h"
#include "ParallelQueenGenV1.h"
using namespace std;

int main(int argc, char** argv)
{
	ParallelQueenGenV1 test(10);
	SerialQueenGen test2(10);
	long long time = 0;
	cout << time << " " << test.TimedGenerateSolutons(time) << endl;
	cout << time << " " << test2.TimedGenerateSolutons(time) << endl;
	return 0;
}