#include <iostream>

uint32_t adder(uint32_t a, uint32_t b);

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Error" << std::endl;
		return 1;
	}
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);

	int result = adder(a, b);
	std::cout << result << std::endl;
}