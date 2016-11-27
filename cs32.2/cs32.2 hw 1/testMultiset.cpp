#include "Multiset.h"
#include <iostream>
#include <cassert>
using namespace std;



/*
void test1()
{
	Multiset ms;
	ms.insert("fennel");
	ms.insert("fennel");
	ms.insert("fenugreek");
	ms.insert("fennel");
	for (int k = 0; k < ms.uniqueSize(); k++)
	{
		string x;
		int n = ms.get(k, x);
		cout << x << " occurs " << n << " times." << endl;
	}
	cout << "past test1" << endl;

}

void test2()
{
	Multiset ms;
	ms.insert("cinnamon");
	ms.insert("galangal");
	ms.insert("cinnamon");
	string s1;
	int n1 = ms.get(1, s1);
	assert((s1 == "cinnamon"  &&  n1 == 2) || (s1 == "galangal"  &&  n1 == 1));
	string s2;
	int n2 = ms.get(1, s2);
	assert(s2 == s1  &&  n2 == n1);
	cout << "pass test2" << endl;
}


void test4()
{
	Multiset ms;
	assert(ms.empty());
	string x = "dill";
	assert(ms.get(0, x) == 0 && x == "dill");  // x unchanged by get failure
	assert(!ms.contains("tamarind"));
	ms.insert("tamarind");
	ms.insert("tamarind");
	assert(ms.size() == 2 && ms.uniqueSize() == 1);
	assert(ms.get(1, x) == 0 && x == "dill");  // x unchanged by get failure
	assert(ms.get(0, x) == 2 && x == "tamarind");
	cout << "Pass test4" << endl;
}

void test5()
{
	ItemType value;
	Multiset ms1, ms2;

	assert(ms2.getSmallestValue(value) == false);
	assert(ms2.getSecondSmallestValue(value) == false);
	assert(ms2.getLeastFrequentValue(value) == false);

	ms1.insert("ABCDE"); 
	ms1.insert("ABCDE");
	ms1.insert("XYZ");
	ms1.insert("GDP");

	ms2.insert("Hello"); ms2.insert("Hello");
	ms2.insert("PPP");   ms2.insert("PPP");
	ms2.insert("XYZ");
	assert(ms1.getSmallestValue(value) == true && value == "ABCDE");
	assert(ms1.getSecondSmallestValue(value) == true && value == "GDP");
	value = "CS32";
	assert(ms1.getLeastFrequentValue(value) == false && value == "CS32");

	assert(ms2.getSmallestValue(value) == true && value == "Hello");
	assert(ms2.getSecondSmallestValue(value) == true && value == "PPP");
	assert(ms2.getLeastFrequentValue(value) == true && value == "XYZ");
	cout << "past test5" << endl;
}

void test6()
{
	ItemType value;
	Multiset ms1, ms2;

	ms1.insert("ABCDE"); 
	ms1.insert("ABCDE");
	ms1.insert("XYZ"); 
	ms1.insert("GDP");

	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType value;
		ms1.get(i, value);
		cout << value << " count#: " << ms1.count(value) << endl;
	}
	cout << "ms1 unique size: " << ms1.uniqueSize() << endl;
	cout << "ms1 size: " << ms1.size() << endl;

	ms2.insert("Hello"); ms2.insert("ABC");
	ms2.insert("XYZ");   ms2.insert("PPP");
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl;

	ms1.replace("ABCDE", "GDP");

	
	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType value;
		ms1.get(i, value);
		cout << value << " count#: " << ms1.count(value) << endl;
	}
	cout << "ms1 unique size: " << ms1.uniqueSize() << endl;
	cout << "ms1 size: " << ms1.size() << endl;
	assert(ms1.uniqueSize() == 2 && ms1.size() == 4);

	ms2.replace("Hello", "abc");
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl;
	assert(ms2.uniqueSize() == 4 && ms2.size() == 4);
	cout << "past test6" << endl;
}

void test7()
{
	Multiset ms1;
	ms1.insert("cumin");
	ms1.insert("cumin");
	ms1.insert("cumin");
	ms1.insert("turmeric");
	ms1.insert("jk");
	Multiset ms2;
	ms2.insert("coriander");
	ms2.insert("cumin");
	ms2.insert("cardamom");
	ms2.insert("jl");
	ms1.swap(ms2);  // exchange contents of ms1 and ms2
	assert(ms1.size() == 4 && ms1.count("coriander") == 1 &&
		ms1.count("cumin") == 1 && ms1.count("cardamom") == 1 && ms1.count("jl"));
	assert(ms2.size() == 5 && ms2.count("cumin") == 3 &&
		ms2.count("turmeric") == 1 && ms2.count("jk"));
	cout << "past test7" << endl;
}
void test8()
{
	Multiset ms;
	ms.insert("cumin");
	assert(!ms.contains(""));
	ms.insert("nutmeg");
	ms.insert("");
	ms.insert("saffron");
	assert(ms.contains(""));
	ms.erase("cumin");
	assert(ms.size() == 3 && ms.contains("saffron") && ms.contains("nutmeg") &&
		ms.contains(""));
	cout << "past test8" << endl;
}
void test9()
{
	ItemType value;
	Multiset ms1, ms2;

	ms1.insert("ABCDE"); ms1.insert("ABCDE");
	ms1.insert("XYZ"); ms1.insert("GDP");

	ms2.insert("Hello"); ms2.insert("ABCDE");
	ms2.insert("XYZ");   ms2.insert("PPP");

	assert(ms2.countIf('=', "ABCDE") == 1);

	ms1.copyIntoOtherMultiset(ms2);
	assert(ms2.uniqueSize() == 5 && ms2.size() == 8);

	assert(ms2.countIf('=', "ABCDE") == 3);
	assert(ms2.countIf('>', "ABCDE") == 5);
	assert(ms2.countIf('<', "ABCDE") == 0);
	cout << "past test9" << endl;
}
void test10()
{
	ItemType value;
	Multiset ms1, ms2;

	ms1.insert("ABCDE");
	ms1.insert("ABCDE");
	ms1.insert("GDP");
	ms1.insert("XYZ");
	ms1.insert("GDP");

	ms1.eraseAll("ABCDE");

	
	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType value;
		ms1.get(i, value);
		cout << value << " count#: " << ms1.count(value) << endl;
	}
	cout << "ms1 unique size: " << ms1.uniqueSize() << endl;
	cout << "ms1 size: " << ms1.size() << endl;


	ms2.insert("Hello");
	ms2.insert("ABCDE");
	ms2.insert("XYZ"); 
	ms2.insert("PPP");


	cout << ms2.eraseAll("Hello") << endl;
	cout << ms2.eraseAll("ABCDE") << endl;
	cout << ms2.eraseAll("XYZ") << endl;
	cout << ms2.eraseAll("PPP") << endl;
	assert(ms2.empty() == true);

	ms2.insert("Hello");
	ms2.insert("ABCDE");
	ms2.insert("XYZ");
	ms2.insert("PPP");

	cout << ms2.replace("hello", "ABCDE") << endl;
	cout << ms2.replace("XYZ", "ABCDE") << endl;
	cout << ms2.replace("PPP", "DELTA") << endl;
	cout << ms2.replace("hello", "ABCDE") << endl;
	cout << "erase all should be false: " << ms2.eraseAll("XYZ") << endl;

	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl;

	

	assert(ms2.size() == 4 && ms2.uniqueSize() == 3);
	assert(ms2.count("ABCDE") == 2 && ms2.count("DELTA") == 1);

	cout << endl << endl;
	//copy into multiset test
	ms1.insert("Hello");
	ms1.insert("Hello");
	ms1.insert("Hello");
	ms1.insert("Hello");
	ms2.insert("Hello");
	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType value;
		ms1.get(i, value);
		cout << value << " count#: " << ms1.count(value) << endl;
	}
	cout << "ms1 unique size: " << ms1.uniqueSize() << endl;
	cout << "ms1 size: " << ms1.size() << endl << endl;

	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;
	cout << "after copy into m2" << endl;
	ms1.copyIntoOtherMultiset(ms2);
	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl;

	cout << "Swap test" << endl << "----------------------------------------" << endl;

	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType value;
		ms1.get(i, value);
		cout << value << " count#: " << ms1.count(value) << endl;
	}
	cout << "ms1 unique size: " << ms1.uniqueSize() << endl;
	cout << "ms1 size: " << ms1.size() << endl << endl;

	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;

	cout << "swapping" << endl;
	ms1.swap(ms2);

	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType value;
		ms1.get(i, value);
		cout << value << " count#: " << ms1.count(value) << endl;
	}
	cout << "ms1 unique size: " << ms1.uniqueSize() << endl;
	cout << "ms1 size: " << ms1.size() << endl << endl;

	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;

	cout << "Swap again!" << endl;
	ms2.swap(ms1);

	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType value;
		ms1.get(i, value);
		cout << value << " count#: " << ms1.count(value) << endl;
	}
	cout << "ms1 unique size: " << ms1.uniqueSize() << endl;
	cout << "ms1 size: " << ms1.size() << endl << endl;

	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;

	cout << "replace test" << endl << "----------------------------------------" << endl;
	cout << endl << "--------ms1---------" << endl;;
	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType value;
		ms1.get(i, value);
		cout << value << " count#: " << ms1.count(value) << endl;
	}
	cout << "ms1 unique size: " << ms1.uniqueSize() << endl;
	cout << "ms1 size: " << ms1.size() << endl << endl;
	cout << "--------ms2---------" << endl;;
	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;

	cout <<  endl <<"replacng Hello with GDP in ms1" << endl;
	ms1.replace("Hello", "GDP");

	cout << endl << "--------ms1---------" << endl;;
	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType value;
		ms1.get(i, value);
		cout << value << " count#: " << ms1.count(value) << endl;
	}
	cout << "ms1 unique size: " << ms1.uniqueSize() << endl;
	cout << "ms1 size: " << ms1.size() << endl << endl;

	cout << endl << "replacng GDP with KGB in ms1" << endl;
	ms1.replace("GDP", "KGB");

	cout << endl << "--------ms1---------" << endl;;
	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType value;
		ms1.get(i, value);
		cout << value << " count#: " << ms1.count(value) << endl;
	}
	cout << "ms1 unique size: " << ms1.uniqueSize() << endl;
	cout << "ms1 size: " << ms1.size() << endl << endl;

	
	
	cout << "pass test10" << endl;



	
}
*/


