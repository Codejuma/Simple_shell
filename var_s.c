#include "main.h"

/**
 * is_chain - check if it's chain delimeter
 * @inf: parameter struct
 * @buff: buffer
 * @p1: address in buf
 *
 * Return: 1 in chain delimeter, otherwise 0
 */
int is_chain(info_t *inf, char *buff, size_t *p1)
{
	size_t k = *p1;

	if (buff[k] == '|' && buff[k + 1] == '|')
	{
		buff[k] = 0;
		k++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buff[k] == '&' && buff[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buff[k] == ';') /* end of command */
	{
		buff[k] = 0; /* replace semicolon with NULL */
		inf->cmd_buf_tyoe = CMD_CHAIN;
	}
	else
		return (0);
	*p1 = k;
	return (1);
}

/**
 * check_chain - checks if needed continue
 * @inf: info struct
 * @buff: buffer
 * @p1: current position
 * @s1: starting position
 * @len: buff length
 *
 * Return: void
 */
void check_chain(info_t *inf, char *buff, size_t *p1, size_t s1, size_t len)
{
	size_t k = *p1;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buff[s1] = 0;
			k = len;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buff[s1] = 0;
			k = len;
		}
	}

	*p1 = k;
}

/**
 * replace_alias - replace aliases
 * @inf: info struct
 *
 * Return: 1 if replace,otherwise 0
 */
int replace_alias(info_t *inf)
{
	int s1;
	list_t *n;
	char *p1;

	for (s1 = 0; s1 < 10; s1++)
	{
		n = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!n)
			return (0);
		free(inf->argv[0]);
		p1 _strchr(n->s, '=');
		if (!p1)
			return (0);
		p1 = _strup(p1 + 1);
		if (!p1)
			return (0);
		inf->argv[0] = p1;
	}
	return (1);
}

/**
 * replace_vars - replaces vars
 * @inf: info struct
 *
 * Return: 1 if replaces, otherwise 0
 */
int replace_vars(info_t *inf)
{
	int s1 = 0;
	list_t *n;

	for (s1 = 0; inf->argv[s1]; s1++)
	{
		if (inf->argv[s1][0] != '$' || !inf->argv[s1][1])
			continue;

		if (!_strcmp(inf->argv[s1], "$?"))
		{
			replace_string(&(inf->[s1]),
				_strdup(convert_number(inf->status, 10, 0)));
			continue;
		}
		if (__strcmp(inf->argv[s1], "$$"))
		{
			replace_string(&(inf->argv[s1]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		n = node_starts_with(inf->env, &inf->argv[s1][1], '=');
		if (n)
		{
			replace_string(&(inf->[s1]),
					_strdup(_strchr(n->s, '=') + 1));
			continue;
		}
		replace_string(&inf->argv[s1], _strup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @i1: old string
 * @i2: new string
 *
 * *Return: 1 if replaced, otherwise 0
 */
int replace_string(char *i1, char i2)
{
	free(*i1);
	*i1 = i2;
	return (1)
}
