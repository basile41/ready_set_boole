#include <iostream>
#include <string>
#include <bitset>
#include <stdio.h>

bool print_truth_table(const std::string &formula);

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error" << std::endl;
		return 1;
	}

	std::string formula(argv[1]);
	bool result = print_truth_table(formula);
	std::cout << "\nresult :" << result << std::endl;
}
