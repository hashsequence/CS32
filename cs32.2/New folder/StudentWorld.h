#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include <stack>
#include "Actor.h"
#include "Level.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	std::vector<std::vector<Actor*>> m_Actor;
	Player* m_Player;
	std::stack<Actor*> retrieveAllGoodiesat(int x, int y, int sub_level);
	std::stack<Actor*> retrieveAllGruntssat(int x, int y, int sub_level);
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir), m_Actor(MAX_SUB_LEVEL),
		m_PlayerContainer(MAX_SUB_LEVEL /*, std::vector<Actor*>(15*15)*/),
		m_Player(nullptr), m_SubLevel(0), m_TimeLimit(3000), m_LevelFinished(false)
	{

	}
	~StudentWorld()
	{
		cleanUp();
	}

	virtual int init();

	virtual int move();

	virtual void cleanUp();

    
    virtual int getCurrentSubLevel()
    {
        return m_SubLevel; // This code is here merely to allow the skeleton to build.
    }
	bool CheckAt(int x, int y, int sub_level, std::stack<unsigned int>& stack_id );
	bool checkAtForPlayer(int x, int y, int sub_level);
	bool fulfilledReqs();
	void finishedLevel();
	unsigned int getCurrentTimeLimit()
	{
		return m_TimeLimit;
	}
	void setDisplaySet();

	//interactions between Actors
	bool bulletDamageSentient(unsigned int obj, Bullet* bulletptr);
	void setCurrentSubLevel(int SubLevel);
	void increaseAmmo()
	{
		m_Player->addAmmo(25);
	}
	void FarplaneDamage(int x, int y, int sub_level);
	bool scanAreaForBullies(int x, int y, int sub_level, BullyNest* ptr);


private:
	std::vector<std::vector<Player*>> m_PlayerContainer;
	unsigned int m_TimeLimit;
	int m_SubLevel;
	bool m_LevelFinished;

	int LoadMainLevel();
	int LoadSubLevels(int sublevel);
	void reduceTimeLimitByOne();
	void ActorsDoSomething();
	void cleanTheDead();
	std::string formatString(int score, int level, int sublevel, int lives, double hp, int ammo,
		unsigned int timelimit);
	Actor* find(unsigned int ID, int x, int y, int sub_level);
};

#endif // STUDENTWORLD_H_
