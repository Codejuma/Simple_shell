#include "main.h"
/**
 * _split_string - funct that split tks
 * @s: the str sep
 * @sp: the separt
 * Return: array of str
 */
char **_split_string(char *s, char sp)
{
	int size = TOK_BUFSIZE, i = 0;
	char *tkns = _calloc(sizeof(char *), size);
	char *tkn;

	if (s == NULL || tkns == NULL)
		return (NULL);

	tkn = _strchr(s, sp); /* Find the first separator */
	while (tkn != NULL)
	{
		*tkn = '\0'; /* Null-terminate the token */
		tkns[i] = s; /* Assign the token to array */
		i++;

		if (i >= size)
		{
			size += TOK_BUFSIZE;
			tkns = _realloc(tkns, sizeof(char *) * size);
			if (tkns == NULL)
			{
				perror("Error allocating memory");
				return (NULL);
			}
		}
		s = tkn + 1; /* Move to next token */
		tkn = strchr(s, sp); /* Find the next separator */
	}
	tkns[i] = s; /* assign the last token */
	tkns[i + 1] = NULL; /* Null-terminate the array */

	return (tkns);
}
/**
 * _which - funct of the path
 * @fdp: the pth passed
 * Return: the path
 */
char **_which(char *fdp)
{
	if (fdp == NULL)
		return (NULL);

	return (_split_string(fdp, ':'));
}
/**
 * child_process - func execute the path
 * @args: the comm ex
 * @env: the environ var
 * @status_main: status var
 * @av: prog name
 * @cnt: the prompt cnt
 * Return: 1
 */
int child_process(char **av, char **args, char **env, int status_main, int cnt)
{
	pid_t pid;
	int status;

	if (args == NULL)
		return (-1);

	pid = fork();
	if (pid < 0)
	{
		perror("./hsh: ");
		exit(1);
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		{
			_error(av[0], cnt, args[0]);
			free(args);
			exit(1);
		}
		exit(0);
	}
	else
	{
		if (status_main == 1)
			free(args[0]);
		free(args);
		waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}
/**
 * search_path - funct gets the apth
 * @environ: var environment
 * Return: tkn path
 */
char **search_path(char **environ)
{
	int j = 0;
	char **tkn_pt;

	for (; environ[j] != NULL ; j++)
	{
		if (environ[j][0] == 'P' && environ[j][2] == 'T')
		{
			tkn_pt = _which(environ[j]);
		}
	}
	return (tkn_pt);
}
