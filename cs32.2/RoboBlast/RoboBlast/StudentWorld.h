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

	StudentWorld(std::string assetDir);
	~StudentWorld();
	virtual int init();
	virtual int move();
	virtual void cleanUp();

    //get functions
	virtual int getCurrentSubLevel();
	bool CheckAt(int x, int y, std::stack<unsigned int>& stack_id );
	bool checkAtForPlayer(int x, int y);
	bool scanAreaForBullies(int x, int y, BullyNest* ptr);
	unsigned int getCurrentTimeLimit();
	bool fulfilledReqs();
	std::stack<Actor*> retrieveAllGoodiesat(int x, int y);
	std::stack<Actor*> retrieveAllGruntssat(int x, int y);

	//Mutator functions
	void finishedLevel();
	void setDisplaySet();
	bool bulletDamageSentient(unsigned int obj, Bullet* bulletptr);
	void setCurrentSubLevel(int SubLevel);
	void increaseAmmo();
	void FarplaneDamage(int x, int y);
	

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
