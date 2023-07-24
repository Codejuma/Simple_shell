#include "main.h"
/**
 * _strlen - func gives len of str
 * @str: the str
 * Return: return int len of str
 */
int _strlen(char *str)
{
	int j = 0;

	if (!str)
		return (0);

	while (*str++)
		j++;
	return (j);
}
/**
 * _strcmp - funct of lexgraphic comprs
 * @str1: the fist str
 * @str2: the second str
 * Return: return - otherwise +
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}
/**
 * starts_with - func of needle start haystc
 * @hystk: str searched
 * @ndl: the sub-str
 * Return: return addrs of nxt cha of hystk
 */
char *starts_with(const char *hystk, const char *ndl)
{
	while (*ndl)
		if (*ndl++ != *hystk++)
			return (NULL);
	return ((char *)hystk);
}
/**
 * _strcat - func concates 2 str
 * @destin: the dest buffer
 * @srb: the buffer sourc
 * Return: return ptr dest buff
 */
char *_strcat(char *destin, char *srb)
{
	char *rt = destin;

	while (*destin)
		destin++;
	while (*srb)
		*destin++ = *srb++;
	*destin = *srb;
	return (rt);
}
