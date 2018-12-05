#include <iostream>
#include <vector>
#include "IQueenGen.h"
using namespace std;

int main(int argc, char* argv)
{
	vector<Board*> solutions;
	IQueenGen test(15);
	double time;
	cout << test.TimedGenerateSolutons(time);

	test.PrintSolutions(cout);
	test.PrintSolutions(cout);
	test.PrintSolutions(cout);

	cout << "Hello World!" << endl;
	cin.get();

	return 0;
}