void test3()
{
	Multiset ms;
	assert(ms.empty());
	unsigned long x = 999;
	assert(ms.get(0, x) == 0 && x == 999);  // x unchanged by get failure
	assert(!ms.contains(42));

	ms.insert(42);
	ms.insert(42);

	assert(!ms.getSecondSmallestValue(x) && x == 999);
	assert(ms.size() == 2 && ms.uniqueSize() == 1);
	assert(ms.get(1, x) == 0 && x == 999);  // x unchanged by get failure
	assert(ms.get(0, x) == 2 && x == 42);

	assert(ms.getSmallestValue(x) && x == 42);
	assert(ms.countIf('=', 42) == 2);
	assert(ms.countIf('>', 42) == 0);
	assert(ms.countIf('<', 42) == 0);

	cout << "Passed test3" << endl;
}

void test11()
{
	Multiset ms1, ms2;
	ItemType value = 0;


	ms1.insert(50);
	ms1.insert(150);
	ms1.insert(250);
	ms1.insert(350);
	ms1.insert(450);

	ms2.insert(30);
	ms2.insert(60);
	ms2.insert(30); 
	ms2.insert(30);
	ms2.insert(350);
	ms2.insert(350); 
	ms2.insert(350); 
	ms2.insert(350);
	ms2.insert(450);
	ms2.insert(350);
	ms2.insert(450); 
	ms2.insert(450); 
	ms2.insert(450);

	cout << "amount less than 150: " << ms1.countIf('>', 150);
	cout << endl << "--------ms1---------" << endl;;
	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType value;
		ms1.get(i, value);
		cout << value << " count#: " << ms1.count(value) << endl;
	}
	cout << "ms1 unique size: " << ms1.uniqueSize() << endl;
	cout << "ms1 size: " << ms1.size() << endl << endl;
	cout << "--------ms2---------" << endl;;
	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;

	cout << "ms1: least frequent value is " << ms1.getLeastFrequentValue(value);
	cout << " and value is " << value << endl;
	cout << "ms2: least frequent value is " << ms2.getLeastFrequentValue(value);
	cout << " and value is " << value << endl;

	cout << "ms1: smallest value is " << ms1.getSmallestValue(value);
	cout << " and value is " << value << endl;
	cout << "ms2: smallest value is " << ms2.getSmallestValue(value);
	cout << " and value is " << value << endl;

	cout << "ms1: second smallest value is " << ms1.getSecondSmallestValue(value);
	cout << " and value is " << value << endl;
	cout << "ms2: second smallest value is " << ms2.getSecondSmallestValue(value);
	cout << " and value is " << value << endl;

	cout << "---------copyintOtherMultiset ms1 into ms2---------" << endl;
	ms1.copyIntoOtherMultiset(ms2);
	cout << "--------ms2---------" << endl;;
	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;
	cout << "ms2: smallest value is " << ms2.getSmallestValue(value);
	cout << " and value is " << value << endl;
	cout << "ms2: second smallest value is " << ms2.getSecondSmallestValue(value);
	cout << " and value is " << value << endl;

}

