
#include "globals.h"
#include "Game.h"
#include <iostream>
#include <ctime>
using namespace std;
///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
	// Initialize the random number generator.  (You don't need to
	// understand how this works.)
	srand(static_cast<unsigned int>(time(0)));

	// Create a game
	// Use this instead to create a mini-game:   Game g(3, 3, 2);
	Game g(9, 10, 40);

	// Play the game
	g.play();
}

/*
#include "Game.h"
#include "Game.h"
#include "Pit.h"
#include "Pit.h"
#include "History.h"
#include "History.h"
#include "Player.h"
#include "Player.h"
#include "Snake.h"
#include "Snake.h"
#include "globals.h"
#include "globals.h"
int main()
{}
*/
/*
#include "History.h"
int main()
{
	History h(2, 2);
	h.record(1, 1);
	h.display();
}
*/
/*
#include "Snake.h"
int main()
{
	Snake s(nullptr, 1, 1);
}
*/
/*
#include "Player.h"
int main()
{
	Player p(nullptr, 1, 1);
}
*/
/*
#include "Pit.h"
int main()
{
	Pit pt(10, 18);
	pt.addPlayer(2, 2);
}
*/
/*
#include "globals.h"
#include "Player.h"
#include "Pit.h"
int main()
{
	Pit pt(10, 20);
	Player p(&pt, 2, 3);
}
*/
/*
#include "Pit.h"
#include "Player.h"
int main()
{
	Pit pt(10, 20);
	Player p(&pt, 2, 3);
}
*/
/*
#include "Player.h"
#include "Pit.h"
int main()
{
	Pit pt(10, 20);
	Player p(&pt, 2, 3);
}
*/
/*
#include "Pit.h"
#include "History.h"
#include "Player.h"
#include "globals.h"
int main()
{
	Pit pt(3, 3);
	pt.addPlayer(1, 1);
	pt.addSnake(1, 2);
	pt.addSnake(2, 2);
	pt.addSnake(2, 3);
	pt.player()->move(RIGHT);
	pt.player()->move(LEFT);
	pt.player()->move(DOWN);
	pt.player()->move(RIGHT);
	pt.player()->move(RIGHT);
	pt.player()->move(UP);
	pt.history().display();
}
*/
/*
#include "Player.h"
#include "Pit.h"
int main()
{
	Pit pt(10, 20);
	Player p(&pt, 2, 3);
	Snake s(&pt, 1, 1);
}
*/
/*
#include "globals.h"
#include "Snake.h"
#include "Player.h"
int main()
{
	Pit pt(10, 10);
}
*/
/*
#include "History.h"
int main()
{
	History h;
}
*/