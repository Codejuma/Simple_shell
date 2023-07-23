#include "main.h"

/**
 * display_history - displays history list
 * @inf: Struct containing argument
 *
 * Return: Always 0
 */
int display_history(info_t *inf)
{
	print_list(inf->history);
	return (0);
}

/**
 * unset_alias - sets string alias
 * @inf: parameter struct
 * @s: string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *inf, char *s)
{
	char *j, a;
	int rt;

	j = _strchr(s, '=');
	if (!j)
		return (1);
	a = *j;
	*j = 0;
	rt = delete_node_at_index(&(inf->alias),
			get_node_index(inf->alias, node_starts_with(inf->alias, s, -1)));
	*j = a;
	return (rt);
}

/**
 * set_alias - sets alias
 * @inf: information struct
 * @s: string alias
 *
 * Return: 0 Always on success, 1 on error
 */
int set_alias(info_t *inf, char *s)
{
	char *j;

	j = _strchr(s, '=');
	if (!j)
		return (1);
	if (!*++j)
		return (unset_alias(inf, s));
	unset_alias(inf, s);
	return (add_node_end(&(inf->alias), s, 0) == NULL);
}

/**
 * print_alias - prints alias string
 * @n: alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *n)
{
	char *j = NULL, *c = NULL;

	if (n)
	{
		j = _strchr(n->str, '=');
		for (c = n->str; c <= j; c++)
			_putchar(*c);
		_putchar('\'');
		_puts(j + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _myalias - copy alias builtin
 * @inf: struc containing inf
 *
 * Return: Always 0
 */
int _myalias(info_t *inf)
{
	int m = 0;
	char *j = NULL;
	list_t *n = NULL;

	if (inf->argc == 1)
	{
		n = inf->alias;
		while (n)
		{
			print_alias(n);
			n = n->next;
		}
		return (0);
	}
	for (m = 1; inf->argv[m]; m++)
	{
		j = _strchr(inf->argv[m], '=');
		if (j)
			set_alias(inf, inf->argv[m]);
		else
			print_alias(node_starts_with(inf->alias, inf->argv[m], '='));
	}

	return (0);
}
