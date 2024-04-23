#include <iostream>

#include "Ast.hpp"

bool print_truth_table(const std::string &formula)
{
	try
	{
		Ast ast(formula);
		ast.print();
		ast.printTruthTable();

		return ast.eval();
	}
	catch(const std::runtime_error& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
	}
	return false;
}
