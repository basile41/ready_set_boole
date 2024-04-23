#include <iostream>

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
