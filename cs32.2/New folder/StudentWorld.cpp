#include "StudentWorld.h"
#include "Actor.h"
#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
Actor* StudentWorld::find(unsigned int ID, int x, int y, int sub_level)
{
	vector<Actor*>* it1 = &m_Actor[sub_level];
	for (vector<Actor*>::iterator it2 = it1->begin(); it2 != it1->end(); it2++)
	{
		if ((*it2)->getID() == ID && (*it2)->getX() == x && (*it2)->getY() == y && (*it2)->isVisible() == true)
		{
			return *it2;
		}
	}
	return m_Actor[0][0];
}
int StudentWorld::init()
{
	int mainlev = -1;
	int sublev = -5;
	mainlev = LoadMainLevel();
	if (mainlev == -1)
		return GWSTATUS_LEVEL_ERROR;
	if (mainlev == 2)
	{
		return GWSTATUS_PLAYER_WON;
	}
	sublev = LoadSubLevels(1);
	if (sublev == -1)
		return GWSTATUS_LEVEL_ERROR;
	return GWSTATUS_CONTINUE_GAME;
}
int StudentWorld::move()
{
	setDisplaySet();
	ActorsDoSomething();
	cleanTheDead();
	if (m_TimeLimit != 0)
	{
		reduceTimeLimitByOne();
	}
	if (m_Player->isAlive() == false || this->getLives() == 0)
		return GWSTATUS_PLAYER_DIED;
	if (m_LevelFinished == true)
	{
		increaseScore(1500);
		increaseScore(m_TimeLimit);
		m_TimeLimit = 3000;
		m_LevelFinished = false;
		return GWSTATUS_FINISHED_LEVEL;
	}
	return GWSTATUS_CONTINUE_GAME;
}
void StudentWorld::cleanUp()
{
	for (std::vector<std::vector<Actor*>>::iterator it1 = m_Actor.begin(); it1 != m_Actor.end(); it1++)
	{
		for (std::vector<Actor*>::iterator it2 = it1->begin(); it2 != it1->end();)
		{
			delete (*it2);
			it2 = it1->erase(it2);
		}
	}
	for (std::vector<std::vector<Player*>>::iterator it1 = m_PlayerContainer.begin(); it1 != m_PlayerContainer.end(); it1++)
	{
		for (std::vector<Player*>::iterator it2 = it1->begin(); it2 != it1->end();)
		{
			delete (*it2);
			it2 = it1->erase(it2);
		}
	}
	m_SubLevel = 0;
}

bool StudentWorld::CheckAt(int x, int y, int sub_level, stack<unsigned int>& stack_id)
{
	    vector<Actor*>* it1 = &m_Actor[sub_level];
		for (vector<Actor*>::iterator it2 = it1->begin(); it2 != it1->end(); it2++)
		{
			if ((*it2)->getX() == x && (*it2)->getY() == y && (*it2)->isVisible() == true)
			{
				stack_id.push((*it2)->getID());
			}
		}
		return !(stack_id.empty());
}

void StudentWorld::ActorsDoSomething()
{

		vector<Actor*>* it1 = &m_Actor[this->getCurrentSubLevel()];

		for (vector<Actor*>::iterator it2 = it1->begin(); it2 != it1->end(); it2++)
		{
			if ((*it2)->getID() != IID_BULLET && (*it2)->getID() != IID_GANGSTER
				&& (*it2)->getID() != IID_ROBOT_BOSS && (*it2)->getID() != IID_BULLY
				&& (*it2)->getID() != IID_BULLY_NEST)
					(*it2)->doSomething();
		}
		for (vector<Actor*>::iterator it2 = it1->begin(); it2 != it1->end(); it2++)
		{
			if ((*it2)->getID() == IID_BULLET)
				(*it2)->doSomething();
		}
		for (vector<Actor*>::iterator it2 = it1->begin(); it2 != it1->end(); it2++)
		{
			if ((*it2)->getID() == IID_BULLY_NEST)
				(*it2)->doSomething();
		}
		for (vector<Actor*>::iterator it2 = it1->begin(); it2 != it1->end(); it2++)
		{
			if ((*it2)->getID() == IID_GANGSTER || (*it2)->getID() == IID_ROBOT_BOSS || (*it2)->getID() == IID_BULLY)
				(*it2)->doSomething();
		}
		m_Player->doSomething();
		
}

