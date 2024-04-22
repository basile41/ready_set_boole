#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <functional>

bool negation(bool a) // not
{
	return !a;
}

bool conjunction(bool a, bool b) // and
{
	return a && b;
}

bool disjunction(bool a, bool b) // or
{
	return a || b;
}

bool exclusive_disjunction(bool a, bool b) // xor
{
	return a != b;
}

bool material_condition(bool a, bool b) // implies
{
	return !a || b;
}

bool logical_equivalence(bool a, bool b) // if and only if
{
	return a == b;
}

bool check_and_pop(std::stack<char> &s)
{
	if (s.empty())
		throw std::runtime_error("Invalid formula");
	char a = s.top();
	s.pop();
	return a;
}

// bool eval_formula(const std::string &formula)
// {
// 	const std::map<char, std::function<bool(bool, bool)>> operators = {
// 		{'&', conjunction},
// 		{'|', disjunction},
// 		{'^', exclusive_disjunction},
// 		{'>', material_condition},
// 		{'=', logical_equivalence}
// 	};
// 	std::stack<char> s;

// 	try
// 	{
// 		for (char c: formula)
// 		{
// 			if (c == ' ')
// 				continue;
// 			if (c == '0' || c == '1')
// 				s.push(c - '0');
// 			else if (c == '!')
// 			{
// 				char a = check_and_pop(s);
// 				s.push(negation(a));
// 			}
// 			else
// 			{
// 				auto it = operators.find(c);
// 				if (it != operators.end())
// 				{
// 					bool b = check_and_pop(s);
// 					bool a = check_and_pop(s);
// 					s.push(it->second(a, b));

// 				}
// 				else
// 					throw std::runtime_error("Invalid character in formula");
// 			}
// 		}
// 		return s.top();
// 	}
// 	catch(const std::exception& e)
// 	{
// 		std::cerr << e.what() << '\n';
// 	}
	
// 	return false;
// }

#include "Ast.hpp"

bool eval_formula(const std::string &formula)
{
	try
	{
		Ast ast(formula);
		ast.print();
		return ast.eval();
	}
	catch(const std::runtime_error& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
	}
	return false;
}