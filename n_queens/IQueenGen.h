/**
 *	@file	- IQueenGen.h
 *	@author	- Jonathon Roscoe | Seattle University | CS4600 Fall 2018
 *	@summary- Interface for a solution generator to the N-Queens problem
**/
#include <vector>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;
#ifndef IQUEENGEN_H
#define IQUEENGEN_H
class IQueenGen
{
public:
	virtual void GenerateSolutions(vector<bool**>& solutions)
	{
		for (int x = 0; x < N; x++)
			for (int y = 0; y < N; y++)
				board[x][y] = true;
		solutions.push_back(board);
	}

	virtual float TimedGenerateSolutons(vector<bool**>& solutions)
	{
		clock_t timer = clock();
		GenerateSolutions(solutions);
		timer = timer - clock();
		return (float)timer / CLOCKS_PER_SEC;
	}

	virtual void PrintBoard(bool** board)
	{
		// Top of board
		for (int i = 0; i < N * 4 + 1; i++)
			cout << "_";
		cout << endl;

		// Interior of board
		for (int y = 0; y < N; y++)
		{
			cout << "|";
			for (int x = 0; x < N; x++)
				board[x][y] ? cout << " " << QUEEN << " |" : cout << " " << EMPTY << " |";
			cout << endl;
		}

		// Bottom of board
		for (int i = 0; i < N * 4 + 1; i++)
			cout << "_";
		cout << endl;
	}

	/*
	*	Constructor
	*	@param numberOfQueens - The desired number of queens, as well as the dimensions
	*		of the board. Uses DEFAULT_NUM if nothing is provided.
	*/
	IQueenGen(int numberOfQueens = DEFAULT_NUM) : N(numberOfQueens)
	{
		board = new bool*[N];
		for (int i = 0; i < N; i++)
			board[i] = new bool[N];

		for (int x = 0; x < N; x++)
			for (int y = 0; y < N; y++)
				board[x][y] = false;
	}

	~IQueenGen()
	{
		for (int i = 0; i < N; i++)
			delete[] board[i];

		delete[] board;
	}

protected:

	virtual bool isValidPosition(char** board, int xPos, int yPos)
	{
		// Checks if any other queens exist in the column
		for (int x = 0; x < xPos; x++)
			if (board[x][yPos]) return false;

		// Checks if any other queens exist in both diagonals
		for (int x = xPos, yd = yPos, yu = yPos; x >= 0; x--)
		{
			if (yd >= 0 && board[x][yd--]) return false;
			if (yu < N && board[x][yu++]) return false;
		}
		return true;
	}

	const string QUEEN = "Q", EMPTY = "_";
	static const int DEFAULT_NUM = 8;
	const int N;
	bool** board;
};
#endif