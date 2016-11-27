#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <stack>
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
const unsigned int SHOOT = 19;
const unsigned int GOODIES = 20;
class StudentWorld;

class Actor: public GraphObject
{
public: 
	StudentWorld* m_SW;
	Actor(int imageID, int startX, int startY, Direction startDirection, int sub_level, StudentWorld* n_SW): 
		GraphObject(imageID, startX, startY, startDirection, sub_level), m_Alive(true), m_SW(n_SW)
	{}
	virtual void doSomething() = 0;
	virtual bool Interactions(unsigned int obj) = 0;
	bool isAlive()
	{
		return m_Alive;
	}
	void setAlive(bool n)
	{
		m_Alive = n;
	}
	
private:
	bool m_Alive;
};
class Goodies : public Actor
{
public:
	Goodies(int imageID, int startX, int startY,
		int sub_level, StudentWorld* n_SW) :
		Actor(imageID, startX, startY, GraphObject::none, sub_level, n_SW)
	{
		setVisible(true);
	}
	virtual void doSomething();
};
class MortalObjects : public Actor
{
public:
	MortalObjects(int imageID, int startX, int startY, Direction startDirection, int sub_level, int n_hp, StudentWorld* n_SW) :
		Actor(imageID, startX, startY, startDirection, sub_level, n_SW), m_hp(n_hp)
	{

	}
	void sethp(int n_hp)
	{
		m_hp = n_hp;
	}

	int gethp() const
	{
		return m_hp;
	}
	void dammage(int dam)
	{
		m_hp -= dam;
		if (m_hp < 0)
			m_hp = 0;
	}
	virtual bool Interactions(unsigned int obj) = 0;

private:
	int m_hp;

};
class Sentient : public MortalObjects
{
public: 
	Sentient(int imageID, int startX, int startY, Direction startDirection, int sub_level, int n_hp, StudentWorld* n_SW): 
		MortalObjects(imageID, startX, startY, startDirection,sub_level,n_hp, n_SW) {}
	virtual bool Interactions(unsigned int obj);
	virtual void Movement();
	virtual bool ShootAtPlayer();
private:
	int m_hp;
};
class Statics : public Actor
{
public:
	Statics(unsigned int id, int startX, int startY, int sub_level, StudentWorld* n_SW) :
		Actor(id, startX, startY, GraphObject::none, sub_level, n_SW)
	{

	}
	virtual void doSomething();
	virtual bool Interactions(unsigned int obj);

};

class Player : public Sentient
{
public:
	Player(int startX, int startY, int sub_level, StudentWorld* n_SW):
		Sentient(IID_PLAYER, startX, startY, GraphObject::right, sub_level, 20, n_SW),
		m_Ammo(0)
	{
		setVisible(false);
	}
	virtual void doSomething();
	int getAmmo()
	{
		return m_Ammo;
	}
	void setAmmo(int n_Ammo)
	{
		m_Ammo = n_Ammo;
	}
	void addAmmo(int n_Ammo)
	{
		m_Ammo += n_Ammo;
	}
	bool useAmmo()
	{
		if (m_Ammo == 0)
			return false;
		m_Ammo--;
		return true;
	}
	virtual bool Interactions(unsigned int obj);
	virtual void Movement();
	
private:
	int m_Ammo;
};

class Gangster : public Sentient
{
public:
	Gangster(int startX, int startY, int sub_level, Direction dir, StudentWorld* n_SW);
	virtual void doSomething();
	virtual bool Interactions(unsigned int obj);

private:
	int m_ticks;
	int m_counter;
};

class Bully : public Sentient
{
public:
	Bully(int startX, int startY, int sub_level, StudentWorld* n_SW);
	virtual void doSomething();
	virtual bool Interactions(unsigned int obj);
	virtual void Movement();
	void MovementObstructed();
	int distanceBeforeTurning();
	int directionRandomize(int i);
	void dropGoodies();
	
private:
	int m_ticks;
	int m_counter;
	int m_walkCounter;
	int m_distance;
	std::stack<unsigned int> m_bullyBag;

	bool MoveRight();
	bool MoveLeft();
	bool MoveUp();
	bool MoveDown();

	bool foundGoodies();

};

class RobotBoss : public Sentient
{
public:
	RobotBoss(int startX, int startY, int sub_level, StudentWorld* n_SW);
	virtual void doSomething();
	virtual bool Interactions(unsigned int obj);
private:
	int m_ticks;
	int m_counter;
};

