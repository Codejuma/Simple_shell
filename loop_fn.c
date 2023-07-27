#include "main.h"
/**
 * read_input - The func that store stdin
 * Return: str of input
 */
char *read_input(void)
{
	char *line = NULL;
	ssize_t signal;
	size_t bufsize = 0;
	int j;

	signal = getline(&line, &bufsize, stdin);
	if (line)
	{
		perror("Error allocating memory for buffer");
		return (0);
	}
	if (signal == 1)
	{
		free(line);
		return (NULL);
	}
	else if (signal == EOF)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		free(line);
		exit(0);
	}
	else
	{
		for (j = 0; line[j] == ' ' && line[j + 1] == ' ' ; j++)
			;
		if (!line[j] && line[j + 1] == '\n')
		{
			free(line);
			return (0);
		}
	}
	return (line);
}
/**
 * sparse_str - funct divide str to array
 * @line: str sep
 * @env: envrion var
 * Return: token othewise NULL
 */
char **sparse_str(char *line, char **env)
{
	int bufsize = TOK_BUFSIZE;
	int i = 0;
	char **tokens;
	char *token;
	char *delim = " \t\r\n\v\f"; /* delimeter chars */
	char *end;
	size_t token_len = 0;

	if (line == NULL)
	{
		return (NULL);
	}
	tokens = calloc(sizeof(char *), bufsize);
	if (!tokens)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}

	token = line;
	while (*token)
	{
		/* skip leading delimiters */
		while (*token && strchr(delim, *token))
			token++;

		if (!*token) /* end of str */
			break;

		/* Find the end of token */

		while (*end && !strchr(delim, *end))
			end++;

		/* copy the token to the tokens array */

		tokens[i] = calloc(token_len + 1, sizeof(char));
		if (!tokens[i])
		{
			perror("error");
			exit(EXIT_FAILURE);
		}
		strncpy(tokens[i], token, token_len);
		tokens[i][token_len] = '\0';

		i++;

		/* resize tokens array if needed */
		if (i >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("error");
				exit(EXIT_FAILURE);
			}
		}
		token = end; /* move to next token */
	}

	if (tokens[0] == NULL)
		tokens[i] = "\n"; /* if it is null new line */
	/* compares the token[0] */
	if ((strcmp(tokens[0], "exit") == 0) && tokens[1] == NULL)
	{
		free(line); /* free memory */
		free(tokens);
		exit(0);
	}
	if ((strcmp(tokens[0], "env") == 0) && tokens[1] == NULL)
		func_printenv(env); /* find the environ */

	return (tokens);
}
/**
 * prompt - function print $
 */
void prompt(void)
{
	char *prompt = {"{^_^} "};
	char *buffer = getcwd(NULL, 0);

	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, prompt, _strlen(prompt));
	}
	free(buffer);
}
