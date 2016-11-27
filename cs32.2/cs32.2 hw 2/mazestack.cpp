#include <stack>
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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	stack<Coord> m_s;
	m_s.push(Coord(sr, sc));
	Coord check = m_s.top();
	maze[sr][sc] = 's';
	while (m_s.empty() == false)
	{
		check = m_s.top();
		m_s.pop();

		if (check.r() == er && check.c() == ec)
			return true;
		if (maze[check.r() - 1][check.c()] == '.')
		{
			m_s.push(Coord(check.r() - 1, check.c()));
			maze[check.r() - 1][check.c()] = 'p';
		}
		if (maze[check.r() ][check.c()  + 1] == '.')
		{
			m_s.push(Coord(check.r(), check.c() + 1));
			maze[check.r() ][check.c()  + 1] = 'p';
		}
		if (maze[check.r()  + 1][check.c() ] == '.')
		{
			m_s.push(Coord(check.r() + 1, check.c()));
			maze[check.r()  + 1][check.c() ] = 'p';
		}
		if (maze[check.r() ][check.c()  - 1] == '.')
		{
			m_s.push(Coord(check.r(), check.c()-1));
			maze[check.r() ][check.c()  - 1] = 'p';
		}
	}
	
	return false;
}
*/