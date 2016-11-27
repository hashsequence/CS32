#include "Player.h"
#include <algorithm>
#include <cctype>

/*The constructor stores the given word list in a data structure of your choice
as private data member. You may also need to build a data structure inside the
constructor that allows you to efficiently search for the next probe word to
return when generateProbeWord() is called.*/
Player::Player(const std::vector<std::string> &words)
{
	words1 = words;
	wordlist = new map;
	std::random_shuffle(words1.begin(), words1.end());
	std::random_shuffle(words1.begin(), words1.end());
	for (unsigned int i = 0; i < words1.size(); i++)
	{
		(*wordlist)[words1[i]].push_back(words1[i]);
	}
	bulls = 0;
	cows = 0;
	stage1 = false;
	currentProbe = "bbbbbbaaaaaaccccccddddddeeeeeeffffffgggggghhhhhhIiiiiiijjjjjjkkkkkkllllllmmmmmmnnnnnnooooooppppppqqqqqqrrrrrrssssssttttttuuuuuuvvvvvvwwwwwwwwxxxxxxyyyyyyzzzzzz";
}


std::string Player::generateProbeWord()
{
	return currentProbe;
}

void Player::playerProbe(const std::string &probeWord, int &nInRightPlace, int &nInWrongPlace)
{
	int bulls = 0, cows = 0, min_length = currentProbe.size();
	if (currentProbe.size() > static_cast<int>(probeWord.size()))
		min_length = probeWord.size();
	bool* flag = new bool[currentProbe.size()];
	bool*probeFlag = new bool[probeWord.size()];
	for (unsigned int i = 0; i < probeWord.size(); i++)
	{
		probeFlag[i] = false;
	}
	for (size_t i = 0; i < currentProbe.size(); i++)
	{
		flag[i] = false;
	}

	for (int i = 0; i < min_length; i++)
	{
		if (currentProbe[i] == probeWord[i])
		{
			bulls++;
			flag[i] = true;
			probeFlag[i] = true;
		}
	}

	for (size_t i = 0; i < currentProbe.size(); i++)
	{
		for (unsigned int j = 0; j < probeWord.size(); j++)
		{

			if (flag[i] == false && probeFlag[j] == false && currentProbe[i] == probeWord[j])
			{
				cows++;
				flag[i] = true;
				probeFlag[j] = true;
			}
		}
	}
	delete[] flag;
	delete[] probeFlag;
	nInRightPlace = bulls;
	nInWrongPlace = cows;
}

void Player::learn(std::string probe, int nInRightPlace, int nInWrongPlace)
{
	if (stage1 == false)
	{
		bulls = nInRightPlace;
		cows = nInWrongPlace;
		index = bulls + cows;
		currentProbe = (*wordlist)[index].front();
		stage1 = true;
		return;
	}
		bulls = nInRightPlace;
		cows = nInWrongPlace;
		int t_bulls;
		int t_cows;
		for (std::list<std::string>::iterator it = (*wordlist)[index].begin(); it != (*wordlist)[index].end();)
		{
			playerProbe(*it, t_bulls, t_cows);
			if (*it == currentProbe)
			{
				it = (*wordlist)[index].erase(it);
			}
			else if (t_bulls < bulls)
			{
				it = (*wordlist)[index].erase(it);
			}
			else if (t_cows < cows)
			{
				it = (*wordlist)[index].erase(it);
			}
			else
			{
				it++;
			}
		}
		if ((*wordlist)[index].empty() == false)
			currentProbe = (*wordlist)[index].front();
		else
		{
			delete wordlist;
			wordlist = new map;
			for (unsigned int i = 0; i < words1.size(); i++)
			{
				(*wordlist)[words1[i]].push_back(words1[i]);
			}
			index = -1;
			stage1 = false;
			currentProbe = "bbbbbbaaaaaaccccccddddddeeeeeeffffffgggggghhhhhhIiiiiiijjjjjjkkkkkkllllllmmmmmmnnnnnnooooooppppppqqqqqqrrrrrrssssssttttttuuuuuuvvvvvvwwwwwwwwxxxxxxyyyyyyzzzzzz";
		}
		
}

Player::~Player()
{
	delete wordlist;
}