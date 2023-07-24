#include "main.h"
/**
 * is_chain - test if is chain delimeter
 * @inf: struct inf
 * @buf: chain buffer
 * @pos: current position
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *inf, char *buf, size_t *pos)
{
	size_t i = *pos;

	if (buf[i] == '|' && buf[i + 1] == '|')
	{
		buf[i] = 0;
		i++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buf[i] == '&' && buf[i + 1] == '&')
	{
		buf[i] = 0;
		i++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buf[i] == ';')
	{
		buf[i] = 0;
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = i;
	return (1);
}

/**
 * check_chain - checkd if we should continue
 * based on the last status
 * @buf: buffer
 * @inf: info struct
 * @pos: current position
 * @s1: starting position
 * @len: buf length
 *
 * Return: void
 */
void check_chain(info_t *inf, char *buf, size_t *pos, size_t s1, size_t len)
{
	size_t i = *pos;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buf[s1] = 0;
			i = len;
		}
	}

	*pos = i;
}

/**
 * replace_alias - replaces an aliases
 * @inf: info struct
 *
 * Return: 1 if successiful, otherwise 0
 */
int replace_alias(info_t *inf)
{
	int j;
	list_t *n;
	char *pos;

	for (j = 0; j < 10; j++)
	{
		n = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!n)
			return (0);
		free(inf->argv[0]);
		pos = _strchr(n->str, '=');
		if (!pos)
			return (0);
		pos = _strdup(pos + 1);
		if (!pos)
			return (0);
		inf->argv[0] = pos;
	}
	return (1);
}
/**
 * replace_vars - replaces vars
 * @inf: info struct
 *
 * Return: 1 if success, otherwise 0 on fail
 */
int replace_var(info_t *inf)
{
	int j = 0;
	list_t *n;

	for (j = 0; inf->argv[j]; j++)
	{
		if (inf->argv[j][0] != '$' || !inf->argv[j][1])
			continue;

		if (!_strcmp(inf->argv[j], "$?"))
		{
			replace_string(&(inf->argv[j]),
					_strdup(convert_number(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[j], "$$"))
		{
			replace_string(&(inf->argv[j]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		n = node_starts_with(inf->env, &inf->argv[j][1], '=');
		if (n)
		{
			replace_string(&(inf->argv[j]),
					_strdup(_strchr(n->str, '=') + 1));
			continue;
		}
		replace_string(&inf->argv[j], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - replaces string
 * @str1: old string
 * @str2: new string
 *
 * Return: 1 if successiful, 0 on fail
 */
int replace_string(char **str1, char *str2)
{
	free(*str1);
	*str1 = str2;
	return (1);
}
