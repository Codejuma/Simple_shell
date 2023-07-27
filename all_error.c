#include "main.h"
/*
 * handle_signal - funct new line
 * @sig: the signal name
 */
void handle_signal(int sig)
{
	char *prompt = {"\n{^_^} "};
	(void) sig;

	write(STDOUT_FILE, prompt, _strlen(prompt));
	fflush(stdout);
}
/**
 * _error - funct of errors
 * @argv: prog name
 * @count: no of prompt
 * @args: command
 * Return: 0
 */
int *_error(char *argv, int count, char *args)
{
	char *num;
	
	num = _itoa(count, 10);

	write(2, argv, _strlen(argv));
	write(2, ": ", 2);
	write(2, number, _strlen(number));
	write(2, ": ", 2);
	write(2, args, _strlen(args));
	perror(" ");

	return (0);
}
/**
 * _stat - func for status
 * @cmd: ptr with comd
 * @path: loc dir
 * Return: 1
 */
int _stat(char **cmd, char **path)
{
	char *con_s = NULL, *new_con = NULL;
	int cnt;

	struct stat sb;

	if (path == NULL)
	{
		free(path);
		free(cmd);
		return(0);
	}

	for (cnt = 0; path[cnt] != NULL ; cnt++)
	{
		con_s = str_concat(path[cnt], "/");
		new_con = str_concat(con_s, cmd[0]);
		if (stat(new_con, &sb) == 0 && (sb.st_mode & S_IXUSR))
		{
			cmd[0] = new_con;
			free(con_s);
			free(path[0]);
			free(path);
			return (1);
		}
		free(con_s);
		free(new_con);
	}
	free(path[0]);
	free(path);
	return (0);
}
