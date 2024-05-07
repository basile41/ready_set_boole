#include <iostream>
#include <string>
#include <bitset>
#include <stdio.h>

std::string negation_normal_form(const std::string &formula);

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error" << std::endl;
		return 1;
	}

	std::string formula(argv[1]);
	std::string nnf_rpn = negation_normal_form(formula);
	std::cout << nnf_rpn << std::endl;
}
