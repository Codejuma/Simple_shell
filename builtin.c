#include "main.h"
/**
 * _myexit - exit my shell
 * @inf: stuct containing argument
 * Return: 0 if info.argv[0] != exit
 */
int _myexit(info_t *inf)
{
	int exck;

	if (inf->argv[1]) /* If there is an exit arguement */
	{
		exck = _erratoi(inf->argv[1]);
		if (exck == -1)
		{
			inf->status = 2;
			print_error(inf, "Illegal number: ");
			_eputs(inf->argv[1]);
			_putchar('\n');
			return (1);
		}
		inf->err_num = _erratoi(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes current directory
 * @inf: struct containing info
 *
 * Return: Always 0
 */
int _mycd(info_t *inf)
{
	char *str, *dirr, buffer[1024];
	int chdir_ret, access_ret;

	str = getcwd(buffer, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		dirr = _getenv(inf, "HOME=");
		if (!dirr)
			chdir_ret = /* TODO: what should this be? */
				chdir((dirr = _getenv(inf, "PWD=")) ? dirr : "/");
		else
			chdir_ret = chdir(dirr);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dirr = _getenv(inf, "OLDPWD=")) ? dirr : "/");
	}
	else
		chdir_ret = chdir(inf->argv[1]);
	if (chdir_ret == -1)
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
 * _myhelp - displays help
 * @inf: Struct containing information
 *
 * Return: always 0
 */
int _myhelp(info_t *inf)
{
	char **arg_ray;

	arg_ray = inf->argv;
	_puts("help works. Function to be implemented \n");
	if (0)
		_puts(*arg_ray); /* temp att_unused workaround */
	return (0);
}
