#include "main.h"
/**
 * clear_info - the funct of info structure
 * @inf: the structure add
 * Return: nothing
 */
void clear_info(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}
/**
 * set_info - the func info structure
 * @inf: the structure addrs
 * @avg: arg vct
 * Return: nothing
 */
void set_info(info_t *inf, char **avg)
{
	int j = 0;

	inf->fname = avg[0];
	if (inf->arg)
	{
		inf->argv = strtow(inf->arg, " \t");
		if (!inf->argv)
		{
			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
				free(inf->argv);
			}
		}
		for (j = 0; inf->argv && inf->argv[j]; j++)
			;
		inf->argc = j;

		replace_alias(inf);
		replace_vars(inf);
	}
}
/**
 * free_info - fuction info strucure field
 * @inf: structure addrs
 * @fd: free if true fields
 * Return: nothing
 */
void free_info(info_t *inf, int fd)
{
	ffree(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (fd)
	{
		if (!inf->cmd_buf)
			free(inf->arg);
		if (inf->env)
			free_list(&(inf->env));
		if (inf->history)
			free_list(&(inf->history));
		if (inf->alias)
			free_list(&(inf->alias));
		ffree(inf->environ);
		inf->environ = NULL;
		bfree((void **)inf->cmd_buf);
		if (inf->readfd > 2)
			close(inf->readfd);
		_putchar(BUF_FLUSH);
	}
}
