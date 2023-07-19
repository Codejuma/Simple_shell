#include "main.h"
/**
 * _eputs - prints input string
 * @s: string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *s)
{
	int j = 0;

	if (!s)
		return;
	while (s[j] != '\0')
	{
		_eputchar(s[j]);
		j++;
	}
}

/**
 * _eputchar - write char to stderr
 * @c: the character to be printed
 *
 * Return: 1 on success, -1 on error
 */
int _eputchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 * _putfd - write c to a given fd
 * @c: given character
 * @fd: filedescriptor
 *
 * Return: 1 on success, -1 on error
 */
int _putfd(char c, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @s: string to be printed
 * @fd: filedescriptor
 *
 * Return: number of chars put
 */
int _putsfd(char *s, int fd)
{
	int j = 0;

	if (!s)
		return (0);
	while (*s)
	{
		j += _putfd(*s++, fd);
	}
	return (j);
}
