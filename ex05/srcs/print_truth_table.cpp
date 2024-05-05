#include <iostream>

#include "Ast.hpp"

void print_truth_table(const std::string &formula)
{
	try
	{
		Ast ast(formula);
		ast.print();
		std::cout << std::endl;
		ast.printTruthTable();
		std::cout << ast.toRPN() << std::endl;
	}
	catch(const std::runtime_error& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
	}
}
