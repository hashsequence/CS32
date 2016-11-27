
#include "newSet.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

void test()
{
	Set uls;
	assert(uls.insert(10));
	assert(uls.insert(20));
	assert(uls.size() == 2);
	assert(uls.contains(20));
	ItemType x = 30;
	assert(uls.get(0, x) && (x == 10 || x == 20));
	ItemType x2 = 40;
	assert(uls.get(1, x) && (x == 10 || x == 20) &&
		x != x2);
}
/*
void test2()
{
	Set ss;
	assert(ss.insert("roti"));
	assert(ss.insert("pita"));
	assert(ss.size() == 2);
	assert(ss.contains("pita"));
	ItemType x = "bing";
	assert(ss.get(0, x) && (x == "roti" || x == "pita"));
	ItemType x2 = "barbari";
	assert(ss.get(1, x) && (x == "roti" || x == "pita") &&
		x != x2);
}
*/

int main()
{
Set s1;
assert(s1.empty());
ItemType x = 9876543;
assert(!s1.get(42, x) && x == 9876543); // x unchanged by get failure
s1.insert(123456789);
assert(s1.size() == 1);
assert(s1.get(0, x) && x == 123456789);
test();
cout << "Passed all tests" << endl;

Set a(1000);   // a can hold at most 1000 distinct items
Set b(5);      // b can hold at most 5 distinct items
Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
ItemType v[6]  = { 1,2,3,4,5,6};

// No failures inserting 5 distinct items into b
for (int k = 0; k < 5; k++)
	assert(b.insert(v[k]));

// Failure if we try to insert a sixth distinct item into b
assert(!b.insert(v[5]));

Set s2;
s2.insert(275893768);
s2.insert(364635742);
s2.insert(702592060);
s2.insert(643732367);
s2.insert(463543427);
s2.insert(123456789);

Set s3;
s3.insert(643732367);
s3.insert(463543427);
s3.insert(123456789);


ItemType value;


cerr << endl << endl;
cerr << "this is s2" << endl;
for (int k = 0; k < s2.size(); k++)
{
	s2.get(k, value);
	cerr << value << std::endl;
}
cerr<< "this is s3" << endl;
for (int k = 0; k < s3.size(); k++)
{
	s3.get(k, value);
	cerr << value << endl;
}

s2.swap(s3);
cerr << "this is s2 after swap" << endl;
for (int k = 0; k < s2.size(); k++)
{
	s2.get(k, value);
	cerr << value << std::endl;
}
cerr << "this is s3 after swap" << endl;
for (int k = 0; k < s3.size(); k++)
{
	s3.get(k, value);
	cerr << value << endl;
}
s2.swap(s3);
cout << "this is s2 after swap again" << endl;
for (int k = 0; k < s2.size(); k++)
{
	s2.get(k, value);
	cerr << value << endl;
}
cerr << "this is s3 after swap again" << endl;
for (int k = 0; k < s3.size(); k++)
{
	s3.get(k, value);
	cerr << value << endl;
}

cerr << "---------------------------------------------" << endl;

s3 = s2;
cerr << "this is s2 after equal" << endl;
for (int k = 0; k < s2.size(); k++)
{
	s2.get(k, value);
	cerr << value << std::endl;
}
cerr << "this is s3 after equal" << endl;
for (int k = 0; k < s3.size(); k++)
{
	s3.get(k, value);
	cerr << value << endl;
}

cerr << "---------------------------------------------" << endl;


s3.erase(275893768);
s3.erase(364635742);
s3.insert(702592060);
s3.insert(643732367);
s3.insert(463543427);
s3.erase(123456789);
cerr << "this is s3 after erase" << endl;
for (int k = 0; k < s3.size(); k++)
{
	s3.get(k, value);
	cerr << value << endl;
}



}


