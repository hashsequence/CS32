#include "StudentMultiset.h"
#include <iostream>

using namespace std;

void test01()
{
	StudentMultiset ms3, ms4;


	ms3.add(123456789);
	ms3.add(484799950);
	ms3.add(123456789); 
	ms3.add(123456789);
	ms3.add(123456789); 
	ms3.add(123456789);
	ms3.add(235252523);
	ms3.add(235252523); 
	ms3.add(235252523);

	ms3.print();
	ms4.print();
	cout << "ms3 size: " << ms3.size() << endl;
	cout << "ms4 size: " << ms4.size() << endl;

}

int main()
{
	test01();
}

