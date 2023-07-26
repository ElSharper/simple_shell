#include "shell.h"

/**
 * input_buf - Buffers chained commands from the input.
 * @info: Structure containing potential arguments.
 * @buf: Address of the buffer.
 * @len: Address of the length variable.
 *
 * Return: Number of bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t read_bytes = 0;
	size_t buffer_len = 0;

	if (!*len) /* If there's nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		read_bytes = getline(buf, &buffer_len, stdin);
#else
		read_bytes = _getline(info, buf, &buffer_len);
#endif
		if (read_bytes > 0)
		{
			if ((*buf)[read_bytes - 1] == '\n')
			{
				(*buf)[read_bytes - 1] = '\0'; /* Remove trailing newline */
				read_bytes--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) Is this a command chain? */
			{
				*len = read_bytes;
				info->cmd_buf = buf;
			}
		}
	}
	return (read_bytes);
}

/**
 * get_input - Retrieves the next line of input from the user.
 * @info: Structure containing potential arguments.
 *
 * Return: Number of bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* Buffer for ';' command chain */
	static size_t buf_pos, buf_end, buf_len;
	ssize_t read_bytes = 0;
	char **buf_ptr = &(info->arg), *current_pos;

	_putchar(BUF_FLUSH);
	read_bytes = input_buf(info, &buf, &buf_len);
	if (read_bytes == -1) /* EOF */
		return (-1);
	if (buf_len) /* There are commands left in the chain buffer */
	{
		buf_end = buf_pos;
		current_pos = buf + buf_pos; /* Get a pointer for return */

		check_chain(info, buf, &buf_end, buf_pos, buf_len);
		while (buf_end < buf_len) /* Iterate to semicolon or end */
		{
			if (is_chain(info, buf, &buf_end))
				break;
			buf_end++;
		}

		buf_pos = buf_end + 1; /* Increment past the nullified ';' */
		if (buf_pos >= buf_len) /* Have we reached the end of the buffer? */
		{
			buf_pos = buf_len = 0; /* Reset the position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_ptr = current_pos;
		return (_strlen(current_pos)); /* Return the length of the current command */
	}

	*buf_ptr = buf;
	return (read_bytes); /* Return the length of the buffer from _getline() */
}

/**
 * read_buf - Reads from the input buffer.
 * @info: Structure containing potential arguments.
 * @buf: Buffer to read into.
 * @pos: Size of the buffer.
 *
 * Return: Number of bytes read.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *pos)
{
	ssize_t read_bytes = 0;

	if (*pos)
		return (0);
	read_bytes = read(info->readfd, buf, READ_BUF_SIZE);
	if (read_bytes >= 0)
		*pos = read_bytes;
	return (read_bytes);
}

/**
 * _getline - Gets the next line of input from STDIN.
 * @info: Structure containing potential arguments.
 * @ptr: Address of the pointer to the buffer, preallocated or NULL.
 * @length: Size of the preallocated ptr buffer if not NULL.
 *
 * Return: Number of bytes read.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t buf_pos, buf_len;
	size_t line_len;
	ssize_t read_bytes = 0, stored_bytes = 0;
	char *buffer_ptr = NULL, *new_buffer_ptr = NULL, *c;

	buffer_ptr = *ptr;
	if (buffer_ptr && length)
		stored_bytes = *length;
	if (buf_pos == buf_len)
		buf_pos = buf_len = 0;

	read_bytes = read_buf(info, buf, &buf_len);
	if (read_bytes == -1 || (read_bytes == 0 && buf_len == 0))
		return (-1);

	c = _strchr(buf + buf_pos, '\n');
	line_len = c ? 1 + (unsigned int)(c - buf) : buf_len;
	new_buffer_ptr = _realloc(buffer_ptr, stored_bytes,
		stored_bytes ? stored_bytes + line_len : line_len + 1);
	if (!new_buffer_ptr) /* MALLOC FAILURE! */
		return (buffer_ptr ? (free(buffer_ptr), -1) : -1);

	if (stored_bytes)
		_strncat(new_buffer_ptr, buf + buf_pos, line_len - buf_pos);
	else
		_strncpy(new_buffer_ptr, buf + buf_pos, line_len - buf_pos + 1);

	stored_bytes += line_len - buf_pos;
	buf_pos = line_len;
	buffer_ptr = new_buffer_ptr;

	if (length)
		*length = stored_bytes;
	*ptr = buffer_ptr;
	return (stored_bytes);
}

/**
 * sigintHandler - Handles the SIGINT signal (Ctrl+C).
 * @sig_num: The signal number.
 *
 * Return: Void.
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
