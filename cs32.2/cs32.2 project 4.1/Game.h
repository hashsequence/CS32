#include <string>
#include <vector>

#ifndef GAME_H
#define GAME_H
class Game
{
public:
	Game(const std::vector<std::string> &words);
	bool setSecretWord(const std::string &sw);
	int secretWordLength() const;
	void probe(const std::string &probeWord, int &nInRightPlace, int &nInWrongPlace);
	~Game();
private:
	// Prevent people from copying Game objects.		
	Game(const Game&);
	Game& operator=(const Game&);
	// Define your own data structure here
	class HashTable
	{
	private:
		std::vector<std::string>* m_bucket;
		int m_length;
		int hash(std::string itemKey)
		{
			unsigned int i, total = 0;

			for (i = 0; i< itemKey.length(); i++)
				total = total + (i + 1) * itemKey[i];

			total = total % m_length;

			return(total);
		}
	public:
		HashTable(int size)
		{
			if (size * 2 > 100000)
			{
				m_length = 100000;
			}
			m_length = size;
			m_bucket = new std::vector<std::string>[m_length];
		}
		~HashTable()
		{
			delete[] m_bucket;
		}
		HashTable& operator=(const HashTable& other)
		{
			delete[] m_bucket;
			for (int i = 0; i < other.m_length; i++)
			{
				m_bucket[i] = other.m_bucket[i];
			}
			m_length = other.m_length;
		}
		void insert(std::string itemkey)
		{
			int i = hash(itemkey);
			m_bucket[i].push_back(itemkey);
		}
		bool WordExist(const std::string& itemkey)
		{
			int i = hash(itemkey);
			int bucket_size = m_bucket[i].size();

			for (int j = 0; j < bucket_size; j++)
			{
				if (m_bucket[i][j] == itemkey)
					return true;
			}
			return false;
		}
	};
	HashTable m_table;
	// ...
	std::string secretWord;
};

#endif //GAME_H