#include "shell.h"

/**
 * get_environ - Returns a copy of the environment variables as a string array.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Pointer to the string array of environment variables.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Deletes an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * @var: The environment variable to remove.
 * Return: 1 if the variable is deleted, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *curr_node = info->env;
	size_t index = 0;
	char *p;

	if (!curr_node || !var)
		return (0);

	while (curr_node)
	{
		p = starts_with(curr_node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			curr_node = info->env;
			continue;
		}
		curr_node = curr_node->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Sets a new environment variable or updates an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The environment variable name.
 * @value: The environment variable value.
 * Return: Always 0.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *new_env_var = NULL;
	list_t *curr_node;
	char *p;

	if (!var || !value)
		return (0);

	new_env_var = malloc(_strlen(var) + _strlen(value) + 2);
	if (!new_env_var)
		return (1);
	_strcpy(new_env_var, var);
	_strcat(new_env_var, "=");
	_strcat(new_env_var, value);
	curr_node = info->env;
	while (curr_node)
	{
		p = starts_with(curr_node->str, var);
		if (p && *p == '=')
		{
			free(curr_node->str);
			curr_node->str = new_env_var;
			info->env_changed = 1;
			return (0);
		}
		curr_node = curr_node->next;
	}
	add_node_end(&(info->env), new_env_var, 0);
	free(new_env_var);
	info->env_changed = 1;
	return (0);
}
