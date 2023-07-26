#include "shell.h"

/**
 * hsh - Main shell loop that handles user input and executes commands.
 * @info: The parameter and return info struct.
 * @av: The argument vector from main.
 *
 * Return: 0 on success, 1 on error, or an error code.
 */
int hsh(info_t *info, char **av)
{
	ssize_t input_result = 0;
	int builtin_result = 0;

	while (input_result != -1 && builtin_result != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		input_result = get_input(info);
		if (input_result != -1)
		{
			set_info(info, av);
			builtin_result = find_builtin(info);
			if (builtin_result == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_result == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_result);
}

/**
 * find_builtin - Searches for a builtin command and executes it if found.
 * @info: The parameter and return info struct.
 *
 * Return: -1 if the builtin command is not found,
 *         0 if the builtin command is executed successfully,
 *         1 if the builtin command is found but not successful,
 *         -2 if the builtin command signals an exit.
 */
int find_builtin(info_t *info)
{
	int index, builtin_result = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (index = 0; builtintbl[index].type; index++)
		if (_strcmp(info->argv[0], builtintbl[index].type) == 0)
		{
			info->line_count++;
			builtin_result = builtintbl[index].func(info);
			break;
		}
	return (builtin_result);
}

/**
 * find_cmd - Searches for a command in the PATH environment variable.
 * @info: The parameter and return info struct.
 *
 * Return: void.
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int index, counter;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (index = 0, counter = 0; info->arg[index]; index++)
		if (!is_delim(info->arg[index], " \t\n"))
			counter++;
	if (!counter)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "Command not found\n");
		}
	}
}

/**
 * fork_cmd - Use forks to run cmd.
 * @info: Return information of the structure.
 *
 * Return: void.
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: Handle error in the function */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: Handle error in the function */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
