#include <iostream>
#include <vector>
#include "SerialQueenGen.h"
using namespace std;

int main(int argc, char* argv)
{
	SerialQueenGen test(8);
	long long time = 0;
	test.PrintSolutions(cout);
	cout << test.TimedGenerateSolutons(time) << " " <<  time << endl;
	cout << test.TimedGenerateSolutons(time) << " " << time << endl;
	cout << test.TimedGenerateSolutons(time) << " " << time << endl;
	cin.get();
	test.PrintSolutions(cout);

	cin.get();
	return 0;
}