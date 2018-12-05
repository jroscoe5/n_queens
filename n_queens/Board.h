/*
@file	- Board.h
@author	- Jonathon Roscoe | Seattle University | CS4600 Fall 2018
@summary- Represents an N x N chess board 
*/

#include <string>
using namespace std;

#ifndef BOARD_H
#define BOARD_H
/*	
Class that simulates an N x N chess board. Spaces with queens are true,
empty spaces are false. Provides a method to print board state to a stream
*/
class Board
{
public:
	/*
	@param squareSize - the desired X and Y dimensions of the board
		SIZE is initialized to DEFAULT_SIZE if less than 1
	All squares are initially empty
	*/
	Board(int squareSize) : SIZE((squareSize > 0) ? squareSize : DEFAULT_SIZE)
	{
		board = new bool*[SIZE];
		for (int i = 0; i < SIZE; i++)
			board[i] = new bool[SIZE];

		for (int x = 0; x < SIZE; x++)
			for (int y = 0; y < SIZE; y++)
				board[x][y] = false;
	}

	/*
	@param rhs - Board object whose square's state will be copied
	*/
	Board(const Board& rhs) : SIZE(rhs.SIZE)
	{
		board = new bool*[SIZE];
		for (int i = 0; i < SIZE; i++)
			board[i] = new bool[SIZE];

		for (int x = 0; x < SIZE; x++)
			for (int y = 0; y < SIZE; y++)
				board[x][y] = rhs.board[x][y];
	}

	~Board()
	{
		for (int i = 0; i < SIZE; i++)
			delete[] board[i];
		delete[] board;
	}

	/*
	@param rhs - Board object whose square's state will be copied
	*/
	Board& operator=(const Board& rhs)
	{
		int minSize = (rhs.SIZE < SIZE) ? rhs.SIZE : SIZE;
		for (int x = 0; x < minSize; x++)
			for (int y = 0; y < minSize; y++)
				board[x][y] = rhs.board[x][y];
	}
	
	/*
	Provides read access to the interior board.
	@param x - the x cordinate of the board
	@param y - the y cordinate of the board
	*/
	bool operator()(int x, int y)
	{
		return board[x][y];
	}

	/*
	Provides write access to the interior board
	@param x - the x cordinate of the board
	@param y - the y cordinate of the board
	@param value - will be written to board at provided cordinates
	*/
	void operator()(int x, int y, bool value)
	{
		board[x][y] = value;
	}

	/*
	Writes a graphical representation of the board state to a stream
	@param out - ostream object to write board to
	*/
	void PrintBoard(ostream& out)
	{
		static const string QUEEN = "Q";
		static const string EMPTY = "-";

		// Top of board: A dashed line
		for (int i = 0; i < SIZE * 4 + 1; i++)
			out << "-";
		out << endl;
		// Interior of board: Cells formatted as '| Q |'
		for (int y = 0; y < SIZE; y++)
		{
			out << "|";
			for (int x = 0; x < SIZE; x++)
				board[x][y] ? out << " " << QUEEN << " |" : out << " " << EMPTY << " |";
			out << endl;
		}
		// Bottom of board: A dashed line
		for (int i = 0; i < SIZE * 4 + 1; i++)
			out << "-";
		out << endl;
	}

private:
	/* Default size of a board */
	static const int DEFAULT_SIZE = 1; 
	/* Board has dimensions [SIZE] x [SIZE] */
	const int SIZE;
	/* Internal 2d boolean array represents the board */
	bool** board;
};
#endif
