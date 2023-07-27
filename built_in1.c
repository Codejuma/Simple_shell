#include "main.h"
/**
 * _myhistory - func that display no
 * @inf: struct args
 * Return: 0
 */
int _myhistory(info_t *inf)
{
	print_list(inf->history);
	return 0;
}
/**
 * unset_alias - func set alias
 * @inf: par astr
 * @s: str
 * Return: 0
 */
int unset_alias(info_t *inf, char *s)
{
	char *k, b;
	int rt;

	k = _strchr(s, '=');
	if (!k)
		return 1;

	b = *k;
	*k = 0;
	rt = delete_node_at_index(&(inf->alias), get_node_index(inf->alias, node_starts_with(inf->alias, s, -1)));
	*k = b;
	return (rt);
}
/**
 * set_alias - func that sets
 * @inf: par strcu
 * @s: str
 * Return: 0 othwer 1
 */
int set_alias(info_t *inf, char *s)
{
	char *k;

	k = _strchr(s, '=');
	if (!k)
		return (1);
	if (!++k)
		return (unset_alias(inf, s));

	unset_alias(inf, s);
	return (add_node_end(&(inf->alias), s, 0) == NULL);
}
/**
 * print-alias - print alias str
 * @nodd: the alias
 * Return: 0 or 1
 */
int print_alias(list_t *nodd)
{
	char *k = NULL, *b = NULL;

	if (nodd)
	{
		k = _strchr(nodd->str, '=');
		for (b = nodd->str; b <= k; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(k + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _myalias - func mimics alias
 * @inf: struc having args
 * Return: 0
 */
int _myalias(info_t *inf)
{
	int j = 0;
	char *k = NULL;
	list_t *nodd = NULL;

	if (inf->argc == 1)
	{
		nodd = inf->alias;
		while (nodd)
		{
			print_alias(nodd);
			nodd = nodd->next;
		}
		return (0);
	}
	for (j = 1; inf->argv[j]; j++)
	{
		k = _strchr(inf->argv[j], '=');
		if (k)
			set_alias(inf, inf->argv[j]);
		else
			print_alias(node_starts_with(inf->alias, inf->argv[j], '='));
	}
	return (0);
}