void test12()
{
	Multiset ms1, ms2;
	ItemType value1 = 0;
	for (int i = 0; i < 150; i++)
	{
		ms1.insert(value1);
		value1++;
	}
	for (int i = 0; i < 100; i++)
	{
		ms2.insert(value1);
		value1++;
	}

	ItemType value = 0;

	cout << endl << "--------ms1---------" << endl;;
	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType value;
		ms1.get(i, value);
		cout << value << " count#: " << ms1.count(value) << " ";
		if (i % 10 == 0)
		{
			cout << endl;
		}
		
	}
	cout << endl << "ms1 unique size: " << ms1.uniqueSize() << endl;
	cout << "ms1 size: " << ms1.size() << endl << endl;
	cout << "--------ms2---------" << endl;;
	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << " ";
		if (i % 10 == 0)
		{
			cout << endl;
		}
	}
	cout << endl << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;

	cout << "---------copyintOtherMultiset ms1 into ms2---------" << endl;
	ms1.copyIntoOtherMultiset(ms2);
	cout << "--------ms2---------" << endl;;
	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;
	cout << "ms2: smallest value is " << ms2.getSmallestValue(value);
	cout << " and value is " << value << endl;
	cout << "ms2: second smallest value is " << ms2.getSecondSmallestValue(value);
	cout << " and value is " << value << endl;

}