int StudentWorld::LoadMainLevel()
{
	string curLevel = "";
	int L = getLevel();
	if (L <= 9 && L >= 0)
	{
		curLevel = "level0";
		curLevel += (L + 48);
		curLevel += ".dat";
	}
	else if (L > 9 && L < 100)
	{
		int L1 = L % 10;
		curLevel = "level";
		curLevel += (((L - L1)/10) + 48);
		curLevel += ((L % 10) + 48);
		curLevel += ".dat";
	}

	Level lev(assetDirectory());
	Level::LoadResult result = lev.loadLevel(curLevel);

	if (result == Level::load_fail_bad_format)
		return -1; // something bad happened! 
	if (result == Level::load_fail_file_not_found)
		return 2;

	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			Level::MazeEntry item = lev.getContentsOf(x, y, 0);
			if (item == Level::player)
			{
				m_Player = new Player(x, y, 0, this);
				m_Player->setVisible(true);
				m_PlayerContainer[0].push_back(m_Player);
			}
			else if (item == Level::vert_gangster)
			{
				
				Gangster* t_Gangster = new Gangster(x, y, 0, GraphObject::down, this);
				m_Actor[0].push_back(t_Gangster);
			}
			else if (item == Level::horiz_gangster)
			{

				Gangster* t_Gangster = new Gangster(x, y, 0, GraphObject::right, this);
				m_Actor[0].push_back(t_Gangster);
			}
			else if (item == Level::robot_boss)
			{

				RobotBoss* t_Robotboss = new RobotBoss(x, y, 0, this);
				m_Actor[0].push_back(t_Robotboss);
			}
			else if (item == Level::wall)
			{
				Wall* t_Wall = new Wall(x, y, 0);
				m_Actor[0].push_back(t_Wall);
			}

			else if (item == Level::fake_wall)
			{
				FakeWall* t_FakeWall = new FakeWall(x, y, 0);
				m_Actor[0].push_back(t_FakeWall);
			}

			else if (item == Level::gold)
			{
				Gold* t_Gold = new Gold(x, y, 0, this);
				m_Actor[0].push_back(t_Gold);
			}

			else if (item == Level::ammo)
			{
				Ammo* t_Ammo = new Ammo(x, y, 0, this);
				m_Actor[0].push_back(t_Ammo);
			}

			else if (item == Level::extra_life)
			{
				Extralife* t_Extralife = new Extralife(x, y, 0, this);
				m_Actor[0].push_back(t_Extralife);
			}

			else if (item == Level::restore_health)
			{
				Restorehealth* t_Restorehealth = new Restorehealth(x, y, 0, this);
				m_Actor[0].push_back(t_Restorehealth);
			}

			else if (item == Level::hostage)
			{
				Hostage* t_Hostage = new Hostage(x, y, 0, this);
				m_Actor[0].push_back(t_Hostage);
			}

			else if (item == Level::farplane_gun)
			{
				FarplaneGun* t_FarplaneGun = new FarplaneGun(x, y, 0, this);
				m_Actor[0].push_back(t_FarplaneGun);
			}

			else if (item == Level::gate1)
			{
				Gate* t_Gate = new Gate(1, x, y, 0, this);
				m_Actor[0].push_back(t_Gate);
			}
			else if (item == Level::gate2)
			{
				Gate* t_Gate = new Gate(2, x, y, 0, this);
				m_Actor[0].push_back(t_Gate);
			}				
			else if (item == Level::gate3)
			{
				Gate* t_Gate = new Gate(3, x, y, 0, this);
				m_Actor[0].push_back(t_Gate);
			}
			else if (item == Level::exit)
			{
				Exit* t_Exit = new Exit(x, y, 0, this);
				m_Actor[0].push_back(t_Exit);
			}

			else if (item == Level::bully_nest)
			{
				BullyNest* t_BullyNest = new BullyNest(x, y,0, this);
				m_Actor[0].push_back(t_BullyNest);
			}
			
		}
	}
	return 1;
}

