#include "Game.h"
#include <algorithm>

Game::Game(const std::vector<std::string> &words) : m_table(words.size())
{
	for (unsigned int i = 0; i < words.size(); i++)
		m_table.insert(words[i]);
}

Game::~Game()
{

}

bool Game::setSecretWord(const std::string &sw)
{
	if (m_table.WordExist(sw))
	{
		secretWord = sw;
		return true;
	}
	secretWord = sw;
	return false;

}
int Game::secretWordLength() const
{
	return static_cast<int>(secretWord.size());
}

void Game::probe(const std::string &probeWord, int &nInRightPlace, int &nInWrongPlace)
{
	int bulls = 0, cows = 0, min_length = secretWordLength();
	if (secretWordLength() > static_cast<int>(probeWord.size()))
		min_length = probeWord.size();
	bool* flag = new bool[secretWordLength()];
	bool*probeFlag = new bool[probeWord.size()];
	for (unsigned int i = 0; i < probeWord.size(); i++)
	{
		probeFlag[i] = false;
	}
	for (int i = 0; i < secretWordLength(); i++)
	{
		flag[i] = false;
	}

	for (int i = 0; i < min_length; i++)
	{
		if (secretWord[i] == probeWord[i])
		{
			bulls++;
			flag[i] = true;
			probeFlag[i] = true;
		}
	}

	for (int i = 0; i < secretWordLength(); i++)
	{
		for (unsigned int j = 0; j < probeWord.size(); j++)
		{

			if (flag[i] == false && probeFlag[j] == false && secretWord[i] == probeWord[j])
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