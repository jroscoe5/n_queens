#include <iostream>
#include <vector>
#include "IQueenGen.h"
using namespace std;

int main(int argc, char* argv)
{
	vector<bool**> solutions;
	IQueenGen test(9);
	test.GenerateSolutions(solutions);
	test.PrintBoard(solutions[0]);

	cout << "Hello World!" << endl;
	cin.get();

	return 0;
}