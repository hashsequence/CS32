#include <queue>
#include <string>
#include <iostream>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	queue<Coord> m_s;
	m_s.push(Coord(sr, sc));
	Coord check = m_s.front();
	maze[sr][sc] = 's';
	while (m_s.empty() == false)
	{
		check = m_s.front();
		m_s.pop();

		if (check.r() == er && check.c() == ec)
			return true;
		if (maze[check.r() - 1][check.c()] == '.')
		{
			m_s.push(Coord(check.r() - 1, check.c()));
			maze[check.r() - 1][check.c()] = 'p';
		}
		if (maze[check.r()][check.c() + 1] == '.')
		{
			m_s.push(Coord(check.r(), check.c() + 1));
			maze[check.r()][check.c() + 1] = 'p';
		}
		if (maze[check.r() + 1][check.c()] == '.')
		{
			m_s.push(Coord(check.r() + 1, check.c()));
			maze[check.r() + 1][check.c()] = 'p';
		}
		if (maze[check.r()][check.c() - 1] == '.')
		{
			m_s.push(Coord(check.r(), check.c() - 1));
			maze[check.r()][check.c() - 1] = 'p';
		}
	}

	return false;
}
