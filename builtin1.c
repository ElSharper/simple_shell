#include "shell.h"

/**
 * _myhistory - Prints the history of commands executed, one command per line,
 *              starting with line numbers from 0.
 * @info: A pointer to a structure containing command arguments and other variables.
 *
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Removes the specified alias from the alias list.
 * @info: A pointer to a structure containing command arguments and other variables.
 * @str: The alias string to be removed.
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *temp_str, ch;
	int retval;

	temp_str = _strchr(str, '=');
	if (!temp_str)
		return (1);
	ch = *temp_str;
	*temp_str = 0;
	retval = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*temp_str = ch;
	return (retval);
}

/**
 * set_alias - Sets an alias to a string.
 * @info: A pointer to a structure containing command arguments and other variables.
 * @str: The alias string to be set.
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *temp_str;

	temp_str = _strchr(str, '=');
	if (!temp_str)
		return (1);
	if (!*++temp_str)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints a specified alias string.
 * @node: The alias node to be printed.
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *temp_pointer = NULL, *alias_pointer = NULL;

	if (node)
	{
		temp_pointer = _strchr(node->str, '=');
		for (alias_pointer = node->str; alias_pointer <= temp_pointer; alias_pointer++)
			_putchar(*alias_pointer);
		_putchar('\'');
		_puts(temp_pointer + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Mimics the behavior of the alias builtin command (see 'man alias').
 * @info: A pointer to a structure containing command arguments and other variables.
 *
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int counter = 0;
	char *temp_pointer = NULL;
	list_t *node_pointer = NULL;

	if (info->argc == 1)
	{
		node_pointer = info->alias;
		while (node_pointer)
		{
			print_alias(node_pointer);
			node_pointer = node_pointer->next;
		}
		return (0);
	}
	for (counter = 1; info->argv[counter]; counter++)
	{
		temp_pointer = _strchr(info->argv[counter], '=');
		if (temp_pointer)
			set_alias(info, info->argv[counter]);
		else
			print_alias(node_starts_with(info->alias, info->argv[counter], '='));
	}

	return (0);
}