int StudentWorld::LoadSubLevels(int m_SubLevelsCreation)
{
	string currSubLevel = "";
	int L = getLevel();
	int S_L = m_SubLevelsCreation;
	
	if (L <= 9 && L >= 0)
	{
		currSubLevel = "level0";
		currSubLevel += (L + 48);
		currSubLevel += "_";
		currSubLevel += (S_L + 48);
		currSubLevel += ".dat";
	}

	Level lev(assetDirectory());
	Level::LoadResult result = lev.loadLevel(currSubLevel, m_SubLevelsCreation);
	
	if (result == Level::load_sublevel_fail_bad_format)
		return -1; // something bad happened! 
	if (result == Level::load_sublevel_fail_file_not_found || m_SubLevelsCreation >=	 MAX_SUB_LEVEL)
		return 0;
	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			Level::MazeEntry item = lev.getContentsOf(x, y, m_SubLevelsCreation);
			if (item == Level::player)
			{
				Player* t_Player = new Player(x, y, m_SubLevelsCreation, this);
				t_Player->setVisible(true);
				m_PlayerContainer[m_SubLevelsCreation].push_back(t_Player);
			}

			else if (item == Level::vert_gangster)
			{

				Gangster* t_Gangster = new Gangster(x, y, m_SubLevelsCreation, GraphObject::down, this);
				m_Actor[m_SubLevelsCreation].push_back(t_Gangster);
			}
			else if (item == Level::horiz_gangster)
			{

				Gangster* t_Gangster = new Gangster(x, y, m_SubLevelsCreation, GraphObject::right, this);
				m_Actor[m_SubLevelsCreation].push_back(t_Gangster);
			}
			else if (item == Level::robot_boss)
			{

				RobotBoss* t_Robotboss = new RobotBoss(x, y, m_SubLevelsCreation, this);
				m_Actor[m_SubLevelsCreation].push_back(t_Robotboss);
			}
			else if (item == Level::wall)
			{
				Wall* t_Wall = new Wall(x, y, m_SubLevelsCreation);
				m_Actor[m_SubLevelsCreation].push_back(t_Wall);
			}

			else if (item == Level::fake_wall)
			{
				FakeWall* t_FakeWall = new FakeWall(x, y, m_SubLevelsCreation);
				m_Actor[m_SubLevelsCreation].push_back(t_FakeWall);
			}
			else if (item == Level::gold)
			{
				Gold* t_Gold = new Gold(x, y, m_SubLevelsCreation, this);
				m_Actor[m_SubLevelsCreation].push_back(t_Gold);
			}
			else if (item == Level::ammo)
			{
				Ammo* t_Ammo = new Ammo(x, y, m_SubLevelsCreation, this);
				m_Actor[m_SubLevelsCreation].push_back(t_Ammo);
			}

			if (item == Level::extra_life)
			{
				Extralife* t_Extralife = new Extralife(x, y, m_SubLevelsCreation, this);
				m_Actor[m_SubLevelsCreation].push_back(t_Extralife);
			}

			else if (item == Level::restore_health)
			{
				Restorehealth* t_Restorehealth = new Restorehealth(x, y, m_SubLevelsCreation, this);
				m_Actor[m_SubLevelsCreation].push_back(t_Restorehealth);
			}

			else if (item == Level::hostage)
			{
				Hostage* t_Hostage = new Hostage(x, y, m_SubLevelsCreation, this);
				m_Actor[m_SubLevelsCreation].push_back(t_Hostage);
			}

			else if (item == Level::farplane_gun)
			{
				FarplaneGun* t_FarplaneGun = new FarplaneGun(x, y, m_SubLevelsCreation, this);
				m_Actor[m_SubLevelsCreation].push_back(t_FarplaneGun);
			}

			else if (item == Level::gate0)
			{
				Gate* t_Gate = new Gate(0,x, y, m_SubLevelsCreation, this);
				m_Actor[m_SubLevelsCreation].push_back(t_Gate);
			}
			else if (item == Level::bully_nest)
			{
				BullyNest* t_BullyNest = new BullyNest(x, y, m_SubLevelsCreation, this);
				m_Actor[m_SubLevelsCreation].push_back(t_BullyNest);
			}
		}
	}
	
	LoadSubLevels(m_SubLevelsCreation+1);
	return 1;
}

