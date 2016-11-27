#include "Set.h"
#include <iostream>

Set::Set()
{
	length = 0;
}

bool Set::empty() const
{
	if (length == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Set::size() const
{
	return length;
}

bool Set::insert(const ItemType& value) 
{
	if (length < DEFAULT_MAX_ITEMS)
	{
		bool flag1 = 0;
		int place = 0;
		for (int k = 0; k < length; k++)
		{
			if (value == m_set[k])
			{
				return false;
			}
			else;
		}
		m_set[length] = value;
		length++;
		return true;
	}
	else
	{
		return false;
	}
}
// Insert value into the set if it is not already present.  Return
// true if the value was actually inserted.  Leave the set unchanged
// and return false if the value was not inserted (perhaps because it
// is already in the set or because the set has a fixed capacity and
// is full).

bool Set::erase(const ItemType& value)
{
	bool flag = 0;
	for (int k = 0; k < length; k++)
	{
		if (m_set[k] == value)
		{
			flag = 1;
		}
	}
	if (flag == 1)
	{
		ItemType temp[DEFAULT_MAX_ITEMS];
		int i = 0;
		for (int k = 0; k < length; k++)
		{
			if (m_set[k] != value)
			{
				temp[i] = m_set[k];
				i++;
			}
			else;
		}
		length = i;
		for (int k = 0; k < length; k++)
		{
			m_set[k] = temp[k];
		}
		return true;
	}
	else
	{
		return false;
	}

	
}
// Remove the value from the set if present.  Return true if the
// value was removed; otherwise, leave the set unchanged and
// return false.
bool Set::contains(const ItemType& value) const
{
	for (int k = 0; k < length; k++)
	{
		if (value == m_set[k])
		{
			return true;
		}
	}
	return false;
}
// Return true if the value is in the set, otherwise false.

bool Set::get(int i, ItemType& value) const
{
	if (0 <= i && i < this->size())
	{
		value = m_set[i];
		return true;
	}
	else
	{
		return false;
	}
}
// If 0 <= i < size(), copy into value an item in the set and
// return true.  Otherwise, leave value unchanged and return false.
// (See below for details about this function.)

void Set::swap(Set& other)
{
	ItemType* right = m_set;
	ItemType* left = other.m_set;
	ItemType temp = *right;
	int temp_length = 0;

	if (length >= other.length)
	{
		for (int k = 0; k < length; k++)
		{
			temp = *(right+k);
			*(right+k) = *(left+k);
			*(left+k) = temp;

		}
	}
	else
	{
		for (int k = 0; k < other.length; k++)
		{
			temp = *(right + k);
			*(right + k) = *(left + k);
			*(left + k) = temp;

		}
	}
	temp_length = length;
	length = other.length;
	other.length = temp_length;
}
// Exchange the contents of this set with the other one.