#include "main.h"
/**
 * bfree - function that free the pointer
 * @p: the pointer address
 * Return: 1 for free othewise 0
 */
int bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
