#include "shell.h"

/**
 * is_chain - Performs a mystical test to determine if the current character in the buffer is a chain delimiter.
 * @info: The magical parameter struct.
 * @buf: The enchanted char buffer.
 * @p: Address of the current position in buf.
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR; /* Casting a magical spell: Command is OR type */
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND; /* Casting a magical spell: Command is AND type */
	}
	else if (buf[j] == ';') /* Found the end of this command, it's a magical semicolon */
	{
		buf[j] = 0; /* Replace the semicolon with a null, as per the ancient script */
		info->cmd_buf_type = CMD_CHAIN; /* Casting a magical spell: Command is CHAIN type */
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - Performs a mystical check to determine if we should continue chaining based on the last status.
 * @info: The magical parameter struct.
 * @buf: The enchanted char buffer.
 * @p: Address of the current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 *
 * Return: Void.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0; /* Break the chain, the status is not favorable */
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0; /* Break the chain, the status is favorable */
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - Performs a mystical replacement of aliases in the tokenized string.
 * @info: The magical parameter struct.
 *
 * Return: 1 if aliases replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Performs a mystical replacement of variables in the tokenized string.
 * @info: The magical parameter struct.
 *
 * Return: 1 if variables replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0))); /* Casting a mystical conversion spell */
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0))); /* Casting a mystical conversion spell */
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1)); /* Casting a mystical replacement spell */
			continue;
		}
		replace_string(&info->argv[i], _strdup("")); /* Casting a mystical replacement spell */

	}
	return (0);
}

/**
 * replace_string - Performs a mystical replacement of strings.
 * @old: Address of the old string.
 * @new: New string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
