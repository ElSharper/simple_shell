#include "shell.h"

/**
 * _strncpy - Copies a string.
 * @dest: The destination string to copy to.
 * @src: The source string.
 * @n: The number of characters to copy.
 * Return: A pointer to the destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int index_dest = 0, index_src = 0;
	char *result = dest;

	while (src[index_src] != '\0' && index_dest < n - 1)
	{
		dest[index_dest] = src[index_src];
		index_dest++;
		index_src++;
	}
	if (index_dest < n)
	{
		int j = index_dest;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 * _strncat - Concatenates two strings.
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of bytes to use.
 * Return: A pointer to the concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int index_dest = 0, index_src = 0;
	char *result = dest;

	while (dest[index_dest] != '\0')
		index_dest++;
	while (src[index_src] != '\0' && index_src < n)
	{
		dest[index_dest] = src[index_src];
		index_dest++;
		index_src++;
	}
	if (index_src < n)
		dest[index_dest] = '\0';
	return (result);
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to search.
 * @c: The character to find.
 * Return: A pointer to the first occurrence of the character in the string.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
