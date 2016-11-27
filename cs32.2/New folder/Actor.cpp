#include "Actor.h"
#include "StudentWorld.h"
#include <stack>
#include <random>

using namespace std;
// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//interaction functions are functions that the Actor does in response to another object
void Sentient::Movement()
{
	stack<unsigned int> Sentientstack;
	Direction face = getDirection();
	bool blocked = false;
	switch (face)
	{
	case up:
		if (m_SW->checkAtForPlayer(getX(), getY() + 1, m_SW->getCurrentSubLevel()) == true)
		{
			blocked = true;
			setDirection(down);
			return;
		}
		if (m_SW->CheckAt(getX(), getY() + 1, m_SW->getCurrentSubLevel(), Sentientstack) == true)
		{
			while (Sentientstack.empty() == false)
			{
				unsigned int obj = Sentientstack.top();
				Sentientstack.pop();
				if (obj == IID_BULLY || obj == IID_GANGSTER || obj == IID_ROBOT_BOSS
					|| obj == IID_WALL || obj == IID_BULLY_NEST || obj == IID_WATERPOOL)
				{
					blocked = true;
					setDirection(down);
					return;
				}
			}
		}
			this->moveTo(getX(), getY() + 1);
			return;
		break;
	case down:
		if (m_SW->checkAtForPlayer(getX(), getY() - 1, m_SW->getCurrentSubLevel()) == true)
		{
			blocked = true;
			setDirection(up);
			return;
		}
		if (m_SW->CheckAt(getX(), getY() - 1, m_SW->getCurrentSubLevel(), Sentientstack) == true)
		{
			while (Sentientstack.empty() == false)
			{
				unsigned int obj = Sentientstack.top();
				Sentientstack.pop();
				if (obj == IID_BULLY || obj == IID_GANGSTER || obj == IID_ROBOT_BOSS
					|| obj == IID_WALL || obj == IID_BULLY_NEST || obj == IID_WATERPOOL)
				{
					blocked = true;
					setDirection(up);
					return;
				}
			}
		}
			this->moveTo(getX(), getY() - 1);
			return;
		break;
	case left:
		if (m_SW->checkAtForPlayer(getX() - 1, getY(), m_SW->getCurrentSubLevel()) == true)
		{
			blocked = true;
			setDirection(right);
			return;
		}
		if (m_SW->CheckAt(getX() - 1, getY(), m_SW->getCurrentSubLevel(), Sentientstack) == true)
		{
			while (Sentientstack.empty() == false)
			{
				unsigned int obj = Sentientstack.top();
				Sentientstack.pop();
				if (obj == IID_BULLY || obj == IID_GANGSTER || obj == IID_ROBOT_BOSS
					|| obj == IID_WALL || obj == IID_BULLY_NEST || obj == IID_WATERPOOL)
				{
					blocked = true;
					setDirection(right);
					return;
				}
			}
		}
			this->moveTo(getX() - 1, getY());
			return;
		break;

	case right:
		if (m_SW->checkAtForPlayer(getX() + 1, getY(), m_SW->getCurrentSubLevel()) == true)
		{
			blocked = true;
			setDirection(left);
			return;
		}
		if (m_SW->CheckAt(getX() + 1, getY(), m_SW->getCurrentSubLevel(), Sentientstack) == true)
		{
			while (Sentientstack.empty() == false)
			{
				unsigned int obj = Sentientstack.top();
				Sentientstack.pop();
				if (obj == IID_BULLY || obj == IID_GANGSTER || obj == IID_ROBOT_BOSS
					|| obj == IID_WALL || obj == IID_BULLY_NEST || obj == IID_WATERPOOL)
				{
					blocked = true;
					setDirection(left);
					return;
				}
			}
		}
		this->moveTo(getX() + 1, getY());
		return;
		break;
	}
}
bool Sentient::Interactions(unsigned int obj)
{
	if (obj == IID_FARPLANE_GUN)
	{
		dammage(10);
		m_SW->playSound(SOUND_ENEMY_IMPACT);
		return true;
	}
	if (obj == IID_BULLET) // get hit by a bullet, get dammaged
	{
		dammage(2);
		if ((this->getID() == IID_ROBOT_BOSS || this->getID()== IID_GANGSTER 
			|| this->getID() == IID_BULLY)&& this->gethp() != 0)
			m_SW->playSound(SOUND_ENEMY_IMPACT);
		if ((this->getID() == IID_PLAYER))
			m_SW->playSound(SOUND_PLAYER_IMPACT);
		return true;
	}
	if (obj == SHOOT) // shoots a bullet
	{
		Bullet* t_Bullet;
		if (this->getDirection() == left)
			t_Bullet = new Bullet(getX() - 1, getY(), left, m_SW->getCurrentSubLevel(), m_SW);
		if (this->getDirection() == right)
			t_Bullet = new Bullet(getX() + 1, getY(), right, m_SW->getCurrentSubLevel(), m_SW);
		if (this->getDirection() == up)
			t_Bullet = new Bullet(getX(), getY() + 1, up, m_SW->getCurrentSubLevel(), m_SW);
		if (this->getDirection() == down)
			t_Bullet = new Bullet(getX(), getY() - 1, down, m_SW->getCurrentSubLevel(), m_SW);
		m_SW->m_Actor[m_SW->getCurrentSubLevel()].push_back(t_Bullet);
		return true;
	}
	return false;
}
bool Sentient::ShootAtPlayer()
{
	bool foundPlayer = false;
	int PX = -5, PY = -5;
	Direction facing = this->getDirection();
	switch (facing)
	{
	case left:
		for (int i = 0; i < getX(); i++)
		{
			stack<unsigned int> Sentientstack;
			if (m_SW->checkAtForPlayer(i, getY(), m_SW->getCurrentSubLevel()))
			{
				foundPlayer = true;
				PX = i;
				PY = getY();
			}
			if (PX == i)
			{	
				if ((m_SW->CheckAt(i+1, getY(), m_SW->getCurrentSubLevel(), Sentientstack) == true))
				{
					while (Sentientstack.empty() == false)
					{
						unsigned int obj = Sentientstack.top();
						Sentientstack.pop();
						if (this->getX() == i + 1)
						{
							if (foundPlayer == true)
							{
								Interactions(SHOOT);
								return true;
							}
						}
						if (obj == IID_FAKE_WALL)
						{
							if (foundPlayer == true)
							{
								return false;
							}
						}
					}
				}
			}
			if (PX != i)
			{
				if ((m_SW->CheckAt(i, getY(), m_SW->getCurrentSubLevel(), Sentientstack) == true))
				{
					while (Sentientstack.empty() == false)
					{
						unsigned int obj = Sentientstack.top();
						Sentientstack.pop();
						if (obj == IID_BULLY || obj == IID_GANGSTER || obj == IID_ROBOT_BOSS
							|| obj == IID_WALL || obj == IID_BULLY_NEST ||
							obj == IID_WATERPOOL || obj == IID_FAKE_WALL)
						{
							if (foundPlayer == true)
							{
								return false;
							}
						}
					}
				}
			}
		}
		if (foundPlayer == true)
		Interactions(SHOOT);
		break;
	case right:
		for (int i = 14; i  > getX(); i--)
		{
			stack<unsigned int> Sentientstack;
			if (m_SW->checkAtForPlayer(i, getY(), m_SW->getCurrentSubLevel()))
			{
				foundPlayer = true;
				PX = i;
				PY = getY();
			}
			if (PX == i)
			{
				if ((m_SW->CheckAt(i - 1, getY(), m_SW->getCurrentSubLevel(), Sentientstack) == true))
				{
					while (Sentientstack.empty() == false)
					{
						unsigned int obj = Sentientstack.top();
						Sentientstack.pop();
						if (this->getX() == i - 1)
						{
							if (foundPlayer == true)
							{
								Interactions(SHOOT);
								return true;
							}
						}
						if (obj == IID_FAKE_WALL)
						{
							if (foundPlayer == true)
							{
								return false;
							}
						}
					}
				}
			}
			if (PX != i)
			{
				if ((m_SW->CheckAt(i, getY(), m_SW->getCurrentSubLevel(), Sentientstack) == true))
				{
					while (Sentientstack.empty() == false)
					{
						unsigned int obj = Sentientstack.top();
						Sentientstack.pop();
						if (obj == IID_BULLY || obj == IID_GANGSTER || obj == IID_ROBOT_BOSS
							|| obj == IID_WALL || obj == IID_BULLY_NEST ||
							obj == IID_WATERPOOL || obj == IID_FAKE_WALL)
						{
							if (foundPlayer == true)
							{
								return false;
							}
						}
					}
				}
			}
		}
		if (foundPlayer == true)
		Interactions(SHOOT);
		break;
	case up:
		for (int i = 14; i > getY(); i--)
		{
			stack<unsigned int> Sentientstack;
			if (m_SW->checkAtForPlayer(getX(), i, m_SW->getCurrentSubLevel()))
			{
				foundPlayer = true;
				PX = getX();
				PY = i;
			}
			if (PY == i)
			{
				if ((m_SW->CheckAt(getX(), i-1, m_SW->getCurrentSubLevel(), Sentientstack) == true))
				{
					while (Sentientstack.empty() == false)
					{
						unsigned int obj = Sentientstack.top();
						Sentientstack.pop();
						if (this->getY() == i - 1) // check if enemy is facing player
						{
							if (foundPlayer == true)
							{
								Interactions(SHOOT);
								return true;
							}
						}
						if (obj == IID_FAKE_WALL) //check if player is in fake wall but not protected
						{
							if (foundPlayer == true)
							{
								return false;
							}
						}
					}
				}
			}
			if (PY != i)
			{
				if ((m_SW->CheckAt(getX(), i, m_SW->getCurrentSubLevel(), Sentientstack) == true))
				{
					while (Sentientstack.empty() == false)
					{
						unsigned int obj = Sentientstack.top();
						Sentientstack.pop();
						if (obj == IID_BULLY || obj == IID_GANGSTER || obj == IID_ROBOT_BOSS
							|| obj == IID_WALL || obj == IID_BULLY_NEST ||
							obj == IID_WATERPOOL || obj == IID_FAKE_WALL)
						{
							if (foundPlayer == true)
							{
								return false;
							}
						}
					}
				}
			}
		}
		if (foundPlayer == true)
		Interactions(SHOOT);
		break;
	case down:
		for (int i = 0; i < getY(); i++)
		{
			stack<unsigned int> Sentientstack;
			if (m_SW->checkAtForPlayer(getX(), i, m_SW->getCurrentSubLevel()))
			{
				foundPlayer = true;
				PX = getX();
				PY = i;
			}
			if (PY == i)
			{
				if ((m_SW->CheckAt(getX(), i+1, m_SW->getCurrentSubLevel(), Sentientstack) == true))
				{
					while (Sentientstack.empty() == false)
					{
						unsigned int obj = Sentientstack.top();
						Sentientstack.pop();
						if (this->getY() == i + 1)
						{
							if (foundPlayer == true)
							{
								Interactions(SHOOT);
								return true;
							}
						}
						if (obj == IID_FAKE_WALL)
						{
							if (foundPlayer == true)
							{
								return false;
							}
						}
					}
				}
			}
			if (PY != i)
			{
				if ((m_SW->CheckAt(getX(), i, m_SW->getCurrentSubLevel(), Sentientstack) == true))
				{
					while (Sentientstack.empty() == false)
					{
						unsigned int obj = Sentientstack.top();
						Sentientstack.pop();
						if (obj == IID_BULLY || obj == IID_GANGSTER || obj == IID_ROBOT_BOSS
							|| obj == IID_WALL || obj == IID_BULLY_NEST ||
							obj == IID_WATERPOOL || obj == IID_FAKE_WALL)
						{
							if (foundPlayer == true)
							{
								return false;
							}
						}
					}
				}
			}
		}
		if (foundPlayer == true)
		Interactions(SHOOT);
		break;
	}
	if (foundPlayer == true)
	return true;
	return false;
}

