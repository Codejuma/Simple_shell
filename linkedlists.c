#include "main.h"
/**
 * add_list_node - adds node to start of list
 * @head: head of a node
 * @name: field node
 * @val: node index
 *
 * Return: list size
 */
list_t *add_list_node(list_t **head, const char *name, int val)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = val;
	if (name)
	{
		new_head->str = _strdup(name);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - add node to end of list
 * @head: node head
 * @name: field node
 * @val: node index
 *
 * Return: list size
 */
list_t *add_node_end(list_t **head, const char *name, int val)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = val;
	if (name)
	{
		new_node->str = _strdup(name);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}
/**
 * print_list_str - prints string element of linked list
 * @h1: first node
 *
 * Return: size list
 */
size_t print_list_str(const list_t *h1)
{
	size_t j = 0;

	while (h1)
	{
		_puts(h1->str ? h1->str : "(nil)");
		_puts("\n");
		h1 = h1->next;
		j++;
	}
	return (j);
}

/**
 * delete_node_at_index - deletes node
 * @head: pointer head
 * @idx: node index
 *
 * Return: 1 on sucees, otherwise 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int idx)
{
	list_t *node, *prev_node;
	unsigned int j = 0;

	if (!head || !*head)
		return (0);

	if (!idx)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (j == idx)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		j++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes
 * @head_p: pointer head
 * Return: void
 */
void free_list(list_t **head_p)
{
	list_t *node, *next_node, *head;

	if (!head_p || !*head_p)
		return;
	head = *head_p;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		node = next_node;
	}
	*head_p = NULL;
}