void test13()
{
	cout << endl << "++++++++++++++++++++test13+++++++++++++++++" << endl;
	Multiset ms1, ms2;
	ItemType value = 0;

	cout << "ms1 and ms2 should be empty: " << ms1.empty() << " " << ms2.empty();

	ms1.insert(50);
	ms1.insert(20);
	ms1.insert(20);
	ms1.insert(150);
	ms1.insert(250);
	ms1.insert(350);
	ms1.insert(450);

	ms2.insert(30);
	ms2.insert(60);
	ms2.insert(30);
	ms2.insert(30);
	ms2.insert(350);
	ms2.insert(5);
	ms2.insert(5);
	ms2.insert(350);
	ms2.insert(350);
	ms2.insert(350);
	ms2.insert(450);
	ms2.insert(350);
	ms2.insert(450);
	ms2.insert(450);
	ms2.insert(450);

	cout << endl << "--------ms1---------" << endl;;
	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType value;
		ms1.get(i, value);
		cout << value << " count#: " << ms1.count(value) << endl;
	}
	cout << "ms1 unique size: " << ms1.uniqueSize() << endl;
	cout << "ms1 size: " << ms1.size() << endl << endl;

	cout << "--------ms2---------" << endl;;
	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;

	cout << "---------------erase test------------" << endl;
	ms1.erase(350);
	ms2.erase(450);

	cout << "erase 350 from ms1 and erase 450 from ms2" << endl;
	cout << endl << "--------ms1---------" << endl;;
	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType value;
		ms1.get(i, value);
		cout << value << " count#: " << ms1.count(value) << endl;
	}
	cout << "ms1 unique size: " << ms1.uniqueSize() << endl;
	cout << "ms1 size: " << ms1.size() << endl << endl;

	cout << "--------ms2---------" << endl;;
	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;


	cout << " ---------------------erase all test----------------" << endl;

	cout << " erase all 30, 350 , and 450 from ms2 " << endl;
	cout << ms2.eraseAll(30);
	cout << ms2.eraseAll(350);
	cout << ms2.eraseAll(450);
	cout << ms2.eraseAll(450);
	cout << endl;
	cout << "--------ms2---------" << endl;;
	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;

	ms2.erase(60);
	ms2.erase(60);
	ms2.erase(5);
	ms2.erase(5);
	cout << "--------ms2---------" << endl;;
	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;

	ms1.insert(50);
	ms1.insert(20);
	ms1.insert(20);
	ms1.insert(150);
	ms1.insert(250);
	ms1.insert(350);
	ms1.insert(450);


	ms2.insert(30);
	ms2.insert(60);
	ms2.insert(30);
	ms2.insert(30);
	ms2.insert(350);
	ms2.insert(29);
	ms2.insert(29);
	ms2.insert(5);
	ms2.insert(5);
	ms2.insert(350);
	ms2.insert(350);
	ms2.insert(350);
	ms2.insert(450);
	ms2.insert(350);
	ms2.insert(450);
	ms2.insert(450);
	ms2.insert(450);

	cout << endl << "--------ms1---------" << endl;;
	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType value;
		ms1.get(i, value);
		cout << value << " count#: " << ms1.count(value) << endl;
	}
	cout << "ms1 unique size: " << ms1.uniqueSize() << endl;
	cout << "ms1 size: " << ms1.size() << endl << endl;
	cout << "ms1: smallest value is " << ms1.getSmallestValue(value);
	cout << " and value is " << value << endl;
	cout << "ms1: second smallest value is " << ms1.getSecondSmallestValue(value);
	cout << " and value is " << value << endl;

	cout << "--------ms2---------" << endl;;
	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;
	cout << "ms2: smallest value is " << ms2.getSmallestValue(value);
	cout << " and value is " << value << endl;
	cout << "ms2: second smallest value is " << ms2.getSecondSmallestValue(value);
	cout << " and value is " << value << endl;

	cout << "--------------- replace test----------------- " << endl;
	ms2.replace(350, 351);
	cout << endl << " replace 350 with 351" << endl;
	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;
	cout << "ms2: smallest value is " << ms2.getSmallestValue(value);
	cout << " and value is " << value << endl;
	cout << "ms2: second smallest value is " << ms2.getSecondSmallestValue(value);
	cout << " and value is " << value << endl;


	cout << "replace 30 with 5" << endl;
	ms2.replace(30, 5);

	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;
	cout << "ms2: smallest value is " << ms2.getSmallestValue(value);
	cout << " and value is " << value << endl;
	cout << "ms2: second smallest value is " << ms2.getSecondSmallestValue(value);
	cout << " and value is " << value << endl;

	cout << "past test13 " << endl;
	cin.ignore();



}

