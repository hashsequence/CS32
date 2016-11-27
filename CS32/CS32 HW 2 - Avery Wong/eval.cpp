#include <iostream>
#include <string>
#include <cassert>
#include <stack>

using namespace std;
//! > & > |

int evaluate(string infix, string& postfix, bool& result)
{
	//converts infix to postfix & check if the infix expression is valid
	bool flag = 0;
	char previous = ' ';
	postfix = "";
	stack<char> operator_stack;
	if (infix.size() == 0)
	{
		return 1;
	}
	for (int k = 0; k < static_cast<int>(infix.size()); k++)
	{
		if (infix[k] != 'T' && infix[k] != 'F' && infix[k] != '(' && infix[k] != ')' && infix[k] != '&' && infix[k] != '|' && infix[k] != '!' && infix[k] != ' ')
		{
			flag = 1;
		}
	}
	for (int k = 0; k < static_cast<int>(infix.size()); k++)
	{
		switch (infix[k])
		{
		case 'T':
		case 'F':
			postfix += infix[k];
			if (k >= 1)
			{
				if (previous == 'F' || previous == 'T' || previous == ')')
				{
					flag = 1;
				}
			}
			previous = infix[k];
			break;
		case '(':
			operator_stack.push(infix[k]);
			if (operator_stack.top() != '(')
			{
				flag = 1;
			}
			if (k >= 1)
			{
				if (previous == ')' || previous == 'T' || previous == 'F')
				{
					flag = 1;
				}
			}
			previous = infix[k];
			break;
		case ')':
			while (operator_stack.top() != '(')
			{
				postfix += operator_stack.top();
				operator_stack.pop();
			}
			operator_stack.pop();
			if (k >= 1)
			{
				if (previous == '(')
				{
					flag = 1;	
				}
			}
			previous = infix[k];
			break;
		case '&':
		case '|':
		case '!':
			while (operator_stack.empty() == false && operator_stack.top() != '(' && infix[k] >= operator_stack.top())
			{
				postfix += operator_stack.top();
				operator_stack.pop();
			}
			operator_stack.push(infix[k]);
			if (infix[k] == '|' || infix[k] == '&')
			{
				if (previous == '!' || previous == '&' || previous == '!')
				{
					flag = 1;
				}
			}
			if (infix[k] == '!')
			{
				if (previous == 'F' || previous == 'T' || previous == ')')
				{
					flag = 1;
				}
			}
			previous = infix[k];
			break;
		default:
			break;
		}
		
	}

		while (operator_stack.empty() == false)
		{
			postfix += operator_stack.top();
			operator_stack.pop();
		}
		if (previous == '(' || previous == '|' || previous == '!' || previous == '&'|| infix[0] == '|' || infix[0] == '&' || infix[0] == ')')
		{
			flag = 1;
		}
		int c1 = 0;
		int c2 = 0;
		for (int k = 0; k < static_cast<int>(infix.size()); k++)
		{
			if (infix[k] == '(')
				c1++;
			if (infix[k] == ')')
				c2++;
		}
		if (c1 != c2)
		{
			flag = 1;
		}
		if (flag == 1)
			return 1;

		//evaluating postfix expression
		stack<bool> operand_stack;
		for (int k = 0; k < static_cast<int>(postfix.size()); k++)
		{
			if (postfix[k] == 'T' || postfix[k] == 'F')
			{
				if (postfix[k] == 'T')
					operand_stack.push(true);
				if (postfix[k] == 'F')
					operand_stack.push(false);
			}
			else if (postfix[k] == '&' || postfix[k] == '|')
			{
				bool expression = 0;
				bool operand2 = 0, operand1 = 0;
				if (operand_stack.top() == true)
					operand2 = true;
				else if (operand_stack.top() == false)
					operand1 = false;
				operand_stack.pop();
				if (operand_stack.top() == true)
					operand2 = true;
				else if (operand_stack.top() == false)
					operand1 = false;
				operand_stack.pop();

				if (postfix[k] == '&')
				{
					expression = (operand1)& (operand2);
					operand_stack.push(expression);
				}
				if (postfix[k] == '|')
				{
					expression = (operand1) | (operand2);
					operand_stack.push(expression);
				}
			}
			else if (postfix[k] == '!')
			{
				bool expression = operand_stack.top();
				operand_stack.pop();
				expression = !expression;
				operand_stack.push(expression);
			}
		}
		result = operand_stack.top();
		return 0;
	

}


int main()
{
	string pf;
	bool answer;
	assert(evaluate("T| F", pf, answer) == 0 && pf == "TF|"  &&  answer);
	assert(evaluate("T|", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("T(F|T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F|F)", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&|"  &&  !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F"  &&  !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T"  &&  answer);

	assert(evaluate("T&!(F|T&T|F)|!!!(F&T&F)", pf, answer) == 0 && answer);
	cout << "Passed all tests" << endl;
}
