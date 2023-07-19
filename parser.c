#include "main.h"
/**
 * exe_cmd - determines executable comman
 * @inf: struct info
 * @p: path file
 *
 * Return: 1 if true, otherwise 0
 */
int exe_cmd(info_t *inf, char *p)
{
	struct stat st;

	(void)inf;
	if (!p || stat(p, &st))
		return (0);

	if (st.st_mode & 5_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * dup_char - duplicate chars
 * @ps: path string
 * @s1: start
 * @s2: stop
 *
 * Return: new buffer
 */
char *dup_char(char *ps, int s1, int s2)
{
	static char buf[1024];
	int j = 0, k = 0;

	for (k = 0, j = start; j < stop; j++)
		if (ps[j] != ':')
			buf[k++] = ps[j];
	buf[k] = 0;
	return (buf);
}

/**
 * find_cmdp - finds command in path string
 * @inf: struct info
 * @ps: path string
 * @cmd: command to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_cmdp(info_t *inf, char *ps, char *cmd)
{
	int j = 0, curr_pos = 0;
	char *p;

	if (!ps)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (find_cmdp(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!ps[j] || ps[j] == ':')
		{
			p = dub_char(ps, curr_pos, j);
			if (!*p)
				_strcat(p, cmd);
			else
			{
				_strcat(p, "/");
				_strcat(p, cmd);
			}
			if (find_cmdp(inf, p))
				return (p);
			if (!ps[j])
				break;
			curr_pos = j;
		}
		j++;
	}
	return (NULL);
}
