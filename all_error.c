#include "main.h"
/**
 * _eputs - funct an str
 * @s: str print
 * Return: void
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
 * _eputchar - func the char
 * @c: the char
 * Return: 1
 */
int _eputchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}
/**
 * _putfd - func writes the char
 * @b: char print
 * @k: file descriptor
 * Return: 1
 */
int _putfd(char b, int k)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (b == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(k, buf, j);
		j = 0;
	}
	if (b != BUF_FLUSH)
		buf[j++] = b;
	return (1);
}
/**
 * _putsfd - func print
 * @s: str print
 * @i: file desrciptor
 * Return: return no chars
 */
int _putsfd(char *s, int i)
{
	int j = 0;

	if (!s)
		return (0);
	while (*s)
	{
		j += _putfd(*s++, i);
	}
	return (j);
}