void test14()
{
	Multiset ms1, ms2;
	ItemType value = 0;


	ms1.insert(50);
	ms1.insert(150);
	ms1.insert(250);
	ms1.insert(350);
	ms1.insert(450);

	ms2.insert(30);
	ms2.insert(60);
	ms2.insert(30);
	ms2.insert(30);
	ms2.insert(350);
	ms2.insert(350);
	ms2.insert(350);
	ms2.insert(350);
	ms2.insert(450);
	ms2.insert(350);
	ms2.insert(450);
	ms2.insert(450);
	ms2.insert(450);

	cout << endl << "--------ms1---------" << endl;;
	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType value;
		ms1.get(i, value);
		cout << value << " count#: " << ms1.count(value) << endl;
	}
	cout << "amount greater than 150: " << ms1.countIf('>', 150) << endl;
	cout << "amount less than 150: " << ms1.countIf('<', 150) << endl;
	cout << "amount equal 150: " << ms1.countIf('=', 150) << endl;
	cout << "ms1 unique size: " << ms1.uniqueSize() << endl;
	cout << "ms1 size: " << ms1.size() << endl << endl;
	cout << "--------ms2---------" << endl;;
	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;

	cout << "ms1: least frequent value is " << ms1.getLeastFrequentValue(value);
	cout << " and value is " << value << endl;
	cout << "ms2: least frequent value is " << ms2.getLeastFrequentValue(value);
	cout << " and value is " << value << endl;

	cout << "ms1: smallest value is " << ms1.getSmallestValue(value);
	cout << " and value is " << value << endl;
	cout << "ms2: smallest value is " << ms2.getSmallestValue(value);
	cout << " and value is " << value << endl;

	cout << "ms1: second smallest value is " << ms1.getSecondSmallestValue(value);
	cout << " and value is " << value << endl;
	cout << "ms2: second smallest value is " << ms2.getSecondSmallestValue(value);
	cout << " and value is " << value << endl;

	cout << "---------copyintOtherMultiset ms1 into ms2---------" << endl;
	ms1.copyIntoOtherMultiset(ms2);
	cout << "--------ms2---------" << endl;;
	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}
	cout << "amount greater than 150 in ms2: " << ms2.countIf('>', 150) << endl;
	cout << "amount less than 150 in ms2: " << ms2.countIf('<', 150) << endl;
	cout << "amount equal 150 in ms2: " << ms2.countIf('=', 150) << endl;
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;
	cout << "ms2: smallest value is " << ms2.getSmallestValue(value);
	cout << " and value is " << value << endl;
	cout << "ms2: second smallest value is " << ms2.getSecondSmallestValue(value);
	cout << " and value is " << value << endl;

	cout << "past test14" << endl;
	cin.ignore();
}

