#include "holberton.h"
/**
 * _strlenn - Sizes the length of a string
 * @string: String to be sized
 * Return: The length ot the string
 */

int _strlenn(const char *string)
{
	int length = 0;

	if (string == NULL)
		return (0);

	while (string[length] != '\0')
		length++;
	return (length);
}
