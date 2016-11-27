#include "History.h"
#include <iostream>
#include "globals.h"

using namespace std;

History::History(int nRows, int nCols) : m_rows(nRows), m_cols(nCols)
{
	m_grid = new int*[m_rows];
	for (int i = 0; i < m_rows; i++)
	{
		m_grid[i] = new int[m_cols];
	}


	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_cols; c++)
		{
			m_grid[r][c] = 0;
		}
	}
}

History::~History()
{
	for (int i = 0; i < m_rows; i++)
	{
		delete[] m_grid[i];
	}
	delete[] m_grid;
}
bool History:: record(int r, int c)
{
	if (r > m_rows || c > m_cols || r <= 0 || c <= 0)
	{
		return false;
	}
	m_grid[r - 1][c - 1]++;
	return true;
}

void History::display() const
{

	clearScreen();

	char** d_grid = new char*[m_rows];
	for (int i = 0; i < m_rows; i++) 
	{
		d_grid[i] = new char[m_cols];
	}

		
	// Fill the grid with dots
	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_cols; c++)
		{
			if (m_grid[r][c] == 0)
			{
				d_grid[r][c] = '.';
			}
			else if (m_grid[r][c] > 0 && m_grid[r][c] <= 26)
			{
				d_grid[r][c] = 'A' + m_grid[r][c] - 1;
			}
			else if (m_grid[r][c] > 26)
			{
				d_grid[r][c] = 'Z';
			}
			cout << d_grid[r][c];
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < m_rows; i++) 
	{
		delete[] d_grid[i];
	}
	delete[] d_grid;
}