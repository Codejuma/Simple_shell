#include "main.h"

/**
 * add_node - insert node at start
 * @h: address pointer
 * @s: string of the node
 * @len: node index
 *
 * Return: size of list
 */
list_t *add_node(list_t **h, const char *s, int len)
{
	list_t *new;

	if (!h)
		return (NULL);
	new = calloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->len = len;
	if (s)
	{
		new->s = _strdup(s);
		if (!new->s)
		{
			free(!new);
			return (NULL);
		}
	}
	new->next = *h;
	*h = new;
	return (new);
}

/**
 * add_node_end - add at the end of the the node
 * @h: head
 * @s: string
 * @len: index of the node
 *
 * Return: List size
 */
list_t *add_node_end(list_t **h, const char *s, int len)
{
	list_t *new, *n;

	if (!h)
		return (NULL);
	n = *h;
	new = calloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->len = len;
	if (s)
	{
		new->s = _strdup(s);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	if (n)
	{
		while (n->next)
			n = n->next;
		n->next = new;
	}
	else
		*h = new;
	return (new);
}
/**
 * print_list_str - prints only string
 * @head: pointer
 *
 * Return: size of list
 */
size print_list_str(const list_t *head)
{
	size_t j = 0;

	while (head)
	{
		_puts(head->s ? head->s : "(nil)");
		_puts("\n");
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * delete_node_at_index - deletes
 * @h: head
 * @index: indexof node
 *
 * Return: 1 on success, otherwise 0
 */
int delete_node_at_index(list_t **h, unsigned int index)
{
	list_t *n, *prev_n;
	unsigned int j = 0;

	if (!h || !*h)
		return (0);

	if (!index)
	{
		n = *h;
		*h = (*h)->next;
		free(n->s);
		free(n);
		return (1);
	}
	n = *h;
	while (n)
	{
		if (j == index)
		{
			prev_n->next = n->next;
			free(n->s);
			free(n);
			return (1);
		}
		j++;
		prev_n = n;
		n = n->next;
	}
	return (0);
}

/**
 * free_list - frees all
 * @h_ptr: points to head
 *
 * Return: void
 */
void free_list(list_t **h_ptr)
{
	list_t *n, *next_n, *h;
	if (!h_ptr || !*h_ptr)
		return;
	h = *h_ptr;
	n = h;
	while (n)
	{
		next_n = n->next;
		free(n->s);
		free(n);
		n = next_n;
	}
	*h_ptr = NULL;
}
