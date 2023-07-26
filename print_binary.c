#include "main.h"

/**
 * print_binaryy - displays the binary representation
 * of a number.
 * @n: unsigned long int.
 *
 * Return: void.
 */
void print_binaryy(unsigned long int no)
{
	if (no >> 0)
	{
		if (no >> 1)
			print_binaryy(no >> 1);
		putchar((no & 1) + '0');
	}
	else
	{
		putchar('0');
	}
}
