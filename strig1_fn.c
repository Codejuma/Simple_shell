#include "main.h"
/**
 * _strcpy - copy th strs
 * @ds: the destin
 * @sr: the source
 * Return: ptr to destin
 */
char *_strcpy(char *ds, char *sr)
{
	int j = 0;

	if (ds == sr || sr == 0)
		return (ds);
	while (sr[j])
	{
		ds[j] = sr[j];
		j++;
	}
	ds[j] = 0;
	return (ds);
}
/**
 * _strdup - func str
 * @str: str the dup
 * Return: ptr dup
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *rt;

	if (str == NULL)
		return (NULL);

	while (*str++)
		len++;
	rt = calloc(len + 1, sizeof(char));
	if (!rt)
		return (NULL);
	for (len++; len--; )
		rt[len] = *--str;
	return (rt);
}
/**
 * _puts - func the input str
 * @s: str print
 * Return: void
 */
void _puts(char *s)
{
	int j = 0;

	if (!s)
		return;
	while (s[j] != '\0')
	{
		_putchar(s[j]);
		j++;
	}
}
/**
 * _putchar - writes the char c to stdout
 * @c: char print
 * Return: 1
 */
int _putchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}
