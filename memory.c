#include "main.h"
/**
 * bfree - func free the ptr and NULL
 * @ptrr: the addrs otr
 * Return: 1 otherwise 0
 */
int bfree(void **ptrr)
{
	if (ptrr && *ptrr)
	{
		free(*ptrr);
		*ptrr = NULL;
		return (1);
	}
	return (0);
}
