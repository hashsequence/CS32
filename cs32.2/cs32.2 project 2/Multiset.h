#ifndef MULTISET_H
#define MULTISET_H

#include <string>

typedef unsigned long ItemType;

class Multiset
{
private:
	struct item
	{
		ItemType value;
		int count;
	};
	struct node
	{
		item data;
		node* next;
		node* prev;
	};
	node* m_head;
	int m_length;	
	int m_total;
public:
	Multiset();
	~Multiset();
	Multiset(const Multiset& other);
	Multiset& operator=(const Multiset& other);
	bool empty() const;
	int size() const;
	int uniqueSize() const;
	bool insert(const ItemType& value);
	int erase(const ItemType& value);
	int eraseAll(const ItemType& value);
	bool contains(const ItemType& value) const;
	int count(const ItemType& value) const;
	int get(int i, ItemType& value) const;
	bool getLeastFrequentValue(ItemType& value) const;
	bool getSmallestValue(ItemType& value) const;
	bool getSecondSmallestValue(ItemType& value) const;
	bool replace(ItemType original, ItemType new_value);
	int countIf(char op, ItemType value) const;
	void swap(Multiset& other);
	void copyIntoOtherMultiset(Multiset& other) const;
};

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result);
void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result);
#endif //MULTISET_H