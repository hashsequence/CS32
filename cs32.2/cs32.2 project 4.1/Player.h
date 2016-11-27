#include <string>
#include <vector>
#include <cctype>
#include <stack>
#include <list>
#ifndef PLAYER_H
#define PLAYER_H
class Player
{
public:
	Player(const std::vector<std::string> &words);
	std::string generateProbeWord();
	void learn(std::string probe, int nInRightPlace, int nInWrongPlace);
	~Player();
private:
	// Prevent people from copying Player objects.		
	Player(const Player&);
	Player& operator=(const Player&);
	// Define your own data structure here	
	class map
	{
	public:
		std::list<std::string>& operator[](std::string w)
		{
			return table[hash(w)];
		}
		std::list<std::string>& operator[](int n)
		{
			return table[n-1];
		}
		std::string get(int i1, int i2)
		{
			int counter = 0;
			for (std::list<std::string>::iterator it = table[i1 - 1].begin(); it != table[i1 - 1].end(); it++)
			{
				if (counter == i2)
				{
					return *it;
				}
				counter++;
			}
			return "";
		}
	private:
		std::list<std::string> table[21];
		int hash(std::string w)
		{
			return (w.size()-1);
		}
	};
	std::string currentProbe;
	int bulls;
	int cows;
	bool stage1;
	int index;
	void playerProbe(const std::string &probeWord, int &nInRightPlace, int &nInWrongPlace);
	map* wordlist;
	std::vector<std::string> words1;
};

#endif