#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <stack>
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

const unsigned int SHOOT = 19; // this constant is for the Interactions function for sentient which indicates the sentient to shoot
const unsigned int GOODIES = 20; // this constant is for the Bully to tell that there is a goody that can be picked up 

class StudentWorld;
/*Actor is my base class for all my objects and has a two pure virtual functions that it passes down
the doSomething()) function and the Interactions() function, the interactions function is a function that
dictates how each of the object will react when in contact with other Actors*/
class Actor: public GraphObject
{
public: 
	StudentWorld* m_SW;
	Actor(int imageID, int startX, int startY, Direction startDirection, int sub_level, StudentWorld* n_SW);
	virtual void doSomething() = 0;
	virtual bool Interactions(unsigned int obj) = 0;
	bool isAlive();
	void setAlive(bool n);
	
private:
	bool m_Alive;
};

/*Goodies is a child class of Actor and a base class for FarplaneGun, Restorehealth, Extralife, and Ammo
it is an abstract class, but it has an implementation of dosomething, but calls the interactions function depending on
what type of goody it is */
class Goodies : public Actor
{
public:
	Goodies(int imageID, int startX, int startY,
		int sub_level, StudentWorld* n_SW);
	virtual void doSomething();
};

/*MortalObjects is a child class of Actor and a parent class of the the sentient class and water pool
dictates how the hit points will work*/
class MortalObjects : public Actor
{
public:
	MortalObjects(int imageID, int startX, int startY, Direction startDirection, int sub_level, int n_hp, StudentWorld* n_SW);
	void sethp(int n_hp);
	int gethp() const;
	void dammage(int dam);
	virtual bool Interactions(unsigned int obj) = 0;

private:
	int m_hp;

};

/*child class of MortalObjects and parent class of Gangster, robotboss, bullies, and player
has a movement function that dictates how the robotboss and the gangsters will move
and has a shootAtPlayer function that dictates how the gangsters, robotboss, and bullies will shoot 
the sentient interactions function have the shoot function for all my sentient classes
*/
class Sentient : public MortalObjects
{
public: 
	Sentient(int imageID, int startX, int startY, Direction startDirection, int sub_level, int n_hp, StudentWorld* n_SW);
	virtual bool Interactions(unsigned int obj);
	virtual void Movement();
	virtual bool ShootAtPlayer();
};

/*is a child class of Actor and a parent class for wall, fakewall, and exit
it does nothing, but is a abstract class*/
class Statics : public Actor
{
public:
	Statics(unsigned int id, int startX, int startY, int sub_level, StudentWorld* n_SW);
	virtual void doSomething();
};

/*the player is a derived class of sentient, and has functions that manages the ammo
the movement function detects whether the user has press corresponding keys that either shoots,
move, or decrement lives*/
class Player : public Sentient
{
public:
	Player(int startX, int startY, int sub_level, StudentWorld* n_SW);
	virtual void doSomething();
	int getAmmo();
	void setAmmo(int n_Ammo);
	void addAmmo(int n_Ammo);
	bool useAmmo();
	virtual bool Interactions(unsigned int obj);
	virtual void Movement();
	
private:
	int m_Ammo;
};

/*gangster is a derived class of my sentient class, and uses the movement method of the sentient class, 
the doSomthing function implemented detects how many action it does per ticks and either shoots the player or moves or 
turn around. Its Interactions function dictates how it reacts to other objects, with bullets it gets damaged, with the farplanegun it gets 
killed*/
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

/*derived class of sentient

the bully operates and rest on certain ticks

when it acts it checks if there is a goody through foundgoodies()
when it dies it calls dropGoodies and resinserts the goodies into the actor containter
the distancebeforeturning dictates when the bully changes direction after a certain amount amount of steps
the directionrandomize chooses a random number from 1 to 4 corresponding to the four directions.
the movement function moves the bully and calls movementobstructed when bully is obstructed
movementobstructed() is called when obstructed or when it has already walked in a certain direction in 6 steps
then calls the distancerandomize to reset the the walkcounter
the bully's Interaction function checks if there are goodies around to be picked up, and gets killed if within the farplaneDamage vicinity*/
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

/*is the same as a horizontal gangster and has 50 hp instead of 10*/
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