bool Player::Interactions(unsigned int obj)
{
	if (obj == SHOOT)
	{
		if (this->useAmmo() == true)
		{
			m_SW->playSound(SOUND_PLAYER_FIRE);
			return Sentient::Interactions(SHOOT);
		}
	}
	if (obj == IID_BULLET)
	{
		return Sentient::Interactions(obj);
	}
	return false;
}
void Player::Movement()
{
	int ch;
	if (m_SW->getKey(ch))
	{
		// user hit a key this tick!
		stack<unsigned int> playerStack;
		bool blocked = false;
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			if (m_SW->CheckAt(getX() - 1, getY(), m_SW->getCurrentSubLevel(), playerStack) == false)
			{
				this->moveTo(getX() - 1, getY());
				this->setDirection(left);
			}
			else
			{
				while (playerStack.empty() == false)
				{
					unsigned int obj = playerStack.top();
					playerStack.pop();
					if (obj == IID_WALL || obj == IID_GANGSTER || obj == IID_WATERPOOL || 
						obj == IID_ROBOT_BOSS || obj == IID_BULLY || obj == IID_BULLY_NEST)
					{
						blocked = true;
					}
				}
				if (blocked == true)
				{
					this->setDirection(left);
				}
				else
				{
					this->moveTo(getX() - 1, getY());
					this->setDirection(left);
				}
			}
			break;
		case KEY_PRESS_RIGHT:
			if (m_SW->CheckAt(getX() + 1, getY(), m_SW->getCurrentSubLevel(), playerStack) == false)
			{
				this->moveTo(getX() + 1, getY());
				this->setDirection(right);
			}
			else
			{
				while (playerStack.empty() == false)
				{
					unsigned int obj = playerStack.top();
					playerStack.pop();
					if (obj == IID_WALL || obj == IID_GANGSTER || obj == IID_WATERPOOL ||
						obj == IID_ROBOT_BOSS || obj == IID_BULLY || obj == IID_BULLY_NEST)
					{
						blocked = true;
					}
				}
				if (blocked == true)
				{
					this->setDirection(right);
				}
				else
				{
					this->moveTo(getX() + 1, getY());
					this->setDirection(right);
				}
			}
			break;
		case KEY_PRESS_UP:
			if (m_SW->CheckAt(getX(), getY() + 1, m_SW->getCurrentSubLevel(), playerStack) == false)
			{
				this->moveTo(getX(), getY() + 1);
				this->setDirection(up);
			}
			else
			{
				while (playerStack.empty() == false)
				{
					unsigned int obj = playerStack.top();
					playerStack.pop();
					if (obj == IID_WALL || obj == IID_GANGSTER || obj == IID_WATERPOOL ||
						obj == IID_ROBOT_BOSS || obj == IID_BULLY || obj == IID_BULLY_NEST)
					{
						blocked = true;
					}
				}
				if (blocked == true)
				{
					this->setDirection(up);
				}
				else
				{
					this->moveTo(getX(), getY()+1);
					this->setDirection(up);
				}
			}
			break;
		case KEY_PRESS_DOWN:
			if (m_SW->CheckAt(getX(), getY() - 1, m_SW->getCurrentSubLevel(), playerStack) == false)
			{
				this->moveTo(getX(), getY() - 1);
				this->setDirection(down);
			}
			else
			{
				while (playerStack.empty() == false)
				{
					unsigned int obj = playerStack.top();
					playerStack.pop();
					if (obj == IID_WALL || obj == IID_GANGSTER || obj == IID_WATERPOOL ||
						obj == IID_ROBOT_BOSS || obj == IID_BULLY || obj == IID_BULLY_NEST)
					{
						blocked = true;
					}
				}
				if (blocked == true)
				{
					this->setDirection(down);
				}
				else
				{
					this->moveTo(getX(), getY()-1);
					this->setDirection(down);
				}
			}
			break;
		case KEY_PRESS_SPACE:
			this->Interactions(SHOOT);
			break;
		case KEY_PRESS_ESCAPE:
			setAlive(false);
			m_SW->decLives();
		}
	}
	else
	{
		return;
	}
}
void Player::doSomething()
{	
	if (gethp() == 0)
	{
		setAlive(false);
		m_SW->decLives();
	}

	if (this->isAlive() == false)
		return;
	else
	{
		Movement();
	}
	
}

