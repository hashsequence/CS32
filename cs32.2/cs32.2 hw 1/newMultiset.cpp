#include "newMultiset.h"
#include <iostream>

Multiset::Multiset(int max_size) : m_length(0), m_maxSize(max_size), m_total(0)
{
	m_set = new items[max_size];
}

Multiset::~Multiset()
{
	delete[] m_set;
}

Multiset::Multiset(const Multiset& other)
{
	m_length = other.m_length;
	m_maxSize = other.m_maxSize;
	m_total = other.m_total;
	m_set = new items[m_maxSize];

	for (int i = 0; i < m_maxSize; i++)
	{
		m_set[i] = other.m_set[i];
	}
}

Multiset& Multiset::operator=(const Multiset& other)
{
	if (this == &other)
	{
		return *this;
	}
	delete[] m_set;
	m_length = other.m_length;
	m_maxSize = other.m_maxSize;
	m_total = other.m_total;
	m_set = new items[m_maxSize];

	for (int i = 0; i < m_maxSize; i++)
	{
		m_set[i] = other.m_set[i];
	}

	return *this;

}

bool Multiset::empty() const
{
	if (m_length == 0)
		return true;
	return false;
}

int Multiset::size() const
{
	return m_total;
}

int Multiset::uniqueSize() const
// Return the number of distinct items in the multiset.  For example,
// the uniqueSize of a multiset containing "cumin", "cumin", "cumin",
// "turmeric" is 2.
{
	return m_length;
}

bool Multiset::insert(const ItemType& value)
// Insert value into the multiset.  Return true if the value was
// actually inserted.  Return false if the value was not inserted
// (perhaps because the multiset has a fixed capacity and is full)
{
	for (int i = 0; i < m_length; i++)
	{
		if (m_set[i].m_value == value)
		{
			(m_set[i].count)++;
			m_total++;
			return true;
		}
	}
	if (m_length >= m_maxSize)
	{
		return false;
	}
	m_set[m_length].m_value = value;
	m_set[m_length].count = 1;
	m_total++;
	m_length++;
	return true;

}

int Multiset::erase(const ItemType& value)
// Remove one instance of value from the multiset if present.
// Return the number of instances removed, which will be 1 or 0.
{
	if (!(this->empty()))
	{
		for (int i = 0; i < m_length; i++)
		{
			if (m_set[i].m_value == value)
			{
				m_set[i].count--;
				if (m_set[i].count <= 0)
				{
					if (i != m_length - 1)
					{
						for (int j = i; j < m_length; j++)
						{
							m_set[j] = m_set[j + 1];
						}
					}
					m_length--;
				}
				m_total--;
				return 1;
			}
		}
	}
	return 0;

}

int Multiset::eraseAll(const ItemType& value)
// Remove all instances of value from the multiset if present.
// Return the number of instances removed.
{
	if (!(this->contains(value)))
	{
		return 0;
	}
	if (this->empty())
	{
		return 0;
	}
	int instances = 0;
	for (int i = 0; i < m_length; i++)
	{
		if (m_set[i].m_value == value)
		{
			instances = m_set[i].count;
			if (i != m_length - 1)
			{
				for (int j = i; j < m_length; j++)
				{
					m_set[j] = m_set[j + 1];
				}
			}
			m_length--;
			m_total -= instances;
			return instances;
		}
	}
	return instances;

}

bool Multiset::contains(const ItemType& value) const
// Return true if the value is in the multiset, otherwise false.
{
	for (int i = 0; i < m_length; i++)
	{
		if (m_set[i].m_value == value)
		{
			return true;
		}
	}
	return false;
}

int Multiset::count(const ItemType& value) const
// Return the number of instances of value in the multiset.
{
	int counter = 0;
	if (!(this->empty()))
	{
		for (int i = 0; i < m_length; i++)
		{
			if (m_set[i].m_value == value)
			{
				return m_set[i].count;
			}
		}
	}
	return 0;

}

int Multiset::get(int i, ItemType& value) const
// If 0 <= i < uniqueSize(), copy into value an item in the
// multiset and return the number of instances of that item in
// the multiset.  Otherwise, leave value unchanged and return 0.
// (See below for details about this function.)
{
	if (0 <= i && i < uniqueSize())
	{
		value = m_set[i].m_value;
		return m_set[i].count;
	}
	return 0;
}

bool Multiset::getLeastFrequentValue(ItemType &value) const
// If there exists a single item that has the least number of instances in the multiset, 
// then copy into value that item in the multiset and return true.
// However, if there exist more than 1 item that have the least number of instances in the multiset,
// then do not copy into value any item in the multiset and return false. In other words, value should remain unchanged.
// If there's no item in the multiset, return false.
{
	if (this->empty())
	{
		return false;
	}
	else if (m_length == 1)
	{
		value = m_set[0].m_value;
		return true;
	}
	else
	{
		ItemType t_value = m_set[0].m_value;
		int t_count = m_set[0].count;


		for (int i = 1; i < m_length; i++)
		{
			if (m_set[i].count < t_count)
			{
				t_value = m_set[i].m_value;
				t_count = m_set[i].count;
			}
		}
		for (int i = 0; i < m_length; i++)
		{
			if (m_set[i].count == t_count && m_set[i].m_value != t_value)
			{
				return false;
			}
		}
		value = t_value;
		return true;
	}
}

