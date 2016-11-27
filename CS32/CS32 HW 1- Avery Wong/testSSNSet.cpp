
#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
#include "SSNSet.h"
using namespace std;

int main()
{
	SSNSet S;
	S.add(123456789);
	S.add(985673340);
	S.add(198763536);
	cout << S.size() << endl;
	S.print();
	SSNSet S2;

	S2 = S;
	cout << S2.size() << endl;
	S2.print();

}
