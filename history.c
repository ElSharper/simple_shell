#include "shell.h"

/**
 * get_history_file - Returns the allocated string containing the history file.
 * @info: Pointer to the info_t struct.
 *
 * Return: Allocated string containing the history file, or NULL on failure.
 */

char *get_history_file(info_t *info)
{
	char *file_buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	file_buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!file_buf)
		return (NULL);
	file_buf[0] = '\0';
	_strcpy(file_buf, dir);
	_strcat(file_buf, "/");
	_strcat(file_buf, HIST_FILE);
	return (file_buf);
}

/**
 * write_history - Writes the history to a file.
 * @info: Pointer to the info_t struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
	ssize_t file_descriptor;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	file_descriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file_descriptor == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}
	_putfd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}

/**
 * read_history - Reads the history from a file.
 * @info: Pointer to the info_t struct.
 *
 * Return: The number of history entries read on success, 0 on failure.
 */
int read_history(info_t *info)
{
	int index, last = 0, line_count = 0;
	ssize_t file_descriptor, read_len, file_size = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	file_descriptor = open(filename, O_RDONLY);
	free(filename);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &st))
		file_size = st.st_size;
	if (file_size < 2)
		return (0);
	buf = malloc(sizeof(char) * (file_size + 1));
	if (!buf)
		return (0);
	read_len = read(file_descriptor, buf, file_size);
	buf[file_size] = '\0';
	if (read_len <= 0)
		return (free(buf), 0);
	close(file_descriptor);
	for (index = 0; index < file_size; index++)
	{
		if (buf[index] == '\n')
		{
			buf[index] = '\0';
			build_history_list(info, buf + last, line_count++);
			last = index + 1;
		}
	}
	if (last != index)
		build_history_list(info, buf + last, line_count++);
	free(buf);
	info->histcount = line_count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Adds an entry to the history linked list.
 * @info: Pointer to the info_t struct.
 * @buf: The buffer containing the history entry.
 * @linecount: The line count of the history entry.
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - Renumbers the history linked list after changes.
 * @info: Pointer to the info_t struct.
 *
 * Return: The new histcount.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int count = 0;

	while (node)
	{
		node->num = count++;
		node = node->next;
	}
	return (info->histcount = count);
}
