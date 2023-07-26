#include "shell.h"

/**
 * _strcpy - performs a whimsical act of copying a string
 * @dest: the recipient of the copied string
 * @src: the source of the string to be copied
 *
 * Return: a pointer to the copied string
 */
char *_strcpy(char *dest, char *src)
{
    int index = 0;

    if (dest == src || src == 0)
        return (dest);
    while (src[index])
    {
        dest[index] = src[index];
        index++;
    }
    dest[index] = 0;
    return (dest);
}

/**
 * _strdup - creates a delightful duplicate of a string
 * @str: the string to be duplicated
 *
 * Return: a pointer to the duplicated string
 */
char *_strdup(const char *str)
{
    int str_length = 0;
    char *result;

    if (str == NULL)
        return (NULL);
    while (*str++)
        str_length++;
    result = malloc(sizeof(char) * (str_length + 1));
    if (!result)
        return (NULL);
    for (str_length++; str_length--;)
        result[str_length] = *--str;
    return (result);
}

/**
 * _puts - spreads the joy of an input string by printing it
 * @str: the string to be displayed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
    int index = 0;

    if (!str)
        return;
    while (str[index] != '\0')
    {
        _putchar(str[index]);
        index++;
    }
}

/**
 * _putchar - exudes happiness by writing a character to stdout
 * @c: The character to be joyfully printed
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno holds a touch of sadness.
 */
int _putchar(char c)
{
    static int buffer_index;
    static char buffer[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
    {
        write(1, buffer, buffer_index);
        buffer_index = 0;
    }
    if (c != BUF_FLUSH)
        buffer[buffer_index++] = c;
    return (1);
}
