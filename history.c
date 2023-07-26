#include "main.h"
/**
 * get_history_file - the func of history
 * @inf: the structure par
 * Return: return str history
 */
char *get_history_file(info_t *inf)
{
	char *buff, *dirr;

	dirr = _getenv(inf, "HOME=");
	if (!dirr)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dirr) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dirr);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	free(buff);
	return (buff);
}
/**
 * write_history - func of the file his
 * @inf: the struct par
 * Return: 1 otherwise -1
 */
int write_history(info_t *inf)
{
	ssize_t fw;
	char *flnam = get_history_file(inf);
	list_t *nodd = NULL;

	if (!flnam)
		return (-1);

	fw = open(flnam, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(flnam);
	if (fw == -1)
		return (-1);
	for (nodd = inf->history; nodd; nodd = nodd->next)
	{
		_putsfd(nodd->str, fw);
		_putfd('\n', fw);
	}
	_putfd(BUF_FLUSH, fw);
	close(fw);
	return (1);
}
/**
 * read_history - func read hist
 * @inf: the structure par
 * Return: histcount othwise 0
 */
int read_history(info_t *inf)
{
	int j, lst = 0, lcont = 0;
	ssize_t fw, rdlenn, fsize = 0;
	struct stat stt;
	char *buff = NULL, *flnam = get_history_file(inf);

	if (!flnam)
		return (0);

	fw = open(flnam, O_RDONLY);
	free(flnam);
	if (fw == -1)
		return (0);
	if (!fstat(fw, &stt))
		fsize = stt.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlenn = read(fw, buff, fsize);
	buff[fsize] = 0;
	if (rdlenn <= 0)
		return (free(buff), 0);
	close(fw);
	for (j = 0; j < fsize; j++)
		if (buff[j] == '\n')
		{
			buff[j] = 0;
			build_history_list(inf, buff + lst, lcont++);
			lst = j + 1;
		}
	if (lst != j)
		build_history_list(inf, buff + lst, lcont++);
	free(buff);
	inf->histcount = lcont;
	while (inf->histcount-- >= HIST_MAX)
		delete_node_at_index(&(inf->history), 0);
	renumber_history(inf);
	return (inf->histcount);
}
/**
 * build_history_list - func entry to hist list
 * @inf: the struct have args
 * @buff: the buf
 * @lcont: the hist lincont and hist
 * Return: 0
 */
int build_history_list(info_t *inf, char *buff, int lcont)
{
	list_t *nodd = NULL;

	if (inf->history)
		nodd = inf->history;
	add_node_end(&nodd, buff, lcont);

	if (!inf->history)
		inf->history = nodd;
	return (0);
}
/**
 * renumber_history - renumbering hist list
 * @inf: the struct have args
 * Return: new histcount
 */
int renumber_history(info_t *inf)
{
	list_t *nodd = inf->history;
	int j = 0;

	while (nodd)
	{
		nodd->num = j++;
		nodd = nodd->next;
	}
	return (inf->histcount = j);
}
