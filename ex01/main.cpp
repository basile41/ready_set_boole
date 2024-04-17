#include <iostream>

uint32_t multiplier(uint32_t a, uint32_t b);

int main(int argc, char **argv)
{
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);

	int result = multiplier(a, b);
	std::cout << result << std::endl;
	std::cout << a * b << std::endl;
}