bool StudentWorld::checkAtForPlayer(int x, int y, int sub_level)
{
	vector<Player*>* it0 = &m_PlayerContainer[sub_level];
	for (vector<Player*>::iterator it = it0->begin(); it != it0->end(); it++)
	{
		if ((*it)->getID() == IID_PLAYER && (*it)->getX() == x && (*it)->getY() == y && (*it)->isVisible() == true)
		{
			return true;
		}
	}
	return false;
}

void StudentWorld::cleanTheDead()
{
	for (std::vector<std::vector<Actor*>>::iterator it1 = m_Actor.begin(); it1 != m_Actor.end(); it1++)
	{
		for (std::vector<Actor*>::iterator it2 = it1->begin(); it2 != it1->end();)
		{
			if ((*it2)->isAlive() == false)
			{
				delete (*it2);
				it2 = it1->erase(it2);
			}
			else
			{
				it2++;
			}
			
		}
	}
}

void StudentWorld::setCurrentSubLevel(int SubLevel)
{
	int t_hp = m_Player->gethp();
	int t_ammo = m_Player->getAmmo();
	
	vector<Player*>* it0 = &m_PlayerContainer[SubLevel];
	for (vector<Player*>::iterator it = it0->begin(); it != it0->end(); it++)
		{
			m_Player = *it;
			m_Player->sethp(t_hp);
			m_Player->setAmmo(t_ammo);
		}
	m_SubLevel = SubLevel;
	return;
}

void StudentWorld::reduceTimeLimitByOne()
{
	m_TimeLimit--;
}

string StudentWorld::formatString(int score, int level, int sublevel, int lives, double hp, int ammo, unsigned int timelimit)
{
	ostringstream oss;
	string s = "";
	oss << "Score: ";

	if (score >= 0 && score < 10)
	{
		for (int i = 0; i < 5; i++)
			oss << 0;
		oss << score;
	}
	else if (score >= 10 && score < 100)
	{
		for (int i = 0; i < 4; i++)
			oss << 0;
		oss << score;
	}
	else if (score >= 100 && score < 1000)
	{
		for (int i = 0; i < 3; i++)
			oss << 0;
		oss << score;
	}
	else if (score >= 1000 && score < 10000)
	{
		for (int i = 0; i < 2; i++)
			oss << 0;
		oss << score;
	}
	else if (score >= 10000 && score < 100000)
	{
		for (int i = 0; i < 1; i++)
			oss << 0;
		oss << score;
	}
	else if (score >= 100000 && score < 1000000)
	{
		oss << score;
	}
	
	oss << "  Level: ";
	if (level > 10)
		oss << setw(2) << level;
	if (level < 10 && level >= 0)
		oss << 0 << level;
	if (sublevel > 10)
		oss << "-" << setw(2) << sublevel;
	if (sublevel < 10)
		oss << "-" << 0 << sublevel;
		oss << "  Lives: " << setw(2) << lives << "  Health: " << setw(3) << ((hp / 20) * 100) << "%"
		<< "  Ammo: " << setw(3) << ammo << "  TimeLimit: " <<	setw(4) << timelimit;
	s += oss.str();
	return s;
}

void StudentWorld::setDisplaySet()
{
	int score = getScore();
	int level = getLevel(); // (e.g. 03)
	int subLevel = getCurrentSubLevel(); // (e.g. 01. 00 is for main level)
	unsigned int timeLimit = getCurrentTimeLimit();
	int livesLeft = getLives();

	string s = formatString(score, level, subLevel, livesLeft, m_Player->gethp(), m_Player->getAmmo(), timeLimit);
	setGameStatText(s);
}