bool Multiset::getSmallestValue(ItemType &value) const
// If there exists a value that is the smallest value among all the values in the multiset, 
// then copy into value that item in the multiset and return true
// Otherwise, return false.
// For both unsigned long and string data type, the lower value can be found by using less than operator (<).
// For example, 10 is smaller than 20, so 10 < 20 is true.
// "ABCDE" is smaller than "XYZ", so "ABCDE" < "XYZ" is true.
{
	if (this->empty())
	{
		return false;
	}
	else if (m_length == 1)
	{
		value = m_set[0].m_value;
		return true;
	}
	else
	{
		items t_item = m_set[0];
		for (int i = 1; i < m_length; i++)
		{
			if (m_set[i].m_value < t_item.m_value)
			{
				t_item = m_set[i];
			}
		}
		value = t_item.m_value;
		return true;
	}
}

bool Multiset::getSecondSmallestValue(ItemType &value) const
// Similar to getSmallestValue(), but this time you need to find the second smallest value.
// If there exists a value that is the 2nd smallest value among all the values in the multiset,
// then copy into value that item in the multiset and return true.
// Otherwise, return false.
// Please note that you cannot use any sorting algorithm to sort the multiset.
{
	if (this->empty())
	{
		return false;
	}
	else if (m_length == 1)
	{
		return false;
	}
	else
	{
		ItemType t_item1 = m_set[0].m_value;
		int item1_pos = 0;

		for (int i = 0; i < m_length; i++)
		{
			if (m_set[i].m_value < t_item1)
			{
				t_item1 = m_set[i].m_value;
				item1_pos = i;
			}
		}

		ItemType t_item2 = m_set[0].m_value;
		int item2_pos = 0;

		if (item1_pos == 0)
		{
			t_item2 = m_set[1].m_value;
			int item2_pos = 1;
		}

		for (int i = 0; i < m_length; i++)
		{
			if ((m_set[i].m_value < t_item2) && (m_set[i].m_value != t_item1))
			{
				t_item2 = m_set[i].m_value;
			}
		}
		value = t_item2;
		return true;
	}
}

bool Multiset::replace(ItemType original, ItemType new_value)
// Replace the item that has the value equal to original by the new value new_value.
// For example, replace("ABCDE","XYZ") will search the multiset for the item "ABCDE" and replace all occurrences of "ABCDE" as "XYZ".
// If the replacement is successful, then return true.
// If there is no item to be replaced, then return false.
{
	if (this->empty())
	{
		return false;
	}
	if (!(this->contains(original)))
	{
		return false;
	}
	if (this->contains(new_value))
	{
		int o_index = -1;
		int n_index = -1;

		for (int i = 0; i < m_length; i++)
		{
			if (m_set[i].m_value == original)
			{
				o_index = i;
			}
			if (m_set[i].m_value == new_value)
			{
				n_index = i;
			}
		}
		m_set[n_index].count += m_set[o_index].count;
		m_total += m_set[o_index].count;
		eraseAll(original);
		return true;
	}
	else
	{
		for (int i = 0; i < m_length; i++)
		{
			if (m_set[i].m_value == original)
			{
				m_set[i].m_value = new_value;
				return true;
			}
		}
		return false;
	}
}

int Multiset::countIf(char op, ItemType value) const
// Count the number of items that the item is greater than, less than, or equal to value.
// For example: 
// countIf('>',100) returns the number of items in multiset in which the item is greater than 100.
// countIf('=',"ABC") returns the number of items in multiset in which the item is equal to "ABC".
// countIf('<',50) returns the number of items in multiset in which the item is less than 50.
// If op is a character other than '>','=', and '<', then return -1.
{
	int counter = 0;
	if (op == '>')
	{
		for (int i = 0; i < m_length; i++)
		{
			if (m_set[i].m_value > value)
			{
				counter += m_set[i].count;
			}
		}
	}
	else if (op == '<')
	{
		for (int i = 0; i < m_length; i++)
		{
			if (m_set[i].m_value < value)
			{
				counter += m_set[i].count;
			}
		}
	}
	else if (op == '=')
	{
		for (int i = 0; i < m_length; i++)
		{
			if (m_set[i].m_value == value)
			{
				counter += m_set[i].count;
			}
		}
	}
	else
	{
		return -1;
	}
	return counter;
}

void Multiset::swap(Multiset& other)
// Exchange the contents of this multiset with the other one.
{
	
	items* t_set = m_set;
	int t_length = m_length;
	int t_maxSize = m_maxSize;
	int t_total = m_total;

	m_set = other.m_set;
	m_length = other.m_length;
	m_maxSize = other.m_maxSize;
	m_total = other.m_total;

	other.m_set = t_set;
	other.m_length = t_length;
	other.m_maxSize = t_maxSize;
	other.m_total = t_total;
	
}

void Multiset::copyIntoOtherMultiset(Multiset &other)
// Insert all the items into the multiset in other.		
{
	int delta_length = 0;
	for (int i = 0; i < m_length; i++)
	{
		bool flag = false;
		for (int j = 0; j < other.m_length; j++)
		{
			if (other.m_set[j].m_value == m_set[i].m_value)
			{
				other.m_set[j].count += m_set[i].count;
				other.m_total += m_set[i].count;
				flag = true;
			}
		}
		if (flag == false && (other.m_length + delta_length) < DEFAULT_MAX_ITEMS)
		{
			other.m_set[other.m_length + delta_length] = m_set[i];
			other.m_total += m_set[i].count;
			delta_length++;
		}
	}
	other.m_length += delta_length;
}

