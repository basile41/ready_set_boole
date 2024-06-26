#include <iostream>
#include <bitset>
#include <stdio.h>

uint32_t gray_code(uint32_t n);

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error" << std::endl;
		return 1;
	}
	int n = atoi(argv[1]);

	int result = gray_code(n);

	std::cout << "n = " << n << std::endl;
	printf("%b\n\n", n);

	std::cout << "gray = " << result << std::endl;
	printf("%b\n", result);
}