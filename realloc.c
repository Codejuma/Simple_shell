#include "main.h"
/**
 * *_memset - func of memory with byte
 * @st: the ptr to memry
 * @a: the byte with ptr st
 * @m: the amnt of byt
 * Return: return st
 */
char *_memset(char *st, char a, unsigned int m)
{
	unsigned int j;

	for (j = 0; j < m; j++)
		st[j] = a;
	return (st);
}
/**
 * ffree - func free the str of strs
 * @strs: the str of strs
 * Return: nothing
 */
void ffree(char **strs)
{
	char **c = strs;

	if (!strs)
		return;
	while (*strs)
		free(*strs++);
	free(c);
}
/**
 * _realloc - func that re=allocates mmy
 * @ptrr: the ptr of prv mall
 * @pr_size: the old block
 * @nxt_size: the next block
 * Return: return the ptr
 */
void *_realloc(void *ptrr, unsigned int pr_size, unsigned int nxt_size)
{
	char *c;

	if (!ptrr)
		return (malloc(nxt_size));
	if (!nxt_size)
		return (free(ptrr), NULL);
	if (nxt_size == pr_size)
		return (ptrr);

	c = malloc(nxt_size);
	if (!c)
		return (NULL);

	pr_size = pr_size < nxt_size ? pr_size : nxt_size;
	while (pr_size--)
		c[pr_size] = ((char *)ptrr)[pr_size];
	free(ptrr);
	return (c);
}