/*checks the objects in its current location and checks if there is a sentient object, and damages the sentient
by calling its interactions function 
gets destroyed if encounters a wall, waterpool
otherwise moves the bullet in its directions 
and checks the objects in its current location again
I chose this class to not be part of sentient even though it moves because it does not have hit points
and its movement algorithm is different and much more simpler*/
class Bullet : public Actor
{
public:
	Bullet(int startX, int startY, Direction startDirection,
		int sub_level, StudentWorld* n_SW);
	virtual void doSomething();
	virtual bool Interactions(unsigned int obj);
};

/*these are child classes of bullies, and its interaction specify what it does specifically if there 
is a player or bully on it*/

/*these are child classes of goodies, and its interaction specify what it does specifically if there 
is a player or bully on it*/
class Extralife : public Goodies
{
public:
	Extralife(int startX, int startY,
		int sub_level, StudentWorld* n_SW);
	virtual bool Interactions(unsigned int obj);
};

class Restorehealth : public Goodies
{
public:
	Restorehealth(int startX, int startY,
		int sub_level, StudentWorld* n_SW);
	virtual bool Interactions(unsigned int obj);
};

class Ammo : public Goodies
{
public: 
	Ammo(int startX, int startY,
		int sub_level, StudentWorld* n_SW);
	virtual bool Interactions(unsigned int obj);
}; 

/*FarplaneGun is a a child class of the goodies, and calles the studentworld function FarplaneDamage and damages all bullies and gangsters in a 9x9 radius and 
hacks off 10 hit points from the player
*/
class FarplaneGun : public Goodies
{
public:
	FarplaneGun(int startX, int startY,
		int sub_level, StudentWorld* n_SW);
	virtual bool Interactions(unsigned int obj);
};

class Wall : public Statics
{
public:
	Wall(int startX, int startY, int sub_level);
	virtual bool Interactions(unsigned int obj);
};

class FakeWall : public Statics
{
public:
	FakeWall(int startX, int startY, int sub_level);
	virtual bool Interactions(unsigned int obj);
};

/*the waterpool is a mortalobject because it has 30 hit points and dies after 30 ticks
the dosomething decrements its hitpoints every turn until it hits zero and dies*/
class Waterpool : public MortalObjects
{
public: 
	Waterpool(int startX, int startY, int sub_level, StudentWorld* n_SW);
	virtual void doSomething();
	virtual bool Interactions(unsigned int obj);

};

/*the hostage is a child class of a goody but does not interact with the bully and only the player
*/
class Hostage : public Goodies
{
public:
	Hostage(int startX, int startY,
		int sub_level, StudentWorld* n_SW);
	virtual bool Interactions(unsigned int obj);
};

/*is a derived class of Actor( I did not make this a derived class of goodies because the bully does not use it)
detects if a the player is on it and act accordingly through its Interaction with player*/
class Gold : public Actor
{
public: 
	Gold(int startX, int startY, int sub_level, StudentWorld* n_SW);
	virtual void doSomething();
	virtual bool Interactions(unsigned int obj);
}; 

/*the bully nest is a derived class of Actor
its dosomething calls the studentworld function scanareaforbullies to check if there are 3 or less bullies in the 3x3 surrounding area, if that
is true it calls the chancetocreatebully function which has a 1/50 chance of return true, and if it is true, it creates a new bully at the coordinate
of the bullynest*/
class BullyNest : public Actor
{
public:
	BullyNest(int startX, int startY, int sub_level, StudentWorld* n_SW);
	virtual void doSomething();
	virtual bool Interactions(unsigned int obj);
	bool chanceTocreateNewBully();

};

/*Exit is a derived class of statics
the Exit doSomething checks if the player has fulfilled all the requirements for the Exit to appear and when it does appear, it checks
if the player is on it and tells the studentworld that the level is finished*/
class Exit : public Statics
{
	int c;
public:
	Exit(int startX, int startY, int sub_level, StudentWorld* n_SW);
	virtual void doSomething();
	virtual bool Interactions(unsigned int obj);
};

/*the gate class is a derived class of Actor,
my implementation of how the player moves between level is to have a player container to move the player between each level accordingly
so in its doSomething implementation I have it call the studentWorld function setCurrentSubLevel, which sets the current sub level to the sub level indicated by the gate number*/
class Gate : public Actor
{

public: 
	Gate(int gateNumber, int startX, int startY, int sub_level, StudentWorld* n_SW);
	virtual void doSomething();
	int getGateNumber();
	virtual bool Interactions(unsigned int obj);
	
private:
	int m_gateNumber;
};







#endif // ACTOR_H_
