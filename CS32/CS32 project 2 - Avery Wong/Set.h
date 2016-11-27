#ifndef SET_H
#define SET_H
#include <string>

typedef std::string ItemType;


class Set
{
private:
	struct node
	{
		ItemType m_data;
		node* m_next;
		node* m_prev;
	};
	node* head;
	node* tail;
	int m_length;
	
public:
	Set();
	~Set();
	Set(const Set& other);
	Set& operator = (const Set& rhs);

	bool empty() const;
	int size() const;
	bool insert(const ItemType& value);
	bool erase(const ItemType& value);
	bool contains(const ItemType& value) const;
	bool get(int pos, ItemType& value) const;
	void swap(Set& other);
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif //SET_H