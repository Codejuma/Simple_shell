#include "main.h"
/**
 * _erratoi - funct str int
 * @str: string converted
 * Return: 0 no str onteriwse -1
 */
int _erratoi(char *str)
{
	int j = 0;
	unsigned long int rels = 0;

	if (*str == '+')
		str++; /* TODO: why does this make main return 255? */
	for (j = 0; str[j] != '\0'; j++)
	{
		if (str[j] >= '0' && str[j] <= 9)
		{
			rels *= 10;
			rels += (str[j] - '0');
			if (rels > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rels);
}
/**
 * print_error - print the erro msg
 * @inf: the para and struct
 * @stre: str having error
 * Return: 0 if no str other -1
 */
void print_error(info_t *inf, char *stre)
{
	_eputs(inf->fname);
	_eputs(": ");
	print_d(inf->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->argv[0]);
	_eputs(": ");
	_eputs(stre);
}
/**
 * print_d - func print dec to bs 10
 * @j: the input
 * @k: the file descriptor
 * Return: no of char
 */
int print_d(int j, int k)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int abs, current;

	if (k == STDERR_FILENO)
		__putchar = _eputchar;
	if (j < 0)
	{
		abs = -j;
		__putchar('-');
		count++;
	}
	else
		abs = j;
	current = abs;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}
/**
 * convert_number - func converter
 * @num: no used
 * @base: bs
 * @flags: args
 * Return: str
 */
char *convert_number(long int num, int base, int flags)
{
	static char *arry;
	static char buffer[100];
	char sign = 0;
	char *pr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	arry = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pr = &buffer[99];
	*pr = '\0';

	do {
		*--pr = arry[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--pr = sign;
	return (pr);
}
/**
 * remove_comments - func replace first '#' with '\0'
 * @buf: str addres
 * Return: 0
 */
void remove_comments(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}
