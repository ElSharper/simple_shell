#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Pointer to the structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - retrieves the value of an environment variable
 * @info: Pointer to the structure containing potential arguments.
 * @name: name of the environment variable to retrieve.
 *
 * Return: value of the environment variable.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node_iter = info->env;
	char *env_val;

	while (node_iter)
	{
		env_val = starts_with(node_iter->str, name);
		if (env_val && *env_val)
			return (env_val);
		node_iter = node_iter->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initializes a new environment variable
 *             or modifies an existing one
 * @info: Pointer to the structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Removes an environment variable
 * @info: Pointer to the structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _myunsetenv(info_t *info)
{
	int idx;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (idx = 1; idx <= info->argc; idx++)
		_unsetenv(info, info->argv[idx]);

	return (0);
}

/**
 * populate_env_list - populates environment linked list
 * @info: Pointer to the structure containing potential arguments.
 *
 * Return: Always 0.
 */
int populate_env_list(info_t *info)
{
	list_t *temp_node = NULL;
	size_t idx;

	for (idx = 0; environ[idx]; idx++)
		add_node_end(&temp_node, environ[idx], 0);
	info->env = temp_node;
	return (0);
}
