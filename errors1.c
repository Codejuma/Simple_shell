#include "main.h"
/**
 * _erratoi - converts string to integer
 * @str: string
 * Return: 0 if no number in string, otherwise -1
 */
int _erratoi(char *str)
{
	int j = 0;
	unsigned long result = 0;

	if (*str == '+')
		str++;
	for (j = 0; str[j] != '\0'; j++)
	{
		if (str[j] >= '0' && str[j] <= '9')
		{
			result *= 10;
			result += (str[j] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints the error msg
 * @inf: info struct
 * @es: string
 * Return: 0 if no numbers, otherwise -1
 */
void print_error(info_t *inf, char *es)
{
	_eputs(inf->fname);
	_eputs(": ");
	print_d(inf->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->argv[0]);
	_eputs(": ");
	_eputs(es);
}

/**
 * print_d - printsa decimal
 * @ip: input
 * @fd: filedescriptor
 *
 * Return: character to be printed
 */
int print_d(int ip, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (ip < 0)
	{
		_abs_ = -ip;
		__putchar('-');
		count++;
	}
	else
		_abs_ = ip;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			count++;
		}
		current %= j;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converts numbers
 * @n: number
 * @b: base
 * @flgs: argument flags
 *
 * Return: string
 */
char *convert_number(long int n, int b, int flgs)
{
	static char *arry;
	static char buffer[50];
	char sign = 0;
	char *p;
	unsigned long i = n;

	if (!(flgs & CONVERT_UNSIGNED) && n < 0)
	{
		i = -n;
		sign = '-';
	}

	arry = flgs & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buffer[49];
	*p = '\0';

	do	{
		*--p = arry[i % b];
		i /= b
	} while (i != 0);

	if (sign)
		*--p = sign;
	return (p);
}
/**
 * remove_comments - replaces '#' with '\0'
 * @buf: string address
 *
 * Return: Always 0
 */
void remove_comments(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		i}
}
