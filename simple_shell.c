#include "main.h"
/**
 * hsh - funct shell loop
 * @inf: the par and return inf
 * @avg: arg vector
 * Return: 0 otherwise 1
 */
int hsh(info_t *inf, char **avg)
{
	ssize_t k = 0;
	int j = 0;

	while (k != -1 && j != -2)
	{
		clear_info(inf);
		if (interactive(inf))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		k = get_input(inf);
		if (k != -1)
		{
			set_info(inf, avg);
			j = find_builtin(inf);
			if (j == -1)
				find_cmd(inf);
		}
		else if (interactive(inf))
			_putchar('\n');
		free_info(inf, 0);
	}
	write_history(inf);
	free_info(inf, 1);
	if (!interactive(inf) && inf->status)
		exit(inf->status);
	if (j == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (j);
}
/**
 * find_builtin - funct find builtin coms
 * @inf: the par and str
 * Return: -1 , 0, 1 and 2
 */
int find_builtin(info_t *inf)
{
	int i, j = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(inf->argv[0], builtintbl[i].type) == 0)
		{
			inf->line_count++;
			j = builtintbl[i].func(inf);
			break;
		}
	return (j);
}
/**
 * find_cmd - func to find PATH
 * @inf: the par and struc
 * Return: nothing
 */
void find_cmd(info_t *inf)
{
	char *path = NULL;
	int i, j;

	inf->path = inf->argv[0];
	if (inf->linecount_flag == 1)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	for (i = 0, j = 0; inf->arg[i]; i++)
		if (!is_delim(inf->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = find_path(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		fork_cmd(inf);
	}
	else
	{
		if ((interactive(inf) || _getenv(inf, "PATH=") ||
	inf->argv[0][0] == '/') && is_cmd(inf, inf->argv[0]))
			fork_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_error(inf, "not found\n");
		}
	}
}
/**
 * fork_cmd - funct that forks
 * @inf: the par struct
 * Return: nothing
 */
void fork_cmd(info_t *inf)
{
	pid_t c_pid;

	c_pid = fork();
	if (c_pid == -1)
	{
		/* TODO: Put error func */
		perror("Error:");
		return;
	}
	if (c_pid == 0)
	{
		if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
		{
			free_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/*TODO: Put error function */
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_error(inf, "Permission denied\n");
		}
	}
}

