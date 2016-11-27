#include "StudentMultiset.h"
#include <iostream>

using namespace std;
StudentMultiset::StudentMultiset()
{

}

bool StudentMultiset::add(unsigned long id)
{
	return m_id.insert(id);
}

int StudentMultiset::size() const
{
	return m_id.size();
}

void StudentMultiset::print() const
{
	ItemType value;
	for (int i = 0; i < m_id.uniqueSize(); i++)
	{
		m_id.get(i, value);
		for (int j = 0; j < m_id.count(value); j++)
		{
			cout << value << endl;
		}
	}

}

