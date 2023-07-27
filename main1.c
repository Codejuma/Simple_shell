#include "main.h"
/**
 * main - funct of prompt input
 * @ac: no of args
 * @av: array of args
 * @env: environ var
 * Return: EXIT_SUCCESS
 */
int main(int ac __attribute__((unused)), char **av, char **env)
{
	char *ln;
	char **args, **path;
	int count = 0, status = 0;
	(void) av;
	signal(SIGINT, handle_signal);
	while (1)
	{
		prompt();
		/* read input and return string */
		ln = read_input();
		/* separates string to get command and args */
		args = sparse_str(ln, env);

		if ((_strcmp(args[0], "\n") != 0) && (_strcmp(args[0], "env") != 0))
		{
			count += 1;
			path = search_path(env);
			 /* busca PATH var enviorn */
			status = _stat(args, path);
			child_process(av, args, env, status, count);
		}
		else
		{
			free(args);
		}
		free(ln);
	}
	return (EXIT_SUCCESS);
}
