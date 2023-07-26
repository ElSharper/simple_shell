#include "main.h"

/**
 * flip_bits - number bit returns
 * pass from number to another
 * @n: the first.
 * @m: the second.
 *
 * Return: bits.
 */
unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	unsigned int number;

	for (number = 0; n || m; n >>= 1, m >>= 1)
	{
		if ((n & 1) != (m & 1))
			number++;
	}

	return (number);
}