void test15()
{
	Multiset ms1, ms2;
	ItemType value1 = 0;
	for (int i = 0; i < 150; i++)
	{
		ms1.insert(value1);
		value1++;
	}
	for (int i = 0; i < 100; i++)
	{
		ms2.insert(value1);
		value1++;
	}

	ItemType value = 0;

	cout << endl << "--------ms1---------" << endl;;
	for (int i = 0; i < ms1.uniqueSize(); i++)
	{
		ItemType value;
		ms1.get(i, value);
		cout << value << " count#: " << ms1.count(value) << " ";
		if (i % 10 == 0)
		{
			cout << endl;
		}

	}
	cout << endl << "ms1 unique size: " << ms1.uniqueSize() << endl;
	cout << "ms1 size: " << ms1.size() << endl << endl;
	cout << "--------ms2---------" << endl;;
	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << " ";
		if (i % 10 == 0)
		{
			cout << endl;
		}
	}
	cout << endl << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;

	cout << "---------copyintOtherMultiset ms1 into ms2---------" << endl;
	ms1.copyIntoOtherMultiset(ms2);
	cout << "--------ms2---------" << endl;;
	for (int i = 0; i < ms2.uniqueSize(); i++)
	{
		ItemType value;
		ms2.get(i, value);
		cout << value << " count#: " << ms2.count(value) << endl;
	}

	cout << "amount greater than 150 in ms2: " << ms2.countIf('>', 150) << endl;
	cout << "amount less than 150 in ms2: " << ms2.countIf('<', 150) << endl;
	cout << "amount equal 150 in ms2: " << ms2.countIf('=', 150) << endl;
	cout << "ms2 unique size: " << ms2.uniqueSize() << endl;
	cout << "ms2 size: " << ms2.size() << endl << endl;
	cout << "ms2: smallest value is " << ms2.getSmallestValue(value);
	cout << " and value is " << value << endl;
	cout << "ms2: second smallest value is " << ms2.getSecondSmallestValue(value);
	cout << " and value is " << value << endl;
	cout << "past test15" << endl;
	cin.ignore();


}

int main()
{
	/*
	test1();
	test2();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();
	*/
	
	
	test3();
	test11();
	test12();
	test13();
	test14();
	test15();
	

	
}
