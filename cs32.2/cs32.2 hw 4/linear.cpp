
bool anyUppercase(const char a[], int n)
{
	if (n < 1)
		return false;
	if (isupper(a[n - 1]))
		return true;
	else
		return anyUppercase(a, n - 1);
}

int countUppercase(const char a[], int n)
{
	if (n < 1)
		return 0;
	if (isupper(a[n - 1]))
		return countUppercase(a, n - 1) + 1;
	else
		return countUppercase(a, n - 1);
}


int firstUppercase(const char a[], int n)
{
	if (n == 0)
		return -1;
	int index = 1 + firstUppercase(a + 1, n - 1);
	if (isupper(a[0]))
		return 0;
	if (index != 0)
		return index;
	else
		return -1;
}

int indexOfLeast(const char a[], int n)
{
	if (n == 0)
		return -1;
	if (n == 1)
		return 0;
	int index = 1 + indexOfLeast(a + 1, n - 1);
	if (a[0] > a[index])
		return index;
	else
		return 0;
}


