#include "shell.h"

/**
 * strtow - Performs the magical act of splitting a string into words.
 * @str: The input string to be enchanted.
 * @d: The delimiter string that guides the magic spell.
 *
 * Return: A pointer to an array of enchanted strings, or NULL on failure.
 */
char **strtow(char *str, char *d)
{
	int i1, i2, i3, i4, w_count = 0;
	char **result;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!d)
		d = " ";

	for (i1 = 0; str[i1] != '\0'; i1++)
		if (!is_delim(str[i1], d) && (is_delim(str[i1 + 1], d) || !str[i1 + 1]))
			w_count++;

	if (w_count == 0)
		return (NULL);

	result = malloc((1 + w_count) * sizeof(char *));
	if (!result)
		return (NULL);

	for (i1 = 0, i2 = 0; i2 < w_count; i2++)
	{
		while (is_delim(str[i1], d))
			i1++;

		i3 = 0;
		while (!is_delim(str[i1 + i3], d) && str[i1 + i3])
			i3++;

		result[i2] = malloc((i3 + 1) * sizeof(char));
		if (!result[i2])
		{
			for (i3 = 0; i3 < i2; i3++)
				free(result[i3]);
			free(result);
			return (NULL);
		}

		for (i4 = 0; i4 < i3; i4++)
			result[i2][i4] = str[i1++];

		result[i2][i4] = '\0';
	}

	result[i2] = NULL;
	return (result);
}

/**
 * strtow2 - Performs another form of enchantment by splitting a string into words.
 * @str: The input string to be enchanted.
 * @d: The magical delimiter that guides the spell.
 *
 * Return: A pointer to an array of enchanted strings, or NULL on failure.
 */
char **strtow2(char *str, char d)
{
	int i1, i2, i3, i4, w_count = 0;
	char **result;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	for (i1 = 0; str[i1] != '\0'; i1++)
		if ((str[i1] != d && str[i1 + 1] == d) ||
			(str[i1] != d && !str[i1 + 1]) || str[i1 + 1] == d)
			w_count++;

	if (w_count == 0)
		return (NULL);

	result = malloc((1 + w_count) * sizeof(char *));
	if (!result)
		return (NULL);

	for (i1 = 0, i2 = 0; i2 < w_count; i2++)
	{
		while (str[i1] == d && str[i1] != d)
			i1++;

		i3 = 0;
		while (str[i1 + i3] != d && str[i1 + i3] && str[i1 + i3] != d)
			i3++;

		result[i2] = malloc((i3 + 1) * sizeof(char));
		if (!result[i2])
		{
			for (i3 = 0; i3 < i2; i3++)
				free(result[i3]);
			free(result);
			return (NULL);
		}

		for (i4 = 0; i4 < i3; i4++)
			result[i2][i4] = str[i1++];

		result[i2][i4] = '\0';
	}

	result[i2] = NULL;
	return (result);
}
