#include "Multiset.h"
#include <iostream>

Multiset::Multiset() :m_length(0), m_total(0)
{
	//create the dummy node and make next and prev pointing to dummy node
	m_head = new node; 
	m_head->next = m_head;
	m_head->prev = m_head;
}

Multiset::~Multiset()
{
	node* temp = m_head->next;
	node* p = temp;
	//if the list is not empty delete all the items
	if (m_head->next != m_head)
	{
		while (temp != m_head)
		{
			p = temp->next; // use a second pointer to store the original pointer
			delete temp; // delete pointer
			temp = p; // make the pointer to the second pointer
		}
	}
	delete m_head; // delete dummy node
}

Multiset::Multiset(const Multiset& other)
{
	//create dummy node and initialize member variables
	m_head = new node;
	m_head->next = m_head;
	m_head->prev = m_head;
	m_length = 0;
	m_total = 0;

	ItemType value;
	int instances;

	//use get function to retrieve the value and count from the other set and use insert to insert value in the new multiset
	for (int i = 0; i < other.m_length; i++)
	{
		instances = other.get(i, value);
		for (int j = 0; j < instances; j++)
		{
			insert(value);
		}
	}
}

Multiset& Multiset::operator=(const Multiset& other)
{
	if (this == &other)
	{
		return *this;
	}
//create a temp multiset and copy other then swap with temp and return this
	Multiset temp(other);
	swap(temp);
	return *this;
}

bool Multiset::empty() const
{
	if (m_length == 0)
	{
		return true;
	}
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
	// if value is actually in multiset find value and increments its count
		for (node* i = m_head->next; i != m_head; i = i->next)
		{
			if (i->data.value == value)
			{
				i->data.count++;
				m_total++;
				return true;
			}
		}
		// if not insert value
	node* temp = new node; 
	//create the new node
	temp->data.value = value;
	temp->data.count = 1;
	//point the next and prev pointers in the list
	temp->next = m_head;
	temp->prev = m_head->prev;
	m_head->prev->next = temp; // move node pointer previous of temp's next pointing to temp
	m_head->prev = temp; // head prev pointer points to temp
	m_length++;
	m_total++;
	return true;
}

int Multiset::erase(const ItemType& value)
// Remove one instance of value from the multiset if present.
// Return the number of instances removed, which will be 1 or 0.
{
	if (m_head->next == m_head)
		return 0;
	for (node* i = m_head->next; i != m_head; i = i->next)
	{
		if (i->data.value == value) // find the value
		{
			i->data.count--; // decrements its count by 1
			if (i->data.count <= 0) // if count decreases to 0 remove the item from list
			{
				i->prev->next = i->next;
				i->next->prev = i->prev;
				delete i;
				m_length--;
			}
			m_total--;
			return 1;
		}
	}
	return 0;
}

int Multiset::eraseAll(const ItemType& value)
// Remove all instances of value from the multiset if present.
// Return the number of instances removed.
{
	// remove the item from list and decrement the m_length and m_total size correctly
	if (m_head->next == m_head)
		return 0;
	int instances = 0;
	for (node* i = m_head->next; i != m_head; i = i->next)
	{
		if (i->data.value == value)
		{
			i->prev->next = i->next;
			i->next->prev = i->prev;
			instances = i->data.count;
			m_total -= instances;
			delete i;
			m_length--;
			return instances;
		}
	}
	return instances;
}

bool Multiset::contains(const ItemType& value) const
// Return true if the value is in the multiset, otherwise false.
{
	if (m_head->next == m_head)
		return false;
	for (node* i = m_head->next; i != m_head; i = i->next)
	{
		if (i->data.value == value)
		{
			return true;
		}
	}
	return false;
}

