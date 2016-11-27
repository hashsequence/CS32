
int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
	if (n2 == 0)
		return 1;
	if (n1 < n2)
		return 0;
	int k = 0;
	if (a1[0] == a2[0])
		k += countIncludes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);

		k += countIncludes(a1 + 1, n1 - 1, a2, n2);
	return k;	
}

void exchange(string& x, string& y)
{
	string t = x;
	x = y;
	y = t;
}

void divide(string a[], int n, string divider, int& firstNotLess, int& firstGreater)
{
	if (n < 0)
		n = 0;

	// It will always be the case that just before evaluating the loop
	// condition:
	//  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
	//  Every element earlier than position firstNotLess is < divider
	//  Every element from position firstNotLess to firstUnknown-1 is
	//    == divider
	//  Every element from firstUnknown to firstGreater-1 is not known yet
	//  Every element at position firstGreater or later is > divider

	firstNotLess = 0;
	firstGreater = n;
	int firstUnknown = 0;
	while (firstUnknown < firstGreater)
	{
		if (a[firstUnknown] > divider)
		{
			firstGreater--;
			exchange(a[firstUnknown], a[firstGreater]);
		}
		else
		{
			if (a[firstUnknown] < divider)
			{
				exchange(a[firstNotLess], a[firstUnknown]);
				firstNotLess++;
			}
			firstUnknown++;
		}
	}
}

void order(string a[], int n)
{
	if (n <= 1)
	{

	}
	else
	{
		int b = 0;
		int c = 0;
		divide(a, n, a[(n)/2], b, c);
		order(a, b);
		order(a + c, n-c);
	}
}
