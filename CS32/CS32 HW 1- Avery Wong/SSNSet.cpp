#include "SSNSet.h"
#include <iostream>

SSNSet::SSNSet() : m_SSN()
{

}

bool SSNSet::add(unsigned long ssn)
{

	if (m_SSN.insert(ssn) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}
// Add an SSN to the SSNSet.  Return true if and only if the SSN
// was actually added.

int SSNSet::size() const
{
	return m_SSN.size();
}

void SSNSet::print() const
{
	ItemType value;
	for (int k = 0; k < size(); k++)
	{
		m_SSN.get(k, value);
		std::cout << value << std::endl;
	}
}
// Write every SSN in the SSNSet to cout exactly once, one per
// line.  Write no other text.
