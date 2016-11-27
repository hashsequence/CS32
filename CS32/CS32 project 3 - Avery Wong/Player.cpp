// Player.cpp

#include "provided.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
	int rate(const Scaffold& board, int N, int color);
	int determineBestComputerMove(Scaffold& board, int N, int color, int& col);
	int determineBestHumanMove(Scaffold& board, int N, int color, int& col);
    int chooseMove(const Scaffold& s, int N, int color);
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
	int input = -1;
	bool validLevel = false;
	if (s.numberEmpty() > 0)
	{
		do
		{
			do
			{
				cout << "Choose a Column:";
				cin >> input;
				cin.ignore(10000, '\n');
			} while (input <= 0 || input > s.cols());

			for (int i = 1; i <= s.levels(); i++)
			{
				if (s.checkerAt(input, i) == VACANT)
				{
					validLevel = true;
				}
			}

		} while (validLevel == false);
		return input;
	}

    return -1;  //  This is not always correct; it's just here to compile
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
	int input = 1;
	bool validLevel = false;
	if (s.numberEmpty() > 0)
	{
		do
		{
			for (int i = 1; i <= s.levels(); i++)
			{
				if (s.checkerAt(input, i) == VACANT)
				{
					validLevel = true;
				}
			}
			if (validLevel == false)
			{
				input++;
			}
		} while (validLevel == false);
		return input;
	}
    return -1;  //  This is not always correct; it's just here to compile
}
/*for each color the function will iterate through every spot in the scaffold and check the rows, horizontals, and diagonal for the respective color

if the color that won was the computer return 1;
if the color that won was the from the other player return -1
if tied return 0
if game is not completed return -2*/
int SmartPlayerImpl::rate(const Scaffold& board, int N, int color)
{
	for (int i = 1; i <= board.cols(); i++)
	{
		for (int j = 1; j <= board.levels(); j++)
		{
			for (int c = 0; c < 2; c++)
			{
				if (c == 1)
				{
					if (color == RED)
					{
						color = BLACK;
					}
					if (color == BLACK)
					{
						color = RED;
					}
				}

				int counterN = 0;
				for (int k = 0; k < N; k++)
				{
					if (board.checkerAt(i, j + k) == color)
					{
						counterN++;
					}
				}
				int counterS = 0;
				for (int k = 0; k < N; k++)
				{
					if (board.checkerAt(i, j - k) == color)
					{
						counterS++;
					}
				}
				int counterW = 0;
				for (int k = 0; k < N; k++)
				{
					if (board.checkerAt(i - k, j) == color)
					{
						counterW++;
					}
				}
				int counterE = 0;
				for (int k = 0; k < N; k++)
				{
					if (board.checkerAt(i + k, j) == color)
					{
						counterE++;
					}
				}
				int counterNW = 0;
				for (int k = 0; k < N; k++)
				{
					if (board.checkerAt(i - k, j + k) == color)
					{
						counterNW++;
					}
				}
				int counterNE = 0;
				for (int k = 0; k < N; k++)
				{
					if (board.checkerAt(i + k, j + k) == color)
					{
						counterNE++;
					}
				}
				int counterSW = 0;
				for (int k = 0; k < N; k++)
				{
					if (board.checkerAt(i - k, j - k) == color)
					{
						counterSW++;
					}
				}
				int counterSE = 0;
				for (int k = 0; k < N; k++)
				{
					if (board.checkerAt(i + k, j - k) == color)
					{
						counterSE++;
					}
				}
				if (counterN == N || counterS == N || counterW == N || counterE == N ||
					counterNW == N || counterNE == N || counterSW == N || counterSE == N)
				{
					if (c == 0)
						return 1;
					if (c == 1)
						return -1;
				}
			}
		}
	}
	if (board.numberEmpty() == 0)
		return 0;
	return -2;
}
int SmartPlayerImpl::determineBestHumanMove(Scaffold& board, int N, int color, int& col)
{
	vector<int> moves;  //declares a vector of moves
	vector<int> ratings; // declares a vector of ratings
	int o_color = color;
	if (color == BLACK) // sets the color of opposing player checker
		o_color = RED;
	if (color == RED)
		o_color = BLACK;
	int rating = 2;
	int bestrating = 10000;

	for (int i = 1; i <= board.cols(); i++) // go through each column
	{
		if (board.makeMove(i, o_color)) // if column is vacant proceed and makes the move
		{
			moves.push_back(i); //pushes the move into the moves vector
			rating = rate(board, N, color); // rates the move and should return 1, 0 , -1
			if (rating == 0 || rating == -1)
			{
				ratings.push_back(rating); //pushes the rating into rating vector
			}
			else
			{
				ratings.push_back(determineBestComputerMove(board, N, color, col));//calls the determinebestComputerMove and returns the best rating from that move
			}
			board.undoMove(); // undos the move
		}
	}
	for (unsigned int i = 0; i < ratings.size(); i++) // find the move with the lowest rating corresponding to lost for computer
	{
		if (ratings[i] <= bestrating)
		{
			bestrating = ratings[i];
			col = moves[i];
		}
	}

	return bestrating;
}
int SmartPlayerImpl::determineBestComputerMove(Scaffold& board, int N, const int color, int& col)
{
	vector<int> moves; // declares a vector of moves 
	vector<int> ratings;//decalres a vector of rating
	int rating = 2;
	int bestrating = -10000;

	for (int i = 1; i <= board.cols(); i++) //goes through each column
	{
		if (board.makeMove(i, color)) //makes the move with the users color
		{
			moves.push_back(i); //pushes move into moves vector
			rating = rate(board, N, color); // rate the move
			if (rating == 0 || rating == 1) // if move is win or tie push rating into ratings vector
			{
				ratings.push_back(rating);
			}
			else
			{
				ratings.push_back(determineBestHumanMove(board, N, color, col)); // otherwise calls the besthumanmove function and take the rating of the best human move
			}
			board.undoMove();
		}
	}
	for (unsigned int i = 0; i < ratings.size(); i++) // find the bestmove with the higest rating
	{
		if (ratings[i] >= bestrating)
		{
			bestrating = ratings[i];
			col = moves[i];
		}
	}
	return bestrating;
}
int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
	int move = 0;
	Scaffold s2(s); //copys the scaffold
	determineBestComputerMove(s2, N, color, move);
	return move;
	
     //  This is not always correct; it's just here to compile
}

//******************** Player derived class functions *************************

// These functions simply delegate to the Impl classes' functions.
// You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color); 
}
