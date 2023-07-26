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
		free(*buff);
		*buff = NULL;
		signal(SIGINT, SIG_DFL);
#if USE_GETLINE
		k = getline(buff, &lep, stdin);
#else
		k = _getline(inf, buff, &lep);
#endif
		if (k > 0)
		{
			if ((*buff)[k - 1] == '\n')
			{
				(*buff)[k - 1] = '\0'; /* remove trailing newline */
				k--;
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
	char *buff = 0; /* the ';' command chain buf */
	size_t a = 0, b = 0, lenn = 0;
	ssize_t k = 0;
	char **buff_m = &(inf->arg), *m = 0;

	_putchar(BUF_FLUSH);
	k = input_buf(inf, &buff, &lenn);
	if (k == -1) /* EOF */
		return (-1);
	if (lenn) /* we have cmd left in the chain buf */
	{
		b = a; /* init new iterator to current buf position */
		m = buff + a; /* get pointer for return */

		check_chain(inf, buff, &b, a, lenn);
		while (b < lenn) /* iterate to ; or end */
		{
			if (is_chain(inf, buff, &b))
				break;

			b++;
		}
		a = b + 1; /* increment past nulled ';'' */
		if (a >= lenn) /* reached end of buffer? */
		{
			a = lenn = 0; /* reset position and len */
			inf->cmd_buf_type = CMD_NORM;
		}
		*buff_m = m; /* pass back pointer to current command position */
		return (_strlen(m)); /* return length of current cmd */
	}
	*buff_m = buff; /* else not a chain, pass back buffer from _getline() */
	return (k); /* return length of buffer from _getline() */
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
 * _getline - func input from standard input
 * @inf: structure par
 * @ptrr: the pointer address
 * @leng: the allocation buffer
 * Return: str
 */
int _getline(info_t *inf, char **ptrr, size_t *leng)
{
	char buff[READ_BUF_SIZE];
	size_t j = 0, lenn = 0;
	size_t m;
	ssize_t k = 0, str = 0;
	char *n = NULL, *new_n = NULL, *b;

	n = *ptrr;
	if (n && leng)
		str = *leng;
	if (j == lenn)
		j = lenn = 0;

	k = read_buf(inf, buff, &lenn);
	if (k == -1 || (k == 0 && lenn == 0))
		return (-1);

	b = _strchr(buff + j, '\n');
	m = b ? 1 + (unsigned int)(b - buff) : lenn;
	new_n = _realloc(n, str, str ? str + m : m + 1);
	if (!new_n)
		return (n ? free(n), -1 : -1);

	if (str)
		_strncat(new_n, buff + j, m - j);
	else
		_strncpy(new_n, buff + j, m - j + 1);

	str += m - j;
	j = m;
	n = new_n;

	if (leng)
		*leng = str;
	*ptrr = n;
	return (str);
}
/**
 * sigintHandler - funct bloct control c
 * @signo: the no of signal
 * Return: nothing to return
 */
void sigintHandler(__attribute__((unused))int signo)
{
	_puts("\n");
	_puts("& ");
	_putchar(BUF_FLUSH);
}
