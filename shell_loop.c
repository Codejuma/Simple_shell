#include "main.h"
/**
 * hsh - main loop
 * @inf: inf struct
 * @av: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int hsh(info_t *inf, char **av)
{
	ssize_t q = 0;
	int builtin_ret = 0;

	while (q != -1 && builtin_ret != -2)
	{
		clear_info(inf);
		if (interactive(inf))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		q = get_input(inf);
		if (q != -1)
		{
			set_inf(inf, av);
			builting_ret = find_builtin(inf);
			if (builtin_ret == -1)
				find_cmd(inf);
		}
		else if (interactive(inf))
			_putchar('\n');
		free_inf(inf, 0);
	}
	write_history(inf);
	free_inf(info, 1);
	if (!interactive(inf) && inf->status)
		exit(inf->status);
	if (builtin_ret == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (builtin_ret);
}
/**
 * find_builtin - finds builtin command
 * @inf: info struct
 *
 * Return: 0 if successiful, 1, on fail,
 * -2 if signal exit()
 */
int find_builtin(info_t *inf)
{
	int j, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", get_envi},
		{"unsetenv", free_envi},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (j = 0; builtintbl[j].type; j++)
		if (_strcmp(inf->argv[0], builtintbl[j].type) == 0)
		{
			inf->line_count++;
			built_in_ret = builtintbl[j].func(inf);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - gets command in path
 * @inf: struct info
 *
 * Return: void
 */
void find_cmd(info_t *inf)
{
	char *p = NULL;
	int j, k;

	inf->path = inf->argv[0];
	if (inf->linecount_flag == 1)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	for (j = 0, k = 0; inf->arg[j]; j++)
		if (!is_delim(inf->arg[j], " \t\n"))
			k++;
	if (!k)
		return;
	p = find_path(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (p)
	{
		inf->p = p;
		fork_cmd(inf);
	}
	else
	{
		if ((interactive(inf) || _getenv(inf, "PATH=")
					|| info->argv[0][0] == '/') && exe_cmd(info, info->argv[0]))
			fork_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_error(inf, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks thread to run cmd
 * @inf: struct inf
 *
 * Return: void
 */
void fork_cmd(info_t *inf)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inf->p, inf->argv, _copyenviron(inf)) == -1)
		{
			free_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(info->status);
			if (inf->status == 126)
				print_error(inf, "Permission denied\n");
		}
	}
}
