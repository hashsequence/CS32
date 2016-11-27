
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

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	Coord start(sr, sc);
	Coord end(er, ec);
	Coord P(start);
	if (sr == er && sc == ec)
	{
		return true;
	}
	maze[sr][sc] = 'P';
	if (maze[P.r() - 1][P.c()] != 'X' && maze[P.r() - 1][P.c()] != 'P') // north
	{
		if (pathExists(maze, P.r() - 1, P.c(), end.r(), end.c()))
			return true;
	}
	if (maze[P.r()][P.c() + 1] != 'X' && maze[P.r()][P.c() + 1] != 'P') //east
	{
		if (pathExists(maze, P.r(), P.c() + 1, end.r(), end.c()))
			return true;
	}
	if (maze[P.r() + 1][P.c()] != 'X' && maze[P.r() + 1][P.c()] != 'P')//south
	{
		if (pathExists(maze, P.r() + 1, P.c(), end.r(), end.c()))
			return true;
	}
	if (maze[P.r()][P.c() - 1] != 'X' && maze[P.r()][P.c() - 1] != 'P')//west
	{
		if (pathExists(maze, P.r(), P.c() - 1, end.r(), end.c()))
			return true;
	}
	return false;
}
