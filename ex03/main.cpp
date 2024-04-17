#include <iostream>
#include <string>
#include <bitset>
#include <stdio.h>

bool eval_formula(const std::string &formula);

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error" << std::endl;
		return 1;
	}
	
	std::string formula(argv[1]);
	bool result = eval_formula(formula);
	std::cout << result << std::endl;
}