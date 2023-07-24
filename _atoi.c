#include "main.h"
/**
 * interactive - the function returns true if interactive
 * @inf: the address structure
 * Return: 1 otherwise 0
 */
int interactive(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}
/**
 * is_delim - function that sees the char delim
 * @b: the character checked
 * @del: the string checked
 * Return: 1 otherwise 0
 */
int is_delim(char b, char *del)
{
	while (*del)
		if (*del++ == b)
			return (1);
	return (0);
}
/**
 * _isalpha - function for alphabetic cha
 * @b: char to input
 * Return: 1 otherwise 0
 */
int _isalpha(int b)
{
	if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * _atoi - the funct converting str to int
 * @str: the str converted
 * Return: converted no
 */
int _atoi(char *str)
{
	int j, sign = 1, flag = 0, output;
	unsigned int resl = 0;

	for (j = 0; str[j] != '\0' && flag != 2; j++)
	{
		if (str[j] == '-')
			sign *= -1;

		if (str[j] >= '0' && str[j] <= '9')
		{
			flag = 1;
			resl *= 10;
			resl += (str[j] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -resl;
	else
		output = resl;

	return (output);
}
