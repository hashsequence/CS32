#include "Set.h"
#include <iostream>

using namespace std;

Set::Set()
{
	m_length = 0;
	head = nullptr;
	tail = nullptr;
}
// head and tail points at null ptr in empty set

Set::~Set()
{
	node *temp;
	while (head != nullptr)
	{
		temp = head->m_next;
		delete head;
		head = temp;
	}
}
//moves the head ptr and delete each element in the set
//sets the new head to the next one using a temp pointer

Set::Set(const Set& other)
{
	m_length = 0;
	head = nullptr;
	tail = nullptr;
	ItemType value;

	for (int k = 0; k < other.size(); k++)
	{
		other.get(k, value);
		this->insert(value);
	}
}


Set& Set::operator = (const Set& rhs)
{
	if (this != &rhs)
	{
		Set temp(rhs);
		swap(temp);
	}
	return *this;
}

bool Set::empty() const
{
	if (m_length == 0)
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
	return m_length;
}

bool Set::insert(const ItemType &value)
{
	bool flag = 1;

	for (node* p = head; p != nullptr; p = p->m_next)//checks if the value is a duplicate
	{
		if (p->m_data == value)
		{
			flag = 0;
		}
		else;

	}
	if (flag == 1)
	{
		node* temp = new node;
		temp->m_data = value;

		if (m_length == 0)// inserting an element into the empty set
		{
			head = temp;
			tail = temp;
			head->m_next = nullptr;
			head->m_prev = nullptr;
			m_length++;
		}
		else if (m_length >= 1) //inserting an element into an empty set with more than one element
		{
			tail->m_next = temp;
			temp->m_prev = tail;
			temp->m_next = nullptr;
			tail = temp;
			m_length++;
		}
		return true;
	}
	return false;
}

bool Set::erase(const ItemType& value)
{
	bool flag = 0;
	node* p = head;
	for (node* p1 = head; p1 != nullptr; p1 = p1->m_next) // checks if the value is there or not, returns false if not
	{
		if (p1->m_data == value)
		{
			flag = 1;
			p = p1;
		}
		else;
	}
	if (flag == 1)// there are four cases: the boudaries, the single set, and the one where it is in between two elements
	{
		if (p->m_prev == nullptr && p->m_next != nullptr && m_length >= 1)
		{
			head = p->m_next;
			head->m_prev = nullptr;
			delete p;
			m_length--;
		}
		else if (p->m_prev != nullptr && p->m_next == nullptr && m_length >= 1)
		{
			tail = p->m_prev;
			tail->m_next = nullptr;
			delete p;
			m_length--;
		}
		else if (p->m_prev != nullptr && p->m_next != nullptr && m_length >= 1)
		{
			p->m_prev->m_next = p->m_next;
			p->m_next->m_prev = p->m_prev;
			delete p;
			m_length--;
		}
		else if (p->m_prev == nullptr && p->m_next == nullptr && m_length >= 1)
		{
			head = nullptr;
			tail = nullptr;
			delete p;
			m_length--;
		}
		return true;
	}
	return false;
}

bool Set::contains(const ItemType& value) const
{
	for (node* p = head; p != nullptr; p = p->m_next)
	{
		if (p->m_data == value)
		{
			return true;
		}
	}
	return false;
}

bool Set::get(int pos, ItemType& value) const
{
	if (pos >= 0 && pos < m_length)
	{
		node* p = head;
		for (int k = 0; k < pos; k++)
		{
			p = p->m_next;
		}
		value = p->m_data;
		return true;
	}
	return false;
}

void Set::swap(Set& other)
{
	node* t_head = head;
	node* t_tail = tail;
	int t_length = m_length;
	//switches the heads and tails of both sets
	head = other.head; 
	tail = other.tail;
	other.head = t_head;
	other.tail = t_tail;
	//switches the lengths
	m_length = other.m_length;
	other.m_length = t_length;
}

//non-member functions

void unite(const Set& s1, const Set& s2, Set& result)
{
	ItemType s1_value;
	ItemType s2_value;
	int s1_length = s1.size();
	int s2_length = s2.size();
	//checks which size is longer
	if (s1_length >= s2_length)
	{
		for (int k = 0; k < s1_length; k++)
		{
			s1.get(k, s1_value);
			s2.get(k, s2_value);
			result.insert(s1_value);//inserts the respective values into the result set, even if there is aliasing involve, the result set will always contain all the elements in every set
			result.insert(s2_value);
		}
	}
	else
	{
		for (int k = 0; k < s2_length; k++)
		{
			s1.get(k, s1_value);
			s2.get(k, s2_value);
			result.insert(s1_value);
			result.insert(s2_value);
		}
	}
}


void subtract(const Set& s1, const Set& s2, Set& result)
{
	ItemType s1_value;
	ItemType s2_value;
	int s1_length = s1.size();
	int s2_length = s2.size();
	//checks for the lengths
	//important fact about aliasing is that it cannot look past the original lengths of the two sets two avoid counting the ones that could
	//possibly be inserted during the process
	if (s1_length >= s2_length)
	{
		for (int k = 0; k < s1_length; k++)
		{
			s1.get(k, s1_value);
			if (k < s2_length)
			{
				s2.get(k, s2_value);
			}
			if (s2.contains(s1_value) == false)
			{
				result.insert(s1_value);
			}
		}	
	}
	else
	{
		for (int k = 0; k < s2_length; k++)
		{
			if (k < s1_length)
			{
				s1.get(k, s1_value);
			}

			s2.get(k, s2_value);
			if (s2.contains(s1_value) == false)
			{
				result.insert(s1_value);
			}
		}
	}
}