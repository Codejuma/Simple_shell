#include "main.h"

/**
 * get_environ - returns the string array copy
 * @inf: struct info
 *
 * Return: Always 0
 */
char **get_environ(info_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = list_to_strings(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenv - removes environment variable
 * @inf: information struct
 * @var: var name
 *
 * Return: 1 on delete, otherwise 0
 */
int _unsetenv(info_t *inf, char *var)
{
	list_t *n = inf->env;
	size_t j = 0;
	char *a;

	if (!n || !var)
		return (0);

	while (n)
	{
		a = starts_with(n->str, var);
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
 * _setenv - inititalize new environment
 * @var: environment name
 * @inf: information name
 * @val: string value
 *
 * Return: Always 0
 */
int _setenv(info_t *inf, char *var, char *val)
{
	char *buf = NULL;
	list_t *n;
	char *a;

	if (!var || !val)
		return (0);

	buf = calloc(_strlen(var) + _strlen(val) + 2, sizeof(char));
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
