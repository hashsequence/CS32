// Scaffold.cpp

#include "provided.h"
#include <iostream>
#include <stack>
#include <vector>

using namespace std;


class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels); 
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const; 
    void display() const; 
    bool makeMove(int column, int color); 
    int undoMove(); 
private:
	
	int m_nColumns;
	int m_nLevels;
	vector<vector<int>> m_grid;
	stack<int> Movelist;
};
/*the scaffold constructor initializes the momber variables for columns and levels and create a 2d array of int using vectors and sets all
the spots VACANT*/
ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels) : m_nColumns(nColumns), m_nLevels(nLevels)
{
	if (m_nColumns <= 0 || m_nLevels <= 0)
	{
		cerr << "Columns or levels are not positive!" << endl;
		exit(1);
	}
	
	m_grid.resize(nColumns);  // grid now has M empty rows
	for (int i = 0; i < nColumns; i++)
		m_grid[i].resize(nLevels);  // row i now has N columns
	for (int i = 0; i < m_nColumns; i++)
	{
		for (int j = 0; j < m_nLevels; j++)
		{
			m_grid[i][j] = VACANT;
		}
	}
	
}

int ScaffoldImpl::cols() const
{
    return m_nColumns;  //  returns the number of columns
}

int ScaffoldImpl::levels() const
{
    return m_nLevels	;  //  returns the number of levels
}

int ScaffoldImpl::numberEmpty() const
{
	int emptySpots = 0;  //initializes a variable to count empty spots
	for (int i = 0; i < m_nColumns; i++) // loop counts the numer of empty spots
	{  
		for (int j = 0; j < m_nLevels; j++)
		{ 
			if (m_grid[i][j] == VACANT)
				emptySpots++;
		}
	}
    return emptySpots;  //  return the number of empty spots
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
	if (column > 0 && column <= cols() && level > 0 && level <= levels())
	{
		if (m_grid[column - 1][level - 1] == RED)
			return RED;
		if (m_grid[column - 1][level - 1] == BLACK)
			return BLACK;
	}
		return VACANT;  
}

void ScaffoldImpl::display() const
{
	for (int i = levels()-1; i >= 0; i--) //the for loop iterates from the topmost level to the lowest level from left to right
	{
		for (int j = 0; j < cols(); j++)
		{
			if (cols() == 1 && j == 0) // if only one column
			{
				if (checkerAt(j + 1, i + 1) == VACANT)
					cout << "| |" << endl;
				if (checkerAt(j + 1, i + 1) == RED)
					cout << "|R|" << endl;
				if (checkerAt(j + 1, i + 1) == BLACK)
					cout << "|B|" << endl;
			}
			if (cols() > 1 && j == 0) //more than one column but leftmost edge
			{
				if (checkerAt(j + 1, i + 1) == VACANT)
					cout << "| |";
				if (checkerAt(j + 1, i + 1) == RED)
					cout << "|R|";
				if (checkerAt(j + 1, i + 1) == BLACK)
					cout << "|B|";
			}
			if (cols() > 1 && j == cols() - 1) //the rightmost edge
			{
				if (checkerAt(j + 1, i + 1) == VACANT)
					cout << " |" << endl;
				if (checkerAt(j + 1, i + 1) == RED)
					cout << "R|" << endl;
				if (checkerAt(j + 1, i + 1) == BLACK)
					cout << "B|" << endl;
			}
			if (j != 0 && j != cols() - 1) // all the internal edges
			{
				if (checkerAt(j + 1, i + 1) == VACANT)
					cout << " |";
				if (checkerAt(j + 1, i + 1) == RED)
					cout << "R|";
				if (checkerAt(j + 1, i + 1) == BLACK)
					cout << "B|";
			}
		}
	}
	for (int k = 0; k < m_nColumns; k++) // displays the boundary +-+ line
	{
		if (k == 0)
		{
			cout << "+-+";
		}
		else
		{
			cout << "-+";
		}
	}
	cout << endl;
}

bool ScaffoldImpl::makeMove(int column, int color)
{
	if (color == RED || color == BLACK) // checks if valid color
	{
		if (column >= 1 && column <= cols()) //check for valid column
		{
			for (int j = 0; j < m_nLevels; j++) // iterates through the column from bottom to top and place checker in first vacant spot
			{
				if (m_grid[column - 1][j] == VACANT)
				{
					m_grid[column - 1][j] = color;
					Movelist.push(column - 1);
					return true;
				}
			}
		}
	}
    return false;  // returns false when no move can be made
}

int ScaffoldImpl::undoMove()
{
	if (Movelist.empty() == true)
		return 0;  //  returns 0 when no move can be undone
	int lastcolumn = Movelist.top();
	for (int j = levels()-1; j >= 0; j--) // iterates through the last column and finds the first filled spot
	{
		if (m_grid[Movelist.top()][j] != VACANT)
		{
			m_grid[Movelist.top()][j] = VACANT; // make topmost filled spot vacant
			Movelist.pop();
			break;
		}
	}
	return lastcolumn + 1; //return the last column checker was deleted from
}

//******************** Scaffold functions *******************************

// These functions simply delegate to ScaffoldImpl's functions.
// You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}

