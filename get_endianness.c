#include "main.h"

/**
 * get_endianness - checker for the end
 *
 * Return: 0 for big , 1 for little.
 */
int get_endianness(void)
{
	unsigned int a;
	char *b;

	a = 1;
	b = (char *) &a;

	return ((int)*b);
}
