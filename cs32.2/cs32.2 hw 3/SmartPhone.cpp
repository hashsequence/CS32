#include <iostream>
#include <string>
using namespace std;

//Your declarations and implementations would go here
class SmartPhone
{
public:
	SmartPhone(string n_name, string n_maintain) :m_name(n_name), m_maintain(n_maintain)
	{

	}
	virtual string name() const;
	virtual void printWebBrowser() const = 0;
	virtual string futureMove() const;
	virtual ~SmartPhone()= 0;
	
private:
	string m_name, m_maintain;
};

SmartPhone::~SmartPhone()
{

}

string SmartPhone::name() const
{
	return m_name;
}

string SmartPhone::futureMove() const
{
	return m_maintain + " its market share";
}

class Windows : public SmartPhone
{
public:
	Windows(string n_name);
	virtual void printWebBrowser() const;
	~Windows();
private:
};

Windows::Windows(string n_name) : SmartPhone(n_name,"tries to maintain") {}

Windows::~Windows()
{
	cout << "Destroying "  << name() << " the Windows" << endl;
}
void Windows::printWebBrowser() const
{
	cout << "IE";
}

class iOS : public SmartPhone
{
public:
	iOS(string n_name, string version);
	virtual void printWebBrowser() const;
	~iOS();
private:
	string m_version;
};

iOS::iOS(string n_name, string version) : SmartPhone(n_name, "continues to lose"), m_version(version) {}

iOS::~iOS()
{
	cout << "Destroying " << name() << " the iOS" << endl;
}
void iOS::printWebBrowser() const
{
	cout << "Safari" << " version " << m_version;
}

class Android : public SmartPhone
{
public:
	Android(string n_name);
	virtual void printWebBrowser() const;
	~Android();
};

Android::Android(string n_name): SmartPhone(n_name, "tries to gain"){}

void Android::printWebBrowser() const
{
	cout << "Chrome";
}
Android::~Android()
{
	cout << "Destroying " << name() << " the Android" << endl;
}

void availability(const SmartPhone* cp)
{
	cout << cp->name() << ", using ";
	cp->printWebBrowser();
	cout << ", " << cp->futureMove() << "." << endl;
}

int main()
{
	SmartPhone* phones[4];
	phones[0] = new Windows("Alcatel OneTouch Fierce XL with Windows 10");
	// iOS has a name and initial version number for the Safari Browser 
	phones[1] = new iOS("iPhone 6 Plus", "10.0 beta 2");
	phones[2] = new Android("Samsung Galaxy S7");
	phones[3] = new Android("HTC 10");

	cout << "The SmartPhones availability!" << endl;
	for (int k = 0; k < 4; k++)
		availability(phones[k]);

	// Clean up the SmartPhones before exiting
	cout << "Cleaning up" << endl;
	for (int k = 0; k < 4; k++)
		delete phones[k];
}
