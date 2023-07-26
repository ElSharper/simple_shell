#include "shell.h"

/**
 * _erratoi - transforms a string to an integer
 * @s: the string that needs to be transformed
 * Return: 0 if there are no numbers in the string, converted number otherwise
 *       -1 in case of error
 */
int _erratoi(char *s)
{
	int j = 0;
	unsigned long int solut = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (j = 0;  s[j] != '\0'; j++)
	{
		if (s[j] >= '0' && s[j] <= '9')
		{
			solut *= 10;
			solut += (s[j] - '0');
			if (solut > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (solut);
}

/**
 * print_error - outputs an error message
 * @info: the struct for input parameters & return
 * @estr: string that indicates the type of error
 * Return: 0 if there are no numbers in the string, converted number otherwise
 *        -1 in case of error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - this function prints a base 10 integer
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, counter = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		counter++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			counter++;
		}
		current %= j;
	}
	__putchar('0' + current);
	counter++;

	return (counter);
}

/**
 * convert_number - conversion function, similar to itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - replaces the first occurrence of '#' with '\0' in a string
 * @buf: the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}
