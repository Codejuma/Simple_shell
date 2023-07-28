#include "main.h"

/**
 * is_cmd - determines
 * @inf: information struct
 * @p: file path
 *
 * Return: 1 if true, otherwise 0
 */
int is_cmd(info_t *inf, char *p)
{
	struct stat st;

	(void)inf;
	if (!p || stat(p, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicate the characters
 * @pstr: pathstring
 * @i1: start index
 * @i2: stop index
 *
 * Return: pointer
 */
char *dup_chars(char *pstr, int i1, int i2)
{
	static char buf[1024];
	int j = 0, r = 0;

	for (r = 0, j = i1; j < i2; j++)
		if (pstr[j] != ':')
			buf[r++] = pstr[j];
	buf[r] = 0;
	return (buf);
}

/**
 * find_path - finds cmdpath
 * @inf: struct info
 * @pstr: path string
 * @cmd: cmd to find
 *
 * Return: full path if found or NULL
 */
char *find_path(info_t *inf, char *pstr, char *cmd)
{
	int j = 0, curr_p = 0;
	char *path;

	if (!pstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pstr[j] || pstr[j] == ':')
		{
			path = dup_chars(pstr, curr_p, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(inf, path))
				return (path);
			if (!pstr[j])
				break;
			curr_p = j;
		}
		j++;
	}
	return (NULL);
}
