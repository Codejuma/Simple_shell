#include "main.h"
/**
 * list_len - func looks len list
 * @fn: first head ptr
 * Return: return the size
 */
size_t list_len(const list_t *fn)
{
	size_t j = 0;

	while (fn)
	{
		fn = fn->next;
		j++;
	}
	return (j);
}
/**
 * list_to_strings - func to return array
 * @fn: first node ptr
 * Return: return array str
 */
char **list_to_strings(list_t *fn)
{
	list_t *nodd = fn;
	size_t j = list_len(fn), m;
	char **sts;
	char *st;

	if (!fn || !j)
		return (NULL);
	sts = calloc(j + 1, sizeof(char *));
	if (!sts)
		return (NULL);
	for (j = 0; nodd; nodd = nodd->next, j++)
	{
		st = calloc(_strlen(nodd->str) + 1, sizeof(char));
		if (!st)
		{
			for (m = 0; m < j; m++)
				free(sts[m]);
			free(sts);
			return (NULL);
		}
		st = _strcpy(st, nodd->str);
		sts[j] = st;
	}
	sts[j] = NULL;
	return (sts);
}
