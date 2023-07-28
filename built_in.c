#include "main.h"
/**
 * _myexit - return exits
 * @inf: struc args
 * Return: return exit 0
 */
int _myexit(info_t *inf)
{
	int i;

	if (inf->argv[1]) /* if there is exit arg */
	{
		i = _erratoi(inf->argv[1]);
		if (i == -1)
		{
			inf->status = 2;
			print_error(inf, "Illegal number: ");
			_eputs(inf->argv[1]);
			_eputchar('\n');
			return (1);
		}
		inf->err_num = _erratoi(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}
/**
 * _mycd - func the chage cur pro
 * @inf: struc the args
 * Return: 0
 */
int _mycd(info_t *inf)
{
	char *s, *dirr, buffer[1024];
	int j;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		dirr = _getenv(inf, "HOME=");
		if (!dirr)
			j = /* TODO: what should this be? */
				chdir((dirr = _getenv(inf, "PWD=")) ? dirr : "/");
		else
			j = chdir(dirr);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
		j = /* TODO: what should this be? */
			chdir((dirr = _getenv(inf, "OLDPWD=")) ? dirr : "/");
	}
	else
		j = chdir(inf->argv[1]);
	if (j == -1)
	{
		print_error(inf, "can't cd to ");
		_eputs(inf->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * _myhelp - func that dr
 * @inf: the strcu args
 * Return: 0
 */
int _myhelp(info_t *inf)
{
	char **ag_ary;

	ag_ary = inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*ag_ary); /* temp att_unused workaround */
	return (0);
}


