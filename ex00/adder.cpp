#include <cstdint>

uint32_t adder(uint32_t a, uint32_t b)
{
	uint32_t carry;

	while (b)
	{
		carry = a & b;
		a = a ^ b;
		b = carry << 1;
	}
	return (a);
}