bool Gold::Interactions(unsigned int obj)
{
	if (obj == IID_PLAYER)
	{
		m_SW->increaseScore(100);
		this->setAlive(false);
		m_SW->playSound(SOUND_GOT_GOLD);
		return true;
	}
	return false;
}
void Gold::doSomething()
{
	if (this->isAlive() == false)
	{
		return;
	}
	else
	{
		if (m_SW->checkAtForPlayer(getX(), getY(),
			m_SW->getCurrentSubLevel()) == true)
		{
			Interactions(IID_PLAYER);
		}
	}
}

Gangster::Gangster(int startX, int startY, int sub_level, Direction dir, StudentWorld* n_SW) :
	Sentient(IID_GANGSTER, startX, startY, dir, sub_level, 10, n_SW)
{
	setVisible(true);
	int ticks = (28 - n_SW->getLevel()) / 4;
	if (ticks < 3)
		ticks = 3;
	m_ticks = ticks;
	m_counter = ticks;
}
void Gangster::doSomething()
{
	
	if (this->isAlive() == false)
	{
		return;
	}
	else
	{
		if (gethp() == 0)
		{
			Waterpool* t_Waterpool = new Waterpool(getX(), getY(), m_SW->getCurrentSubLevel(), m_SW);
			m_SW->m_Actor[m_SW->getCurrentSubLevel()].push_back(t_Waterpool);
			setAlive(false);
			m_SW->playSound(SOUND_ENEMY_DIE);
			return;
		}
		if (m_counter % m_ticks == 0)
		{

			if (ShootAtPlayer())
			{
				m_counter++;
			}
			else
			{
				Movement();
				m_counter++;
			}
		}
		else
		{
			m_counter++;
		}
		return;
	}
	
}
bool Gangster::Interactions(unsigned int obj)
{
	if (obj == IID_FARPLANE_GUN)
	{
		return Sentient::Interactions(obj);
	}
	if (obj == IID_BULLET) //damages bully
	{
		m_SW->increaseScore(100);
		m_SW->playSound(SOUND_ENEMY_IMPACT);
		return Sentient::Interactions(obj);
	}
	if (obj == SHOOT) // bully fires the laser gun
	{
		m_SW->playSound(SOUND_ENEMY_FIRE);
		return Sentient::Interactions(obj);
	}
	return false;
}

