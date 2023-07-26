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
	sts = malloc(sizeof(char *) * (j + 1));
	if (!sts)
		return (NULL);
	for (j = 0; nodd; nodd = nodd->next, j++)
	{
		st = malloc(_strlen(nodd->str) + 1);
		if (!st)
		{
			for (m = 0; m < j; m++)
				free(sts[m]);
			free(sts);
			return (NULL);
		}
		st = _strcpy(st, nodd->str);
		sts[j] = st;
		free(st);
	}
	sts[j] = NULL;
	return (sts);
}
/**
 * print_list - func print all elmt
 * @fn: fst node ptr
 * Return: return size
 */
size_t print_list(const list_t *fn)
{
	size_t j = 0;

	while (fn)
	{
		_puts(convert_number(fn->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(fn->str ? fn->str : "(nil)");
		_puts("\n");
		fn = fn->next;
		j++;
	}
	return (j);
}
/**
 * node_starts_with - func node str
 * @nodd: list ptr
 * @prfx: str march
 * @b: the char which is next
 * Return: return node otherwise null
 */
list_t *node_starts_with(list_t *nodd, char *prfx, char b)
{
	char *pr = NULL;

	while (nodd)
	{
		pr = starts_with(nodd->str, prfx);
		if (pr && ((b == -1) || (*pr == b)))
			return (nodd);
		nodd = nodd->next;
	}
	return (NULL);
}
/**
 * get_node_index - func idx node
 * @hd: the ptr head
 * @nodd: the ptr node
 * Return: return idx otherwise -1
 */
ssize_t get_node_index(list_t *hd, list_t *nodd)
{
	size_t j = 0;

	while (hd)
	{
		if (hd == nodd)
			return (j);
		hd = hd->next;
		j++;
	}
	return (-1);
}

