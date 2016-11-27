// Game.cpp

#include "provided.h"
#include <iostream>

class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black); 
    bool completed(int& winner) const; 
    bool takeTurn(); 
    void play(); 
    int checkerAt(int c, int r) const;
private:
	Scaffold m_board;
	Player* m_red;
	Player* m_black;
	int m_N;
	int winner;
	int turn;
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black) :m_board(nColumns, nLevels), m_N(N),m_red(red), m_black(black)
{
	winner = TIE_GAME;
	turn = RED;
	if (nColumns <= 0 || nLevels <= 0 || N > nColumns || N > nLevels)
	{
		exit(1);
	}
}
/*If the game isn't over (i.e., more moves are possible), return false and do not change winner. Otherwise, 
set winner to RED, BLACK, or TIE_GAME, reflecting the outcome of the game, and return true.*/
bool GameImpl::completed(int& winner) const
{
	if (m_board.numberEmpty() > 0)
	{
		
		for (int i = 1; i <= m_board.cols(); i++)
		{
			for (int j = 1; j <= m_board.levels(); j++)
			{
				// check who won
				for (int c = 0; c < 2; c++)
				{
					int color = RED;
					if (c == 1)
						color = BLACK;
						
					int counterN = 0;
					for (int k = 0; k < m_N; k++)
					{
						if (m_board.checkerAt(i, j + k) == color)
						{
							counterN++;
						}
					}
					int counterS = 0;
					for (int k = 0; k < m_N; k++)
					{
						if (m_board.checkerAt(i, j - k) == color)
						{
							counterS++;
						}
					}
					int counterW = 0;
					for (int k = 0; k < m_N; k++)
					{
						if (m_board.checkerAt(i - k, j) == color)
						{
							counterW++;
						}
					}
					int counterE = 0;
					for (int k = 0; k < m_N; k++)
					{
						if (m_board.checkerAt(i + k, j) == color)
						{
							counterE++;
						}
					}
					int counterNW = 0;
					for (int k = 0; k < m_N; k++)
					{
						if (m_board.checkerAt(i - k, j + k) == color)
						{
							counterNW++;
						}
					}
					int counterNE = 0;
					for (int k = 0; k < m_N; k++)
					{
						if (m_board.checkerAt(i + k, j + k) == color)
						{
							counterNE++;
						}
					}
					int counterSW = 0;
					for (int k = 0; k < m_N; k++)
					{
						if (m_board.checkerAt(i - k, j - k) == color)
						{
							counterSW++;
						}
					}
					int counterSE = 0;
					for (int k = 0; k < m_N; k++)
					{
						if (m_board.checkerAt(i + k, j - k) == color)
						{
							counterSE++;
						}
					}
					if (counterN == m_N || counterS == m_N || counterW == m_N || counterE == m_N ||
						counterNW == m_N || counterNE == m_N || counterSW == m_N || counterSE == m_N)
					{
						winner = color;
						return true;
					}

				}
				
			}
		}
	}
	if (m_board.numberEmpty() == 0)
	{
		winner = TIE_GAME;
		return true;
	}
    return false;  //  returns false if game is not completed
}

bool GameImpl::takeTurn()
{
	if (completed(winner) == true) //returns true if game is complted
	{
		return false;  //  This is not always correct; it's just here to compile
	}
	if (turn == RED) //red makes a move
	{
		m_board.makeMove(m_red->chooseMove(m_board, m_N, RED), RED);
		if (completed(winner) == true)
		{
			return false;
		}
	}
	if (turn == BLACK) //black makes a move
	{
		m_board.makeMove(m_black->chooseMove(m_board, m_N, BLACK), BLACK);
		if (completed(winner) == true)
		{
			return false;
		}
	}
	if (turn == RED) // switches turn
	{
		turn = BLACK;
	}
	else
	{
		turn = RED;
	}
	return true;
}

void GameImpl::play()
{
	do
	{
		m_board.display();
		if (turn == RED)
		{
			std::cout << m_red->name() << "'s turn" << std::endl;
		}
		if (turn == BLACK)
		{
			std::cout << m_black->name() << "'s turn" << std::endl;
		}
		if (m_red->isInteractive() == false && turn == RED)
		{
			std::cout << "Press enter to continue.";
			std::cin.ignore(10000, '\n'); 
		}
		if (m_black->isInteractive() == false && turn == BLACK)
		{
			std::cout << "Press enter to continue.";
			std::cin.ignore(10000, '\n');
		}
	} while (takeTurn() == true);

	m_board.display();
		if (winner == RED)
		{
			std::cout << "Winner is " << m_red->name() << std::endl;
		}
		if (winner == BLACK)
		{
			std::cout << "Winner is " << m_black->name() << std::endl;
		}
		if (winner == TIE_GAME)
		{
			std::cout << "Game is Tied!" << std::endl << std::endl;
		}
}

int GameImpl::checkerAt(int c, int r) const
{
	return m_board.checkerAt(c, r);
}

//******************** Game functions *******************************

// These functions simply delegate to GameImpl's functions.
// You probably don't want to change any of this code.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
