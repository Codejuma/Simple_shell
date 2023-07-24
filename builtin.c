#include "main.h"
/**
 * _exit - exit my shell
 * @inf: stuct containing argument
 * Return: 0 if info.argv[0] != exit
 */
int _exit(info_t *inf)
{
	int exitcheck;

	if (inf->argv[1])
	{
		exitcheck = _erratoi(inf->argv[1]);
		if (exitcheck == -1)
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
	inf->err_mum = -1;
	return (-2);
}

/**
 * change_dir - changes current directory
 * @inf: struct containing info
 *
 * Return: Always 0
 */
int change_dir(info_t *inf)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		dir = _getenv(inf, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(inf, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
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
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(inf, "OLDPWD=")) ? dir : "/");
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
 * display_help - displays help
 * @inf: Struct containing information
 *
 * Return: always 0
 */
int display_help(info_t *inf)
{
	char **arg_array;

	arg_array = inf->argv;
	_puts("help works. Function to be implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
