#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command.
 * @info: The info structure.
 * @path: the file path.
 *
 * Return: 1 if true, 0 if not.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat file_status;

	(void)info;
	if (!path || stat(path, &file_status) != 0)
		return (0);

	if (file_status.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Duplicates characters from a string.
 * @pathstr: The string to duplicate characters from.
 * @start: the index start.
 * @stop: The index stop.
 *
 * Return: Pointer to a new buffer containing the duplicated characters.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int index = 0, buffer_index = 0;

	for (buffer_index = 0, index = start; index < stop; index++)
		if (pathstr[index] != ':')
			buffer[buffer_index++] = pathstr[index];
	buffer[buffer_index] = '\0';
	return (buffer);
}

/**
 * find_path - Finds the full path of a command in string of the PATH.
 * @info: The info struct.
 * @pathstr: string of PATH.
 * @cmd: The command to find.
 *
 * Return: The full path of the command if found, or NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int index = 0, current_position = 0;
	char *filepath;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[index] || pathstr[index] == ':')
		{
			filepath = dup_chars(pathstr, current_position, index);
			if (*filepath == '\0')
				_strcpy(filepath, cmd);
			else
			{
				_strcat(filepath, "/");
				_strcat(filepath, cmd);
			}
			if (is_cmd(info, filepath))
				return (filepath);
			if (!pathstr[index])
				break;
			current_position = index + 1;
		}
		index++;
	}
	return (NULL);
}