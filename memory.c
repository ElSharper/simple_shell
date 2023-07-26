#include "shell.h"

/**
 * bfree - Frees the memory pointed to by a pointer and sets it to NULL.
 * @ptr: Address of the pointer to be freed.
 *
 * Return: 1 if memory is freed successfully, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
