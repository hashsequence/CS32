
class Creature
{
public:
	Creature(string nm);
	virtual ~Creature() = 0;
	string name() const;
	virtual bool isMortal() const = 0;
	virtual string move() const = 0;

private:
	string m_name;
};

Creature::Creature(string nm) :m_name(nm)
{
	//empty
}

Creature::~Creature()
{

}

string Creature::name() const
{
	return m_name;
}

class Phoenix : public Creature
{
public:
	Phoenix(string nm);
	~Phoenix();
	virtual bool isMortal() const;
	virtual string move() const;
};

Phoenix::Phoenix(string nm) : Creature(nm)
{
	//empty
}

Phoenix::~Phoenix()
{
	cout << "Destroying " << name() << " the phoenix." << endl;
}

bool Phoenix::isMortal() const
{
	return false;
}

string Phoenix::move() const
{
	return "fly";
}

class Giant : public Creature
{
private:
	int m_weight;
public:
	Giant(string nm, int weight);
	~Giant();
	virtual bool isMortal() const;
	virtual string move() const;
};

Giant::Giant(string nm, int weight) : Creature(nm), m_weight(weight)
{
	// empty
}

Giant::~Giant()
{
	cout << "Destroying " << name() << " the giant." << endl;
}

bool Giant::isMortal() const
{
	return true;
}

string Giant::move() const
{
	if (m_weight < 20)
		return "tromp";
	else
		return "lumber";
}
class Centaur : public Creature
{
public:
	Centaur(string nm);
	~Centaur();
	virtual bool isMortal() const;
	virtual string move() const;
};

Centaur::Centaur(string nm) : Creature(nm)
{
	//empty
}

Centaur::~Centaur()
{
	cout << "Destroying " << name() << " the centaur." << endl;
}

bool Centaur::isMortal() const
{
	return true;
}

string Centaur::move() const
{
	return "trot";
}

void animate(const Creature* c)
{
	cout << c->name() << ", who is ";
	if (c->isMortal())
		cout << "mortal";
	else
		cout << "immortal";
	cout << ", will now " << c->move() << ".\n";
}

