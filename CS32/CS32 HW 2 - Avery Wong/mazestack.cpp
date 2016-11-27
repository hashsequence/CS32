#include <iostream>
#include <stack>

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

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);


int main()
{

	char maze[10][10] = {
		{ 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' },
		{ 'X', '.', '.', '.', '.', '.', '.', '.', '.', 'X' },
		{ 'X', 'X', '.', 'X', '.', 'X', 'X', 'X', 'X', 'X' },
		{ 'X', '.', '.', 'X', '.', 'X', '.', '.', '.', 'X' },
		{ 'X', '.', '.', 'X', '.', '.', '.', 'X', '.', 'X' },
		{ 'X', 'X', 'X', 'X', '.', 'X', 'X', 'X', '.', 'X' },
		{ 'X', '.', 'X', '.', '.', '.', '.', 'X', 'X', 'X' },
		{ 'X', '.', '.', 'X', 'X', '.', 'X', 'X', '.', 'X' },
		{ 'X', '.', '.', '.', 'X', '.', '.', '.', '.', 'X' },
		{ 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X' }
	};
	if (pathExists(maze, 6, 4, 1, 1))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;

}

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	stack<Coord> coordStack;     // declare a stack of Coords
	Coord start(sr, sc);
	Coord end(er, ec);
	Coord P(start);
	coordStack.push(P);
	if (maze[sr][sc] == 'X' || maze[er][ec] == 'X')
		return false;
	maze[sr][sc] = 'P';
	while (coordStack.empty() == false)
	{
		P = coordStack.top();
		coordStack.pop();	
	
		if (P.r() == end.r() && P.c() == end.c())
			return true;
		if (maze[P.r() - 1][P.c()] != 'X' && maze[P.r() - 1][P.c()] != 'P') // north
		{
			coordStack.push(Coord(P.r() - 1, P.c()));
			maze[P.r()-1][P.c()] = 'P';	
		}
		if (maze[P.r()][P.c()+1] != 'X' && maze[P.r()][P.c()+1] != 'P') //east
		{
			coordStack.push(Coord(P.r(), P.c()+1));
			maze[P.r()][P.c()+1] = 'P';
		}
		if (maze[P.r()+1][P.c()] != 'X' && maze[P.r()+1][P.c()] != 'P')//south
		{
			coordStack.push(Coord(P.r()+1, P.c()));
			maze[P.r()+1][P.c()] = 'P';
		}
		if (maze[P.r()][P.c()-1] != 'X' && maze[P.r()][P.c()-1] != 'P')//west
		{
			coordStack.push(Coord(P.r(), P.c()-1));
			maze[P.r()][P.c()-1] = 'P';
		}
	}
	return false;

	
}
