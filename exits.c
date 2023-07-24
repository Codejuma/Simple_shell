#include "main.h"
/**
 * *_strncpy - funct copies str
 * @destin: destin str to be copied
 * @sr: the str source
 * @m: the amount chae copied
 * Return: return the str
 */
char *_strncpy(char *destin, char *sr, int m)
{
	int a, b;
	char *str = destin;

	a = 0;
	while (sr[a] != '\0' && a < m - 1)
	{
		destin[a] = sr[a];
		a++;
	}
	if (a < m)
	{
		b = a;
		while (b < m)
		{
			destin[b] = '\0';
			b++;
		}
	}
	return (str);
}
/**
 * *_strncat - funct that joins 2 strs
 * @destin: the 1st str
 * @sr: the 2rd str
 * @m: the amount bytes used
 * Return: the str joined
 */
char *_strncat(char *destin, char *sr, int m)
{
	int a, b;
	char *str = destin;

	a = 0;
	b = 0;
	while (destin[a] != '\0')
		a++;
	while (sr[b] != '\0' && b < m)
	{
		destin[a] = sr[b];
		a++;
		b++;
	}
	if (b < m)
		destin[a] = '\0';
	return (str);
}
/**
 * *_strchr - func that locat char str
 * @str: the str parsed
 * @b: the char
 * Return: return pointer to memory
 */
char *_strchr(char *str, char b)
{
	do {
		if (*str == b)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