bool StudentWorld::bulletDamageSentient(unsigned int obj, Bullet* bulletptr)
{
	if (obj == IID_PLAYER) // damages player
	{
		m_Player->Interactions(IID_BULLET);
		bulletptr->setAlive(false);
		return true;
	}
	if (obj == IID_GANGSTER || obj == IID_ROBOT_BOSS)
	{
		find(obj, bulletptr->getX(), bulletptr->getY(),getCurrentSubLevel())->Interactions(IID_BULLET);
		bulletptr->setAlive(false);
		return true;
	}
	if (obj == IID_BULLY)
	{
		find(obj, bulletptr->getX(), bulletptr->getY(), getCurrentSubLevel())->Interactions(IID_BULLET);
		bulletptr->setAlive(false);
		return true;
	}
	return false;
}

stack<Actor*> StudentWorld::retrieveAllGoodiesat(int x, int y, int sub_level)
{
	stack<Actor*> goodiesstack;
	vector<Actor*>* it1 = &m_Actor[sub_level];
	for (vector<Actor*>::iterator it2 = it1->begin(); it2 != it1->end(); it2++)
	{
		if ((*it2)->getX() == x && (*it2)->getY() == y && 
			((*it2)->getID() == IID_RESTORE_HEALTH || (*it2)->getID() == IID_AMMO || (*it2)->getID() == IID_EXTRA_LIFE))
		{
			goodiesstack.push((*it2));
			playSound(SOUND_BULLY_MUNCH);
		}
	}
	return goodiesstack;
}

stack<Actor*> StudentWorld::retrieveAllGruntssat(int x, int y, int sub_level)
{
	stack<Actor*> gruntsstack;
	vector<Actor*>* it1 = &m_Actor[sub_level];
	for (vector<Actor*>::iterator it2 = it1->begin(); it2 != it1->end(); it2++)
	{
		if ((*it2)->getX() == x && (*it2)->getY() == y &&
			((*it2)->getID() == IID_BULLY || (*it2)->getID() == IID_GANGSTER))
		{
			gruntsstack.push((*it2));
		}
	}
	return gruntsstack;
}

bool StudentWorld::fulfilledReqs()
{
	for (std::vector<std::vector<Actor*>>::iterator it1 = m_Actor.begin(); it1 != m_Actor.end(); it1++)
	{
		for (std::vector<Actor*>::iterator it2 = it1->begin(); it2 != it1->end();it2++)
		{
			if ((*it2)->getID() == IID_GOLD || (*it2)->getID() == IID_HOSTAGE || (*it2)->getID() == IID_ROBOT_BOSS)
			{
				return false;
			}
		}
	}
	return true;
}

void StudentWorld::finishedLevel()
{
	m_LevelFinished = true;
}

void StudentWorld::FarplaneDamage(int x, int y, int sub_level)
{
	for (int i = x - 4; i < x + 5; i++)
	{
		for (int j = y - 4; j < y + 5; j++)
		{
			stack<Actor*> gruntsstack(retrieveAllGruntssat(i, j, sub_level));
			while (gruntsstack.empty() == false)
			{
				(gruntsstack.top())->Interactions(IID_FARPLANE_GUN);
				gruntsstack.pop();
			}
		}
	}
}

bool StudentWorld::scanAreaForBullies(int x, int y, int sub_level, BullyNest* ptr)	
{
	stack<unsigned int> scan;
	int count = 0;
	bool BullyOnNest = false;
	for (int i = x - 3; i < x + 4; i++)
	{
		for (int j = y - 3; j < y + 4; j++)
		{
			this->CheckAt(i, j, sub_level, scan);
			while (scan.empty() == false)
			{
				if (scan.top() == IID_BULLY)
				{
					count++;
					if (ptr->getX() == x, ptr->getY() == y)
					{
						BullyOnNest = true;
					}
				}
				scan.pop();
			}
		}
	}	
	if (count < 3 && BullyOnNest == false)
	{
		return true;
	}
	return false;
}



