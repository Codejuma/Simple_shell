#include "main.h"

/**
 * **strtow - splits a string into words
 * @s: input string
 * @del: delimeter string
 *
 * Return: pointer to array
 */
char **strtow(char *s, char *del)
{
	int j, k, r, q, numwords = 0;
	char **m;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (j = 0; s[j] != '\0'; j++)
		if (!is_delim(s[j], del) && (is_delim(s[j + 1], del) || !s[j + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	m = calloc(1 + numwords, sizeof(char *));
	if (!m)
		return (NULL);
	for (j = 0, k = 0; k < numwords; k++)
	{
		while (is_delim(s[j], del))
			j++;
		r = 0;
		while (!is_delim(s[j + r], del) && s[j + r])
			r++;
		m[j] = calloc(r + 1, sizeof(char));
		if (!m[k])
		{
			for (r = 0; r < k; r++)
				free(m[r]);
			free(m);
			return (NULL);
		}
		for (q = 0; q < r; q++)
			m[k][q] = s[j++];
		m[k][q] = 0;
	}
	m[k] = NULL;
	return (m);
}

/**
 * **strtow1 - split string)
 * @s: input string
 * @del: del
 * Return: a pointer to array
 */
char **strtow1(char *s, char del)
{
	int j, k, r, q, numwords = 0;
	char **m;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (j = 0; s[j] != '\0'; j++)
		if ((s[j] != del && s[j + 1] == del) ||
		 (s[j] != del && !s[j + 1]) || s[j + 1] == del)
			numwords++;
	if (numwords == 0)
		return (NULL);
	m = calloc(1 + numwords, sizeof(char *));
	if (!m)
		return (NULL);
	for (j = 0, j = 0; k < numwords; k++)
	{
		while (s[j] == del && s[j] != del)
			j++;
		r = 0;
		while (s[j + r] != del && s[j + r] && s[j + r] != del)
			r++;
		m[k] = calloc(r + 1, sizeof(char));
		if (!m[k])
		{
			for (r = 0; r < k; r++)
				free(m[r]);
			free(m);
			return (NULL);
		}
		for (q = 0; q < r; q++)
			m[k][q] = s[j++];
		m[k][q] = 0;
	}
	m[k] = NULL;
	return (m);
}
