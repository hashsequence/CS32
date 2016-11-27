#include "History.h"
#include <iostream>

using namespace std;

History::History(int nRows, int nCol)
{
	hrows = nRows;
	hcols = nCol;
	for (int c1 = 0; c1 < hrows; c1++)
		for (int c2 = 0; c2 < hcols; c2++)
			hgrid[MAXROWS][MAXCOLS] = 0;
}

bool History::record(int r, int c)
{
	if (r < hrows && c < hcols)
	{
		hgrid[r][c]++;
		return true;
	}
	else
	{
		return false;
	}

}

void History::display() const
{
	char grid[MAXROWS][MAXCOLS];
	int r, c;

	// Fill the grid with dots
	for (r = 0; r < hrows; r++)
	{
		for (c = 0; c < hcols; c++)
		{
			grid[r][c] = '.';
		}
	}

	for (r = 0; r < hrows; r++)
	{
		for (c = 0; c < hcols; c++)
		{
			switch (hgrid[r][c])
			{
			case 0:
				grid[r][c] = '.';
				break;
			case 1:
				grid[r][c] = 'A';
				break;
			case 2:
				grid[r][c] = 'B';
				break;
			case 3:
				grid[r][c] = 'C';
				break;
			case 4:
				grid[r][c] = 'D';
				break;
			case 5:
				grid[r][c] = 'E';
				break;
			case 6:
				grid[r][c] = 'F';
				break;
			case 7:
				grid[r][c] = 'G';
				break;
			case 8:
				grid[r][c] = 'H';
				break;
			case 9:
				grid[r][c] = 'I';
				break;
			case 10:
				grid[r][c] = 'J';
				break;
			case 11:
				grid[r][c] = 'K';
				break;
			case 12:
				grid[r][c] = 'L';
				break;
			case 13:
				grid[r][c] = 'M';
				break;
			case 14:
				grid[r][c] = 'N';
				break;
			case 15:
				grid[r][c] = 'O';
				break;
			case 16:
				grid[r][c] = 'P';
				break;
			case 17:
				grid[r][c] = 'Q';
				break;
			case 18:
				grid[r][c] = 'R';
				break;
			case 19:
				grid[r][c] = 'S';
				break;
			case 20:
				grid[r][c] = 'T';
				break;
			case 21:
				grid[r][c] = 'U';
				break;
			case 22:
				grid[r][c] = 'V';
				break;
			case 23:
				grid[r][c] = 'W';
				break;
			case 24:
				grid[r][c] = 'X';
				break;
			case 25:
				grid[r][c] = 'Y';
				break;
			default:
				grid[r][c] = 'Z';
				break;
			}
		}
	}
	clearScreen();
	for (r = 0; r < hrows; r++)
	{
		for (c = 0; c < hcols; c++)
			cout << grid[r][c];
		cout << endl;
	}
	cout << endl;
}