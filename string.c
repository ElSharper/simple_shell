#include "shell.h"

/**
 * _strlen - computes the length of a string
 * @s: the string to measure
 *
 * Return: the length of the string
 */
int _strlen(char *s)
{
	int length = 0;

	if (!s)
		return (0);

	while (*s++)
		length++;
	return (length);
}

/**
 * _strcmp - compares two strings lexicographically
 * @s1: the first string
 * @s2: the second string
 *
 * Return: a negative value if s1 is alphabetically before s2.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if haystack starts with needle
 * @haystack: the string to search in
 * @needle: the substring to find
 *
 * Return: a pointer to the next character in haystack if needle is found.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination string
 * @src: the source string
 *
 * Return: a pointer to the destination string
 */
char *_strcat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (result);
}