int Multiset::count(const ItemType& value) const
// Return the number of instances of value in the multiset.
{
	if (m_head->next == m_head)
		return 0;
	for (node* i = m_head->next; i != m_head; i = i->next)
	{
		if (i->data.value == value)
		{
			return i->data.count;
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
	if (m_head->next == m_head)
		return 0;
	int k = 0;
	for (node* j = m_head->next; j != m_head; j = j->next)
	{
		if (k == i)
		{
			value = j->data.value;
			return j->data.count;
		}
		k++;
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
	//algorithm works as following
	// find the least frequent value
	//then check again to see if another value has same count
	//if not return true
	if (m_head->next == m_head)
	{
		return false;
	}
	node* temp = m_head->next;
	for (node* i = m_head->next->next; i != m_head; i = i->next)
	{
		if (temp->data.count > i->data.count)
		{
			temp = i;
		}
	}
	for (node* i = m_head->next->next; i != m_head; i = i->next)
	{
		if (i->data.count == temp->data.count && i->data.value != temp->data.value)
		{
			return false;
		}
	}
	value = temp->data.value;
	return true;
}

bool Multiset::getSmallestValue(ItemType &value) const
// If there exists a value that is the smallest value among all the values in the multiset, 
// then copy into value that item in the multiset and return true
// Otherwise, return false.
// For both unsigned long and string data type, the lower value can be found by using less than operator (<).
// For example, 10 is smaller than 20, so 10 < 20 is true.
// "ABCDE" is smaller than "XYZ", so "ABCDE" < "XYZ" is true.
{
	if (m_head->next == m_head)
	{
		return false;
	}
	//algorithm work as following
	//first search for smallest value by traversing list
	//return value
	node* temp = m_head->next;
	for (node* i = m_head->next->next; i != m_head; i = i->next)
	{
		if (temp->data.value > i->data.value)
		{
			temp = i;
		}
	}
	value = temp->data.value;
	return true;
}

bool Multiset::getSecondSmallestValue(ItemType &value) const
// Similar to getSmallestValue(), but this time you need to find the second smallest value.
// If there exists a value that is the 2nd smallest value among all the values in the multiset,
// then copy into value that item in the multiset and return true.
// Otherwise, return false.
// Please note that you cannot use any sorting algorithm to sort the multiset.
{
	//algorithm works as following
	//first search for smallest value
	//then search for second smallest value
	//returns false if less than 2 items
	//return true if found second smallest value
	if (m_head->next == m_head || m_length < 2)
	{
		return false;
	}
	node* temp1 = m_head->next;
	node* temp2 = m_head->next;
	for (node* i = m_head->next->next; i != m_head; i = i->next)
	{
		if (temp1->data.value > i->data.value)
		{
			temp1 = i;
		}
	}
	if (temp1 == m_head->next) 
	{
		temp2 = m_head->next->next;
	}
	for (node* i = m_head->next->next; i != m_head; i = i->next)
	{
		if (temp2->data.value > i->data.value && i != temp1)
		{
			temp2 = i;
		}
	}
	value = temp2->data.value;
	return true;
}

bool Multiset::replace(ItemType original, ItemType new_value)
// Replace the item that has the value equal to original by the new value new_value.
// For example, replace("ABCDE","XYZ") will search the multiset for the item "ABCDE" and replace all occurrences of "ABCDE" as "XYZ".
// If the replacement is successful, then return true.
// If there is no item to be replaced, then return false.
{
	//algorithm works as following
	//if the value does not contain the original, is empty return false
	//if the set contains the new value
	//search for original, replace the original with new and increment its count to correct size
	//then eraseAll the new value that was originally in the list
	//if the set does not contain new value
	//replace the orginal value with the new value's value
	if (m_head->next == nullptr)
	{
		return false;
	}
	if (!contains(original))
	{
		return false;
	}
	if (!contains(new_value))
	{
		for (node* i = m_head->next; i != m_head; i = i->next)
		{
			if (i->data.value == original)
			{
				i->data.value = new_value;
				return true;
			}
		}
	}
		node* m_o = nullptr;
		node* m_n = nullptr;
		for (node* i = m_head->next; i != m_head; i = i->next)
		{
			if (i->data.value == original)
			{
				m_o = i;
			}
			if (i->data.value == new_value)
			{
				m_n = i;
			}
		}
		m_n->data.count += m_o->data.count;
		m_total += m_o->data.count;
		eraseAll(original);
		return true;
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
		for (node* i = m_head->next; i != m_head; i = i->next)
		{
			if (i->data.value > value)
			{
				counter += i->data.count;
			}
		}
	}
	else if (op == '<')
	{
		for (node* i = m_head->next; i != m_head; i = i->next)
		{
			if (i->data.value < value)
			{
				counter += i->data.count;
			}
		}
	}
	else if (op == '=')
	{
		for (node* i = m_head->next; i != m_head; i = i->next)
		{
			if (i->data.value == value)
			{
				counter += i->data.count;
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
	//swap the pointers and member variables
	node*t_head = m_head;
	int t_length = m_length;
	int t_total = m_total;

	m_head = other.m_head;
	other.m_head = t_head;

	m_length = other.m_length;
	other.m_length = t_length;

	m_total = other.m_total;
	other.m_total = t_total;
}

void Multiset::copyIntoOtherMultiset(Multiset &other) const
// Insert all the items into the multiset in other.		
{
	//algorithm works byt the following
	//traverse linked list of this set and get the value and count and insert into other set with corresponding count
	ItemType value;
	int instances;
	for (int i = 0; i < m_length; i++)
	{
		get(i, value);
		instances = count(value);
		for (int j = 0; j < instances; j++)
		{
			other.insert(value);
		}
	}
}

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
	//algorithm
	//create two new multiset using copy construction of ms1 and ms2
	//copy ts2 into ts1, then copy assign ts1 into result;
	Multiset t_1(ms1);
	Multiset t_2(ms2);
	t_2.copyIntoOtherMultiset(t_1);
	result = t_1;
}

void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
	//algorithm works by using two loops to search through ms1 and ms2
	//retrieve the values and counts using get
	//take the differene of the two counts
	//if n1 - n2 >0 then put into temp_result
	//if not disregard it
	//if the value is in ms1 but not in ms2 insert value into temp_result
	//copy assign temp to result
	Multiset temp;
	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType ms1_value;
		int ms1_instances = ms1.get(i, ms1_value);
		bool flag = false;
		for (int j = 0; j < ms2.uniqueSize(); j++)
		{
			ItemType ms2_value;
			int ms2_instances = ms2.get(j, ms2_value);
			if (ms2_value == ms1_value)
			{
				flag = true;
				if (ms1_instances > ms2_instances)
				{
					for (int k = 0; k < (ms1_instances - ms2_instances); k++)
					{
						temp.insert(ms1_value);
					}
				}
			}
		}
		if (flag == false)
		{
			for (int k = 0; k < ms1_instances; k++)
			{
				temp.insert(ms1_value);
			}
		}
	}
	result = temp;
}