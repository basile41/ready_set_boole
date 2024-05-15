#include <iostream>

#include "Ast.hpp"

std::string negation_normal_form(const std::string &formula)
{
	try
	{
		Ast ast(formula);
		// ast.print();
		// std::cout << std::endl;
		// ast.printTruthTable();
		return ast.toRPN();
	}
	catch(const std::runtime_error& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
	}
	return "";
}
