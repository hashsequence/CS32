#include <string>
#include <stack>
#include <iostream>

bool balanced(std::string expr)
{
	std::stack<char> m_s;
	for (unsigned int i = 0; i < expr.length(); i++)
	{
		switch (expr[i])
		{
			case '(':
			case '[':
			case '{':
				m_s.push(expr[i]);
				break;
			case ')':
				if (m_s.empty())
					return false;
				if (m_s.top() == '(')
					m_s.pop();
				break;
			case ']':
				if (m_s.empty())
					return false;
				if (m_s.top() == '[')
					m_s.pop();
				break;
			case '}':
				if (m_s.empty())
					return false;
				if (m_s.top() == '{')
					m_s.pop();
				break;
			default:
				break;
		}
	}
	return m_s.empty();
}

