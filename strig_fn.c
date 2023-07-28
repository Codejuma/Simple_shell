#include "main.h"
/**
 * _strlen - func len str
 * @str: str len
 * Return: int len
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
 * _strcmp - funct of lex compar
 * @str1: 1st str
 * @str2: 2rd str
 * Return: negative othewise posi
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
 * starts_with - func of hystakc
 * @haystack: str search
 * @needle: the str find
 * Return: addrss of next
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
/**
 * _strcat - funct concat 2 str
 * @dest: the destin
 * @src: the source
 * Return: return ptr
 */
char *_strcat(char *dest, char *src)
{
	char *rt = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (rt);
}

