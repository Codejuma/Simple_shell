#include "main.h"
/**
 * input_buf - funct buffer commands
 * @inf: structure par
 * @buff: the buffer address
 * @length: the length address
 * Return: return bytes
 */
ssize_t input_buf(info_t *inf, char **buff, size_t *length)
{
	ssize_t k = 0;
	size_t lep = 0;

	if (!*length) /* if nothing left fill it */
	{
		/*bree((void **)inf->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		k = getline(buff, &lep, stdin);
#else
		k = _getline(inf, buff, &lep);
#endif
		if (k > 0)
		{
			if ((*buff)[k - 1] == '\n')
			{
				(*buff)[k - 1] = '\0';
				k++;
			}
			inf->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(inf, *buff, inf->histcount++);
			{
				*length = k;
				inf->cmd_buf = buff;
			}
		}
	}
	return (k);
}
/**
 * get_input - func het line no nw
 * @inf: the strc para
 * Return: return the bytes
 */
ssize_t get_input(info_t *inf)
{
	static char *buff;
	static size_t a, b, lenn;
	ssize_t k = 0;
	char **buff_m = &(inf->arg), *m;

	_putchar(BUF_FLUSH);
	k = input_buf(inf, &buff, &lenn);
	if (k == -1)
		return (-1);
	if (lenn)
	{
		b = a;
		m = buff + a;

		check_chain(inf, buff, &b, a, lenn);
		while (b < lenn)
		{
			if (is_chain(inf, buff, &b))
				break;

			b++;
		}
		a = b + 1;
		if (a >= lenn)
		{
			a = lenn = 0;
			inf->cmd_buf_type = CMD_NORM;
		}
		*buff_m = m;
		return (_strlen(m));
	}
	*buff_m = buff;
	return (k);
}
/**
 * read_buf - the func is for buffer
 * @inf: structure par
 * @buff: the buff
 * @j: the size
 * Return: k
 */
ssize_t read_buf(info_t *inf, char *buff, size_t *j)
{
	ssize_t k = 0;

	if (*j)
		return (0);
	k = read(inf->readfd, buff, READ_BUF_SIZE);
	if (k >= 0)
		*j = k;
	return (k);
}
/**
 * _getline - the func line input
 * @inf: structure par
 * @ptrr: the pointer address buff
 * @leng: the allocation ptrr
 * Return: str
 */
int _getline(info_t *inf, char **ptrr, size_t *leng)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, lenn;
	size_t m;
	ssize_t k = 0, str = 0;
	char *n = NULL, *new_n = NULL, *b;

	n = *ptrr;
	if (n && leng)
		str = *leng;
	if (j == lenn)
		j = lenn = 0;

	k = read_buf(inf, buf, &lenn);
	if (k == -1 || (k == 0 && lenn == 0))
		return (-1);

	b = _strchr(buf + j, '\n');
	m = b ? 1 + (unsigned int)(b - buf) : lenn;
	new_n = _realloc(n, str, str ? str + m : m + 1);
	if (!new_n) /* malloc failure ! */
		return (n ? free(n), -1 : -1);

	if (str)
		_strncat(new_n, buf + j, m - j);
	else
		_strncpy(new_n, buf + j, m - j + 1);

	str += m - j;
	j = m;
	n = new_n;

	if (leng)
		*leng = str;
	*ptrr = n;
	return (str);
}
/**
 * sigintHandler - funct Ctrl - C
 * @s_n: the sig no
 * Return: void
 */
void sigintHandler(__attribute__((unused))int s_n)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
