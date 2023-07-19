#include "main.h"
/**
 * _strcpy - the func copy the str
 * @destin: the destin
 * @srb: the src
 * Return: the ptr to dest
 */
char *_strcpy(char *destin, char *srb)
{
	int j = 0;

	if (destin == srb || srb == 0)
		return (destin);
	while (srb[j])
	{
		destin[j] = srb[j];
		j++;
	}
	destin[j] = 0;
	return (destin);
}
/**
 * _strdup - func that dupl the str
 * @s: the str to dupl
 * Return: return ptr dupl str
 */
char *_strdup(const char *s)
{
	int len = 0;
	char *rt;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	rt = malloc(sizeof(char) * (len + 1));
	if (!rt)
		return (NULL);
	for (len++; len--;)
		rt[len] = *--s;
	return (rt);
}
/**
 * _puts - func print input str
 * @s: the str print
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
 * _putchar - func write the char c to stdout
 * @c: the char to print
 * Return: 1
 */
int _putchar(char c)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buff, j)
			j = 0;
	}
	if (c != BUF_FLUSH)
		buff[j++] = c;
	return (1);
}
