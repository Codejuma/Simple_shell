#include "main.h"
/**
 * _strdup - func cope str
 * @s: the array
 * Return: return ptr
 */
char *_strdup(char *s)
{
	int i, j;
	char *str = NULL;

	if (s == NULL)
		return (0);
	for (i = 0; s[i]; i++)
		;

	i++;
	str = malloc(i * sizeof(char *));
	if (!str)
		return (NULL);

	for (j = 0; j < i; j++)
	{
		str[j] = s[j];
	}
	free(str);
	return (str);
}
/**
 * _itoa - func int to ascii
 * @num: number
 * @base: the bs
 * Return: return char
 */
char *_itoa(int num, int base)
{
	static char *array = "0123456789abcdef";
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (num < 0)
	{
		n = -num;
		sign = '-';
	}
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}