RobotBoss::RobotBoss(int startX, int startY, int sub_level, StudentWorld* n_SW) :
	Sentient(IID_ROBOT_BOSS, startX, startY, right, sub_level, 50, n_SW)
{
	setVisible(true);
	int ticks = (28 - n_SW->getLevel()) / 4;
	if (ticks < 3)
		ticks = 3;
	m_ticks = ticks;
	m_counter = ticks;
}
bool RobotBoss::Interactions(unsigned int obj)
{
	if (obj == IID_BULLET) //damages Robotboss
	{
		m_SW->increaseScore(100);
		m_SW->playSound(SOUND_ENEMY_IMPACT);
		return Sentient::Interactions(obj);
	}
	if (obj == SHOOT) // bully fires the laser gun
	{
		m_SW->playSound(SOUND_ENEMY_FIRE);
		return Sentient::Interactions(obj);
	}
	return false;
}
void RobotBoss::doSomething()
{
	if (this->isAlive() == false)
	{
		return;
	}
	else
	{
		if (gethp() == 0)
		{
			setAlive(false);
			m_SW->playSound(SOUND_ENEMY_DIE);
			m_SW->increaseScore(3000);
			Hostage* t_Hostage = new Hostage(getX(), getY(), m_SW->getCurrentSubLevel(), m_SW);
			m_SW->m_Actor[m_SW->getCurrentSubLevel()].push_back(t_Hostage);
			return;
		}
		if (m_counter % m_ticks == 0)
		{

			if (ShootAtPlayer())
			{
				m_counter++;
			}
			else
			{
				Movement();
				m_counter++;
			}
		}
		else
		{
			m_counter++;
		}
		return;
	}
}

