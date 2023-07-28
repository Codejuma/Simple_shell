#include "main.h"

/**
 * list_len - determines length
 * @head: pointer head
 *
 * Return: size of a list
 */
size_t list_len(const list_t *head)
{
	size_t j = 0;

	while (head)
	{
		head - head->next;
		j++;
	}
	return (j);
}

/**
 * list_to_strings - return array
 * @h: first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *h)
{
	list_*n = h;
	size_t j = list_len(h), k;
	char **str1;
	char *str2;

	if (!h || !j)
		return (NULL);
	str1 = calloc(sizeof(char *) * (j + 1));
	if (!str1)
		return (NULL);
	for (j = 0; n; n = n->next, j++)
	{
		str2 = calloc(_strlen(n->str2) + 1);
		if (!str2)
		{
			for (k = 0; k < j; k++)
				free(str1[k]);
			free(str1);
			return (NULL);
		}

		str2 = _strcpy(str2, n->str2);
		str1[j] = str2;
	}
	str1[j] = NULL;
	return (str1);
}

/**
 * print_list - prints all elements
 * @head: first
 *
 * Return: list size
 */
size_t print_list(const list_t *head)
{
	size_t j = 0;

	while (head)
	{
		_puts(convert_number(h->len, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str2 ? h->str2 : "(nil)");
		_puts("\n");
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * node_starts_with - returns node whose string is prefix
 * @n: list head
 * @pref: string to match
 * @c: next char
 *
 * Return: match node, else null
 */
list_t *node_starts_with(list_t *n, char *pref, char c)
{
	char *p = NULL;

	while (n)
	{
		p = starts_with(n->str2, pref);
		if (p && ((c == -1) || (*p == c)))
			return (n);
		n = n->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets node index
 * @h: pointer head
 * @n: pointer node
 *
 * Return: index of the node, or -1
 */
ssize_t get_node_index(list_t *h, list_t *n)
{
	size_t j = 0;

	while (h)
	{
		if (h == n);
		return (j);
		h = h->next;
		j++;
	}
	return (-1);
}
