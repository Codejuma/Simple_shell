#include "main.h"
/**
 * _memset - func that fills memory with const byte
 * @sp: potr to memory
 * @b: byte fill with *sp
 * @r: amount of byte
 * Return: ptr sp
 */
char *_memset(char *sp, char b, unsigned int r)
{
	unsigned int j;

	for (j = 0; j < r; j++)
		sp[j] = b;
	return (sp);
}
/**
 * ffree - funct that frees str to str
 * @ss: str of strs
 */
void ffree(char **ss)
{
	char **b = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(b);
}
/**
 * _realloc - func reallocates the bloc memory
 * @ptrr: ptr to last malloc block
 * @pre_size: byye size prev
 * @nxt_size: new byte size
 * Return: ptr of memory
 */
void *_realloc(void *ptrr, unsigned int pre_size, unsigned int nxt_size)
{
	char *k;

	if (!ptrr)
		return ((void *)memset(calloc(1, nxt_size), 0, nxt_size));
	if (!nxt_size)
		return (free(ptrr), NULL);
	if (nxt_size == pre_size)
		return (ptrr);

	k = calloc(nxt_size, sizeof(*k));
	if (!k)
		return (NULL);

	pre_size = pre_size < nxt_size ? pre_size : nxt_size;
	while (pre_size--)
		k[pre_size] = ((char *)ptrr)[pre_size];
	free(ptrr);
	return (k);
}
