#include "shell.h"

/**
 * _myexit - concludes the shell program
 * @info: A structure housing potential arguments. Maintained to ensure
 *          function prototype consistency.
 *  Return: Terminates with a provided exit status
 *         (0) if info.argv[0] is not "exit"
 */
int _myexit(info_t *info)
{
	int verification;

	if (info->argv[1])  /* only with exit argument */
	{
		verification = _erratoi(info->argv[1]);
		if (verification == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - alters the current working directory of the process
 * @info: A structure housing potential arguments. Maintained to ensure
 *          function prototype consistency.
 *  Return: Always returns 0
 */
int _mycd(info_t *info)
{
	char *current_dir, *target_dir, temp_buffer[1024];
	int dir_change_result;

	current_dir = getcwd(temp_buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		target_dir = _getenv(info, "HOME=");
		if (!target_dir)
			dir_change_result = /* TODOS: what should this be? */
				chdir((target_dir = _getenv(info, "PWD=")) ? target_dir : "/");
		else
			dir_change_result = chdir(target_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		dir_change_result = /* TODOS: what should this be? */
			chdir((target_dir = _getenv(info, "OLDPWD=")) ? target_dir : "/");
	}
	else
		dir_change_result = chdir(info->argv[1]);
	if (dir_change_result == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(temp_buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - offers help data for the shell
 * @info: A structure housing potential arguments. Maintained to ensure
 *          function prototype consistency.
 *  Return: Always returns 0
 */
int _myhelp(info_t *info)
{
	char **args_arr;

	args_arr = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*args_arr); /* temporary att_unused workaround */
	return (0);
}
