#include"main.h"
/**
 * get_history_file - gets history file
 * @inf: info struct
 *
 * Return: allocated string
 */
char *get_history_file(info_t *inf)
{
	char *buff, *dirr;

	dirr = _getenv(inf, "HOME=");
	if (!dirr)
		return (NULL);
	buff = (char *)calloc(_strlen(dirr) + _strlen(HIST_FILE) + 2, sizeof(char));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dirr);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - creates file
 * @inf: info struct
 *
 * Return: 1 on success, otherwise -1
 */
int write_history(info_t *inf)
{
	ssize_t fd;
	char *fn = get_history_file(inf);
	list_t *n = NULL;

	if (!fn)
		return (-1);

	fd = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (fd == -1)
		return (-1);
	for (n = inf->history; n; n = n->next)
	{
		_putsfd(n->str, fd);
		_putfd('\n', fd);
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history
 * @inf: info struct
 *
 * Return: history count on success, otherwise 0
 */
int read_history(info_t *inf)
{
	int j, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *fn = get_history_file(inf);

	if (!fn)
		return (0);

	fd = open(fn, O_RDONLY);
	free(fn);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = (char *)calloc(fsize + 1, sizeof(char));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (j = 0; j < fsize; j++)
		if (buff[j] == '\n')
		{
			buff[j] = 0;
			build_history_list(inf, buff + last, linecount++);
			last = j + 1;
		}
	if (last != j)
		build_history_list(inf, buff + last, linecount++);
	free(buff);
	inf->histcount = linecount;
	while (inf->histcount-- >= HIST_MAX)
		delete_node_at_index(&(inf->history), 0);
	renumber_history(inf);
	return (inf->histcount);
}

/**
 * build_history_list - adds entry to linked list
 * @inf: info struct
 * @buff: buffer
 * @linecount: histo count
 *
 * Return: Always 0
 */
int build_history_list(info_t *inf, char *buff, int linecount)
{
	list_t *n = NULL;

	if (inf->history)
		n = inf->history;
	add_node_end(&n, buff, linecount);

	if (!inf->history)
		inf->history = n;
	return (0);
}
/**
 * renumber_history - funct renumbers the hist list
 * @inf: struct having args
 * Return: the new count
 */
int renumber_history(info_t *inf)
{
	list_t *n = inf->history;
	int j = 0;

	while (n)
	{
		n->num = j++;
		n = n->next;
	}
	return (inf->histcount = j);
}
