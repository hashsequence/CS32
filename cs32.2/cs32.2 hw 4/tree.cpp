int countIncludes(const char a1[], int n1, const char a2[], int n2)
{
	if (n2 == 0)
		return 1;
	if (n2 > n1)
		return 0;
	int k = 0;
	if (a1[0] == a2[0])
		k += countIncludes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
	k += countIncludes(a1 + 1, n1 - 1, a2, n2);
	return k;
}