class Bullet : public Actor
{
public:
	Bullet(int startX, int startY, Direction startDirection,
		int sub_level, StudentWorld* n_SW):
		Actor(IID_BULLET, startX, startY, startDirection, sub_level, n_SW)
	{
		setVisible(true);
	}
	virtual void doSomething();
	virtual bool Interactions(unsigned int obj);
};

class Extralife : public Goodies
{
public:
	Extralife(int startX, int startY,
		int sub_level, StudentWorld* n_SW) :
		Goodies(IID_EXTRA_LIFE, startX, startY,
			sub_level, n_SW)
	{

	}
	virtual bool Interactions(unsigned int obj);
};

class Restorehealth : public Goodies
{
public:
	Restorehealth(int startX, int startY,
		int sub_level, StudentWorld* n_SW) :
		Goodies(IID_RESTORE_HEALTH, startX, startY,
			sub_level, n_SW)
	{

	}
	virtual bool Interactions(unsigned int obj);
};

class Ammo : public Goodies
{
public: 
	Ammo(int startX, int startY,
		int sub_level, StudentWorld* n_SW) :
		Goodies(IID_AMMO, startX, startY,
			sub_level, n_SW)
	{
		
	}
	virtual bool Interactions(unsigned int obj);

}; 

class FarplaneGun : public Goodies
{
public:
	FarplaneGun(int startX, int startY,
		int sub_level, StudentWorld* n_SW) :
		Goodies(IID_FARPLANE_GUN, startX, startY,
			sub_level, n_SW)
	{

	}
	virtual bool Interactions(unsigned int obj);
};

class Wall : public Statics
{
public:
	Wall(int startX, int startY, int sub_level) :
		Statics(IID_WALL, startX, startY, sub_level, nullptr)
	{
		setVisible(true);
	}
};

class FakeWall : public Statics
{
public:
	FakeWall(int startX, int startY, int sub_level) :
		Statics(IID_FAKE_WALL, startX, startY, sub_level, nullptr)
	{
		setVisible(true);
	}
};

class Waterpool : public MortalObjects
{
public: 
	Waterpool(int startX, int startY, int sub_level, StudentWorld* n_SW) :
		MortalObjects(IID_WATERPOOL, startX, startY, none, sub_level, 30, n_SW) 
	{
		setVisible(true);
	}
	virtual void doSomething();
	virtual bool Interactions(unsigned int obj);

};

class Hostage : public Goodies
{
public:
	Hostage(int startX, int startY,
		int sub_level, StudentWorld* n_SW) :
		Goodies(IID_HOSTAGE, startX, startY,
			sub_level, n_SW)
	{

	}
	virtual bool Interactions(unsigned int obj);
};

class Gold : public Actor
{
public: 
	Gold(int startX, int startY, int sub_level, StudentWorld* n_SW) :
		Actor(IID_GOLD, startX, startY, GraphObject::none, sub_level, n_SW)
	{
		setVisible(true);
	}

	virtual void doSomething();
	virtual bool Interactions(unsigned int obj);
}; 

class BullyNest : public Actor
{
public:
	BullyNest(int startX, int startY, int sub_level, StudentWorld* n_SW) :
		Actor(IID_BULLY_NEST, startX, startY, GraphObject::none, sub_level, n_SW)
	{
		setVisible(true);
	}
	virtual void doSomething();
	virtual bool Interactions(unsigned int obj);
	bool chanceTocreateNewBully();

};

class Exit : public Statics
{
public:
	Exit(int startX, int startY, int sub_level, StudentWorld* n_SW) :
		Statics(IID_EXIT, startX, startY, sub_level, n_SW)
	{
		setVisible(false);
	}
	virtual void doSomething();
};

class Gate : public Actor
{

public: 
	Gate(int gateNumber,int startX, int startY, int sub_level, StudentWorld* n_SW) :
		Actor(IID_GATE, startX, startY, GraphObject::none, sub_level, n_SW), m_gateNumber(gateNumber)
	{
		setVisible(true);
	}
	virtual void doSomething();
	int getGateNumber()
	{
		return m_gateNumber;
	}
	virtual bool Interactions(unsigned int obj);
	
private:
	int m_gateNumber;
};







#endif // ACTOR_H_
