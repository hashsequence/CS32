	void removeBad(list<Movie*>& li)
	{
		std::list<Movie*>::iterator it = li.begin();
		while (it != li.end())
		{
			if ((*it)->rating() < 50) // a iterator pointer to a list of pointer must be first dereferenced
			{
				delete *it; // since the iterator is a double pointer you must delete the pointer that the it is pointing to
				it = li.erase(it);
			}
			else
				it++;
		}

	}

