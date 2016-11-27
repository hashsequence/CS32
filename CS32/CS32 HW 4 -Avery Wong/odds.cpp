void removeOdds(vector<int>& v)
{
	std::vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		if (*it % 2 == 1)
		{
			it = v.erase(it);
		}
		else
			it++;
	}
}