Bully::Bully(int startX, int startY, int sub_level, StudentWorld* n_SW) :
	Sentient(IID_BULLY, startX, startY, GraphObject::right, sub_level, 5, n_SW)
{
	setVisible(true);
	int ticks = ((28 - n_SW->getLevel()) / 4);
	if (ticks < 3)
		ticks = 3;
	m_ticks = ticks;
	m_counter = ticks;
	m_walkCounter = 0;
	m_distance = distanceBeforeTurning();
}
bool Bully::foundGoodies()
{
	bool found = false;
	stack<Actor*> bullystack(m_SW->retrieveAllGoodiesat(getX(), getY(), m_SW->getCurrentSubLevel()));
	if (!bullystack.empty())
		found = true;
	while (!bullystack.empty())
	{
		bullystack.top()->Interactions(IID_BULLY);
		m_bullyBag.push(bullystack.top()->getID());
		bullystack.pop();
	}
	return found;
}
void Bully::dropGoodies()
{
	while (m_bullyBag.empty() == false)
	{
		if (m_bullyBag.top() == IID_AMMO)
		{
			Ammo* t_Ammo = new Ammo(getX(), getY(), m_SW->getCurrentSubLevel(), m_SW);
			m_SW->m_Actor[m_SW->getCurrentSubLevel()].push_back(t_Ammo);
		}
		else if (m_bullyBag.top() == IID_RESTORE_HEALTH)
		{
			Restorehealth* t_Restorehealth = new Restorehealth(getX(), getY(), m_SW->getCurrentSubLevel(), m_SW);
			m_SW->m_Actor[m_SW->getCurrentSubLevel()].push_back(t_Restorehealth);
		}
		else if (m_bullyBag.top() == IID_EXTRA_LIFE)
		{
			Extralife* t_Extralife = new Extralife(getX(), getY(), m_SW->getCurrentSubLevel(), m_SW);
			m_SW->m_Actor[m_SW->getCurrentSubLevel()].push_back(t_Extralife);
		}
		m_bullyBag.pop();
	}
}
int Bully::distanceBeforeTurning()
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 6); // distribution in range [1, 6]

	return dist6(rng);
}
int Bully::directionRandomize(int i)
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, i); // distribution in range [1, 6]

	return dist6(rng);
}
void Bully::Movement()
{
	stack<unsigned int> bullystack;
	Direction face = getDirection();
	bool blocked = false;
	switch (face)
	{
	case up:
		if (m_SW->checkAtForPlayer(getX(), getY() + 1, m_SW->getCurrentSubLevel()) == true)
		{
			MovementObstructed();
			return;
		}
		if (m_SW->CheckAt(getX(), getY() + 1, m_SW->getCurrentSubLevel(), bullystack) == true)
		{
			while (bullystack.empty() == false)
			{
				unsigned int obj = bullystack.top();
				bullystack.pop();
				if (obj == IID_BULLY || obj == IID_GANGSTER || obj == IID_ROBOT_BOSS
					|| obj == IID_WALL || obj == IID_BULLY_NEST || obj == IID_WATERPOOL)
				{
					MovementObstructed();
					return;
				}
			}
		}
		m_walkCounter++;
		this->moveTo(getX(), getY() + 1);
		break;
	case down:
		if (m_SW->checkAtForPlayer(getX(), getY() - 1, m_SW->getCurrentSubLevel()) == true)
		{
			MovementObstructed();
			return;
		}
		if (m_SW->CheckAt(getX(), getY() - 1, m_SW->getCurrentSubLevel(), bullystack) == true)
		{
			while (bullystack.empty() == false)
			{
				unsigned int obj = bullystack.top();
				bullystack.pop();
				if (obj == IID_BULLY || obj == IID_GANGSTER || obj == IID_ROBOT_BOSS
					|| obj == IID_WALL || obj == IID_BULLY_NEST || obj == IID_WATERPOOL)
				{
					MovementObstructed();
					return;
				}
			}
		}
		m_walkCounter++;
		this->moveTo(getX(), getY() - 1);
		break;
	case left:
		if (m_SW->checkAtForPlayer(getX() - 1, getY(), m_SW->getCurrentSubLevel()) == true)
		{
			MovementObstructed();
			return;
		}
		if (m_SW->CheckAt(getX() - 1, getY(), m_SW->getCurrentSubLevel(), bullystack) == true)
		{
			while (bullystack.empty() == false)
			{
				unsigned int obj = bullystack.top();
				bullystack.pop();
				if (obj == IID_BULLY || obj == IID_GANGSTER || obj == IID_ROBOT_BOSS
					|| obj == IID_WALL || obj == IID_BULLY_NEST || obj == IID_WATERPOOL)
				{
					MovementObstructed();
					return;
				}
			}
		}
		m_walkCounter++;
		this->moveTo(getX() - 1, getY());
		break;

	case right:
		if (m_SW->checkAtForPlayer(getX() + 1, getY(), m_SW->getCurrentSubLevel()) == true)
		{
			MovementObstructed();
			return;
		}
		if (m_SW->CheckAt(getX() + 1, getY(), m_SW->getCurrentSubLevel(), bullystack) == true)
		{
			while (bullystack.empty() == false)
			{
				unsigned int obj = bullystack.top();
				bullystack.pop();
				if (obj == IID_BULLY || obj == IID_GANGSTER || obj == IID_ROBOT_BOSS
					|| obj == IID_WALL || obj == IID_BULLY_NEST || obj == IID_WATERPOOL)
				{
					MovementObstructed();
					return;
				}
			}
		}
		m_walkCounter++;
		this->moveTo(getX() + 1, getY());
		break;
	}
}
bool Bully::MoveRight()
{
	bool blocked = false;
	stack<unsigned int> bullystack;

	setDirection(right);
	if (m_SW->checkAtForPlayer(getX() + 1, getY(), m_SW->getCurrentSubLevel()) == true)
	{
		blocked = true;
	}
	if (m_SW->CheckAt(getX() + 1, getY(), m_SW->getCurrentSubLevel(), bullystack) == true)
	{
		while (bullystack.empty() == false)
		{
			unsigned int obj = bullystack.top();
			bullystack.pop();
			if (obj == IID_BULLY || obj == IID_GANGSTER || obj == IID_ROBOT_BOSS
				|| obj == IID_WALL || obj == IID_BULLY_NEST || obj == IID_WATERPOOL)
			{
				blocked = true;
			}
		}
	}
	if (blocked == false)
	{
		this->moveTo(getX() + 1, getY());
		return true;
	}
	return false;
}
bool Bully::MoveLeft()
{
	bool blocked = false;
	stack<unsigned int> bullystack;

	setDirection(left);
	if (m_SW->checkAtForPlayer(getX() - 1, getY(), m_SW->getCurrentSubLevel()) == true)
	{
		blocked = true;
	}
	if (m_SW->CheckAt(getX() - 1, getY(), m_SW->getCurrentSubLevel(), bullystack) == true)
	{
		while (bullystack.empty() == false)
		{
			unsigned int obj = bullystack.top();
			bullystack.pop();
			if (obj == IID_BULLY || obj == IID_GANGSTER || obj == IID_ROBOT_BOSS
				|| obj == IID_WALL || obj == IID_BULLY_NEST || obj == IID_WATERPOOL)
			{
				blocked = true;
			}
		}
	}
	if (blocked == false)
	{
		this->moveTo(getX() - 1, getY());
		return true;
	}
	return false;

}
bool Bully::MoveUp()
{
	bool blocked = false;
	stack<unsigned int> bullystack;
	setDirection(up);
	if (m_SW->checkAtForPlayer(getX(), getY() + 1, m_SW->getCurrentSubLevel()) == true)
	{
		blocked = true;
	}
	if (m_SW->CheckAt(getX(), getY() + 1, m_SW->getCurrentSubLevel(), bullystack) == true)
	{
		while (bullystack.empty() == false)
		{
			unsigned int obj = bullystack.top();
			bullystack.pop();
			if (obj == IID_BULLY || obj == IID_GANGSTER || obj == IID_ROBOT_BOSS
				|| obj == IID_WALL || obj == IID_BULLY_NEST || obj == IID_WATERPOOL)
			{
				blocked = true;
			}
		}
	}
	if (blocked == false)
	{
		this->moveTo(getX(), getY() + 1);
		return true;
	}
	return false;
}
bool Bully::MoveDown()
{
	bool blocked = false;
	stack<unsigned int> bullystack;

	setDirection(down);
	if (m_SW->checkAtForPlayer(getX(), getY() - 1, m_SW->getCurrentSubLevel()) == true)
	{
		blocked = true;
	}
	if (m_SW->CheckAt(getX(), getY() - 1, m_SW->getCurrentSubLevel(), bullystack) == true)
	{
		while (bullystack.empty() == false)
		{
			unsigned int obj = bullystack.top();
			bullystack.pop();
			if (obj == IID_BULLY || obj == IID_GANGSTER || obj == IID_ROBOT_BOSS
				|| obj == IID_WALL || obj == IID_BULLY_NEST || obj == IID_WATERPOOL)
			{
				blocked = true;
			}
		}
	}
	if (blocked == false)
	{
		this->moveTo(getX(), getY() - 1);
		return true;
	}
	return false;
}
void Bully::MovementObstructed()
{
	m_walkCounter = 0;
	m_distance = distanceBeforeTurning();
		int dir = directionRandomize(4);
		switch (dir)
		{
		case 1:
			if (MoveUp())
				return;
			break;
		case 2:
			if (MoveDown())
				return;
			break;
		case 3:
			if (MoveLeft())
				return;
			break;
		case 4:
			if (MoveRight())
				return;
			break;
		}
		if (dir == 1)
		{
			if (MoveDown())
				return;
			if (MoveLeft())
				return;
			if (MoveRight())
				return;
		}
		else if (dir == 2)
		{
			if (MoveUp())
				return;
			if (MoveLeft())
				return;
			if (MoveRight())
				return;
		}
		else if (dir == 4)
		{
			if (MoveUp())
				return;
			if (MoveDown())
				return;
			if (MoveRight())
				return;
		}
		else if (dir == 4)
		{
			if (MoveUp())
				return;
			if (MoveDown())
				return;
			if (MoveLeft())
				return;
		}
}
bool Bully::Interactions(unsigned int obj)
{
	if (obj == IID_FARPLANE_GUN)
	{
		return Sentient::Interactions(obj);
	}
	if (obj == IID_BULLET) //damages bully
	{
		return Sentient::Interactions(obj);
	}
	if (obj == SHOOT) // bully fires the laser gun
	{
		m_SW->playSound(SOUND_ENEMY_FIRE);
		return Sentient::Interactions(obj);
	}
	if (obj == GOODIES) // interacts with goodies
	{
		return foundGoodies();
	}
	if (obj == IID_PLAYER) // shoots at player
	{
		Sentient::Interactions(obj);
	}

		
	return false;
	
}
void Bully::doSomething()
{
		
	if (this->isAlive() == false)
	{
		return;
	}
	else
	{
		if (gethp() == 0)
		{
			this->setAlive(false);
			m_SW->playSound(SOUND_ENEMY_DIE);
			m_SW->increaseScore(10);
			this->dropGoodies();
		}
		else if (m_counter % m_ticks == 0)
		{

			if (ShootAtPlayer() == true)
			{
				m_counter++;
			}
			else if (foundGoodies() == true)
			{
				m_counter++;
			}
			else if (m_walkCounter < m_distance)
			{
				Movement();
				m_counter++;

			}
			else if (m_walkCounter >= m_distance)
			{
				MovementObstructed();
				m_counter++;
			}
			else
			{
				m_counter++;
			}
			

		}
		else;
		m_counter++;

	}
}

