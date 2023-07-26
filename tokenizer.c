#include "shell.h"

/**
 * **strtow - performs the magical act of splitting a string into words.
 * @str: the input string to be enchanted
 * @d: the delimiter string that guides the magic spell
 * Return: a pointer to an array of enchanted strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
    int index1, index2, index3, index4, word_count = 0;
    char **result;

    if (str == NULL || str[0] == 0)
        return (NULL);
    if (!d)
        d = " ";
    for (index1 = 0; str[index1] != '\0'; index1++)
        if (!is_delim(str[index1], d) && (is_delim(str[index1 + 1], d) || !str[index1 + 1]))
            word_count++;

    if (word_count == 0)
        return (NULL);
    result = malloc((1 + word_count) * sizeof(char *));
    if (!result)
        return (NULL);
    for (index1 = 0, index2 = 0; index2 < word_count; index2++)
    {
        while (is_delim(str[index1], d))
            index1++;
        index3 = 0;
        while (!is_delim(str[index1 + index3], d) && str[index1 + index3])
            index3++;
        result[index2] = malloc((index3 + 1) * sizeof(char));
        if (!result[index2])
        {
            for (index3 = 0; index3 < index2; index3++)
                free(result[index3]);
            free(result);
            return (NULL);
        }
        for (index4 = 0; index4 < index3; index4++)
            result[index2][index4] = str[index1++];
        result[index2][index4] = 0;
    }
    result[index2] = NULL;
    return (result);
}

/**
 * **strtow2 - performs another form of enchantment by splitting a string into words
 * @str: the input string to be enchanted
 * @d: the magical delimiter that guides the spell
 * Return: a pointer to an array of enchanted strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
    int index1, index2, index3, index4, word_count = 0;
    char **result;

    if (str == NULL || str[0] == 0)
        return (NULL);
    for (index1 = 0; str[index1] != '\0'; index1++)
        if ((str[index1] != d && str[index1 + 1] == d) ||
            (str[index1] != d && !str[index1 + 1]) || str[index1 + 1] == d)
            word_count++;
    if (word_count == 0)
        return (NULL);
    result = malloc((1 + word_count) * sizeof(char *));
    if (!result)
        return (NULL);
    for (index1 = 0, index2 = 0; index2 < word_count; index2++)
    {
        while (str[index1] == d && str[index1] != d)
            index1++;
        index3 = 0;
        while (str[index1 + index3] != d && str[index1 + index3] && str[index1 + index3] != d)
            index3++;
        result[index2] = malloc((index3 + 1) * sizeof(char));
        if (!result[index2])
        {
            for (index3 = 0; index3 < index2; index3++)
                free(result[index3]);
            free(result);
            return (NULL);
        }
        for (index4 = 0; index4 < index3; index4++)
            result[index2][index4] = str[index1++];
        result[index2][index4] = 0;
    }
    result[index2] = NULL;
    return (result);
}
