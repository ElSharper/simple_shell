#include "shell.h"

/**
 * _eputs - displays a given string
 * @str: the string to display
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}

/**
 * _eputchar - writes the character c to standard error output
 * @c: The character to write
 *
 * Return: 1 on success.
 * On error, returns -1 and appropriately sets errno.
 */
int _eputchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to a specified file descriptor
 * @c: The character to write
 * @fd: The target file descriptor
 *
 * Return: 1 on success.
 * On error, returns -1 and sets errno appropriately.
 */
int _putfd(char c, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 *_putsfd - outputs a provided string
 * @str: the string to output
 * @fd: the file descriptor to which the string is written
 *
 * Return: the number of characters output
 */
int _putsfd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += _putfd(*str++, fd);
	}
	return (j);
}