void Goodies::doSomething()
{
	if (this->isAlive() == false)
	{
		return;
	}
	else
	{
		if (this->m_SW->checkAtForPlayer(this->getX(), this->getY(), 
			m_SW->getCurrentSubLevel()) == true)
		{
			this->setAlive(false);
			Interactions(IID_PLAYER);
		}
	}
}

bool Bullet::Interactions(unsigned int obj)
{
	if (m_SW->bulletDamageSentient(obj, this) == true)  //except bully
	{
		return true;
	}
	else if (obj == IID_WALL || obj == IID_WATERPOOL)
	{
		this->setAlive(false);
		return true;
	}
	else if (obj == IID_BULLY_NEST)
	{
		this->setAlive(false);
		return true;
	}
	else if (obj == IID_BULLY)
	{
		return m_SW->bulletDamageSentient(obj, this);
	}
	return false;
}
void Bullet::doSomething()
{
	if (this->isAlive() == false)
	{
		return;
	}
	else
	{
		//checks if any interactions with bullet on this spot
		bool BullynestExist = false;
		bool BullyExist = false;
		stack<unsigned int> bulletstack;
		if (m_SW->checkAtForPlayer(getX(), getY(), m_SW->getCurrentSubLevel()) == true)
		{
			Interactions(IID_PLAYER);
			return;
		}
		if (m_SW->CheckAt(getX(), getY(), m_SW->getCurrentSubLevel(), bulletstack) == true)
		{
			while (bulletstack.empty() == false)
			{
				unsigned int obj = bulletstack.top();
				bulletstack.pop();
				if (obj == IID_BULLY)
					BullyExist = true;
				if (obj == IID_BULLY_NEST)
					BullynestExist = true;
				if (obj == IID_WATERPOOL)
				{
					Interactions(obj);
					return;
				}
				if (obj != IID_BULLY && obj != IID_BULLY_NEST)
					Interactions(obj);
				if (isAlive() == false)
					return;
			}
			if (BullyExist == true && BullynestExist == false)
				Interactions(IID_BULLY);
			else if (BullyExist == true && BullynestExist == true)
				Interactions(IID_BULLY);
			else if(BullyExist == false && BullynestExist == true)
				Interactions(IID_BULLY_NEST);
			else if (BullyExist == false && BullynestExist == false)
			{ }
			if (isAlive() == false)
				return;
		}
		// move bullet
		if (this->getDirection() == up)
		{
			this->moveTo(getX(), getY()+1);
		}
		else if (this->getDirection() == down)
		{
			this->moveTo(getX(), getY()-1);
		}
		else if (this->getDirection() == left)
		{
			this->moveTo(getX()-1, getY());
		}
		else if (this->getDirection() == right)
		{
			this->moveTo(getX()+1, getY());
		}
		//checks if any interactions with bullet on this new spot
		BullynestExist = false;
		BullyExist = false;
		if (m_SW->checkAtForPlayer(getX(), getY(), m_SW->getCurrentSubLevel()) == true)
		{
			Interactions(IID_PLAYER);
			return;
		}
		if (m_SW->CheckAt(getX(), getY(), m_SW->getCurrentSubLevel(), bulletstack) == true)
		{
			while (bulletstack.empty() == false)
			{
				unsigned int obj = bulletstack.top();
				bulletstack.pop();
				if (obj == IID_BULLY)
					BullyExist = true;
				if (obj == IID_BULLY_NEST)
					BullynestExist = true;
				if (obj == IID_WATERPOOL)
				{
					Interactions(obj);
					return;
				}
				if (obj != IID_BULLY && obj != IID_BULLY_NEST)
				Interactions(obj);
				if (isAlive() == false)
					return;
			}
			if (BullyExist == true && BullynestExist == false)
				Interactions(IID_BULLY);
			else if (BullyExist == true && BullynestExist == true)
				Interactions(IID_BULLY);
			else if (BullyExist == false && BullynestExist == true)
				Interactions(IID_BULLY_NEST);
			else if (BullyExist == false && BullynestExist == false)
			{
			}

			if (isAlive() == false)
				return;
		}
	}
}

