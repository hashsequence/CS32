void listAll(string path, const File* f)  // two-parameter overload
{
	//You will write this code.
	const vector<File*>* c = f->files();
	if (c == NULL) // if the file isn't a directory
	{
		cout << path << "/" << f->name() << endl;
	}

	else //if f points to a directory
	{
		path += "/" + f->name();	//add the name of the directory to the path string
		cout << path << endl;
		for (vector<File*>::const_iterator it = c->begin(); it != c->end(); it++) //creates an iterator to step through the vector of files in the directory
		{
			listAll(path, *it); //recursively calls the function with the current path
		}
	}
}

