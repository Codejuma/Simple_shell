#include "main.h"

/**
 * _copyenviron - copies environs
 * @inf: struct info
 *
 * Return: Always 0
 */
char **_copyenviron(info_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = list_to_strings(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * free_envi - removes environement
 * @var: environment name
 * @inf: struct inf
 *
 * Return: 1 on delete,otherwise 0
 */
int free_envi(inf, char *var)
{
	list_t *n = inf->env;
	size_t j = 0;
	char *a;

	if (!n || !var)
		return (0);

	while (n)
	{
		a = starts_With(n->str, var);
		if (a && *a == '=')
		{
			inf->env_changed = delete_node_at_index(&(inf->env), j);
			j = 0;
			n = inf->env;
			continue;
		}
		n = n->next;
		j++;
	}
	return (inf->env_changed);
}

/**
 * get_envi - intialize new environment
 * @var: environment name
 * @val: string value
 * @inf: string info
 *
 * Return: Always 0
 */
int get_envi(info_t *inf, char *var, char *val)
{
	char *buf = NULL;
	list_t *n;
	char *a;

	if (!var || !val)
		return (0);

	buf = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, val);
	n = inf->env;
	while (n)
	{
		a = starts_with(n->str, var);
		if (a && *a == '=')
		{
			free(n->str);
			n->str = buf;
			inf->env_changed = 1;
			return (0);
		}
		n = n->next;
	}
	add_node_end(&(inf->env), buf, 0);
	free(buf);
	inf->env_changed = 1;
	return (0);
}