bool Extralife::Interactions(unsigned int obj)
{
	if (obj == IID_PLAYER)
	{
		m_SW->playSound(SOUND_GOT_GOODIE);
		m_SW->increaseScore(150);
		m_SW->incLives();
		return true;
	}
	if (obj == IID_BULLY)
	{
		this->setAlive(false);
		return true;
	}
	return false;
}
bool Restorehealth::Interactions(unsigned int obj)
{
	if (obj == IID_PLAYER)
	{
		m_SW->playSound(SOUND_GOT_GOODIE);
		m_SW->increaseScore(250);
		m_SW->m_Player->sethp(20);
		return true;
	}
	if (obj == IID_BULLY)
	{
		this->setAlive(false);
		return true;
	}
	return false;
}
bool Ammo::Interactions(unsigned int obj)
{
	if (obj == IID_PLAYER)
	{
		m_SW->playSound(SOUND_GOT_GOODIE);
		m_SW->increaseScore(150);
		m_SW->increaseAmmo();
		return true;
	}
	if (obj == IID_BULLY)
	{
		this->setAlive(false);
		return true;
	}
	return false;
}
bool Hostage::Interactions(unsigned int obj)
{
	if (obj == IID_PLAYER)
	{
		m_SW->playSound(SOUND_GOT_GOODIE);
	}
	// does nothing
	return false;
}
bool FarplaneGun::Interactions(unsigned int obj)
{
	if (obj == IID_PLAYER)
	{
		m_SW->playSound(SOUND_GOT_FARPLANE_GUN);
		m_SW->FarplaneDamage(getX(), getY(), m_SW->getCurrentSubLevel());
		m_SW->m_Player->dammage(10);
		return true;
	}
	return false;
}


