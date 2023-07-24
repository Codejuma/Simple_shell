#include "main.h"
/**
 * **strtow - func that split str into word
 * @s: the str input
 * @del: delimetr str
 * Return: return ptr to an arry of str
 */
char **strtow(char *s, char *del)
{
	int a,  b, g, n, nword;
	char **st;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (a = 0; s[a] != '\0'; a++)
		if (!is_delim(s[a], del) && (is_delim(s[a + 1], del) || !s[a + 1]))
			nword++;
	if (nword == 0)
		return (NULL);
	st = malloc((1 + nword) * sizeof(char *));
	if (!st)
		return (NULL);
	for (a = 0, b = 0; b < nword; b++)
	{
		while (is_delim(s[a], del))
			a++;
		g = 0;
		while (!is_delim(s[a + g], del) && s[a + g])
			g++;
		st[b] = malloc((g + 1) * sizeof(char));
		if (!st[b])
		{
			for (g = 0; g < b; g++)
				free(st[g]);
			free(st);
			return (NULL);
		}
		for (n = 0; n < g; n++)
			st[b][n] = s[a++];
		st[b][n] = 0;
	}
	st[b] = NULL;
	return (st);
}
/**
 * **strtow2 - func split str to word
 * @s: the str imput
 * @del: the delim
 * Return: return ptr array str
 */
char **strtow2(char *s, char del)
{
	int a, b, g, n, nword;
	char **st;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (a = 0; s[a] != '\0'; a++)
		if ((s[a] != del && s[a + 1] == del) ||
	(s[a] != del && !s[a + 1]) || s[a + 1] == del)
			nword++;
	if (nword == 0)
		return (NULL);
	st = malloc((1 + nword) * sizeof(char *));
	if (!st)
		return (NULL);
	for (a = 0, b = 0; b < nword; b++)
	{
		while (s[a] == del && s[a] != del)
			a++;
		g = 0;
		while (s[a + g] != del && s[a + g] && s[a + g] != del)
			g++;
		st[b] = malloc((g + 1) * sizeof(char));
		if (!st[b])
		{
			for (g = 0; g < b; g++)
				free(st[g]);
			free(st);
			return (NULL);
		}
		for (n = 0; n < g; n++)
			st[b][n] = s[a++];
		st[a][n] = 0;
	}
	st[b] = NULL;
	return (st);
}
