#include "main.h"
/**
 * _puts - func the str
 * @s: the str
 * Return: nothing to return
 */
void _puts(char *s)
{
	int j;

	for (j = 0 ; s[j] != '\0' ; j++)
	{
		_putchar(s[j]);
	}
	_putchar('\n');
}
/**
 * _strlen - the func str
 * @s: use int
 * Return: return the len str
 */
int _strlen(const char *s)
{
	int j;

	j = 0;
	while (s[j] != '\0')
	{
		j++;
	}
	return ((j + 1));
}
/**
 * _putchar - writes the character c to stdout
 * @c: the character to print
 * Return: 1
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * str_concat - funct pack ptr to array
 * @s1: arr 1
 * @s2: arr 2
 * Return: return array
 */
char *str_concat(char *s1, char *s2)
{
	char *dst;
	unsigned int i, j, size;

	/* If the array is empty */
	if (s1 == NULL)
		s1 = "";

	if (s2 == NULL)
		s2 = "";

	/* count size total */
	size = (_strlen(s1) + _strlen(s2) + 1);

	/* malloc */
	dst = (char *) malloc(size * sizeof(char));

	if (dst == 0)
	{
		return (NULL);
	}

	/* concatenate arrays */
	for (i = 0; *(s1 + i) != '\0'; i++)
		*(dst + i) = *(s1 + i);

	for (j = 0; *(s2 + j) != '\0'; j++)
	{
		*(dst + i) = *(s2 + j);
		i++;
	}
	dst[i] = '\0';
	free(dst);

	return (dst);
}