void Statics::doSomething()
{
	//doesnt do anything
}
bool Statics::Interactions(unsigned int obj)
{
	return false;
	//doesnt do anything
}

bool Gate::Interactions(unsigned int obj)
{
	return false;
}
void Gate::doSomething()
{
	if (this->isAlive() == false)
	{
		return;
	}
	else if (this->isAlive() && m_SW->checkAtForPlayer(this->getX(), this->getY(), m_SW->getCurrentSubLevel()) == true)
	{
		this->setAlive(false);
		this->setVisible(false);
		m_SW->setCurrentSubLevel(this->m_gateNumber);
	}
}

void Exit::doSomething()
{
	if (m_SW->fulfilledReqs() == true)
	{
		setVisible(true);
	}
		if (m_SW->checkAtForPlayer(getX(), getY(), m_SW->getCurrentSubLevel()) == true && this->isVisible() == true)
		{
			m_SW->playSound(SOUND_FINISHED_LEVEL);
			m_SW->increaseScore(1500);
			m_SW->finishedLevel();
		}
	
}

void Waterpool::doSomething()
{
	if (this->isAlive() == false)
	{
		return;
	}
	else
	{
		if (gethp() == 0)
		{
			setAlive(false);
			m_SW->playSound(SOUND_ENEMY_DIE);
			return;
		}
		dammage(1);
	}
}
bool Waterpool::Interactions(unsigned int obj)
{
	return false;
	//doesnt do anything
}

bool BullyNest::chanceTocreateNewBully()
{
	int chance = -1;
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 50); // distribution in range [1, 6]

	chance = dist6(rng);
	if (chance == 25)
		return true;
	return false;
}
void BullyNest::doSomething()
{
	if (this->isAlive() == false)
	{
		return;
	}
	else
	{
		if (m_SW->scanAreaForBullies(getX(),getY(),m_SW->getCurrentSubLevel(),this) == true)
		{
			if (chanceTocreateNewBully() == true)
			{
				Bully* t_Bully = new Bully(getX(), getY(), m_SW->getCurrentSubLevel(), m_SW);
				m_SW->m_Actor[m_SW->getCurrentSubLevel()].push_back(t_Bully);
				m_SW->playSound(SOUND_BULLY_BORN);
			}
		}
	}
}
bool BullyNest::Interactions(unsigned int obj)
{
	return false;
	//doesnt do anything
}

