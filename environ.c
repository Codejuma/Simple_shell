#include "main.h"
extern char **environ;
/**
 * _myenv - function execute env
 * @inf: struct has args
 * Return: 0
 */
int _myenv(info_t *inf)
{
	print_list_str(inf->env);
	return (0);
}
/**
 * _getenv - func the value of env var
 * @inf: struct contains potential args
 * @nam: environ variable nam
 * Return: Return the value
 */
char *_getenv(info_t *inf, const char *nam)
{
	list_t *nodd = inf->env;
	char *s;

	while (nodd)
	{
		s = starts_with(nodd->str, nam);
		if (s && *s)
			return (s);
		nodd = nodd->next;
	}
	return (NULL);
}
/**
 * _mysetenv - funct new env
 * @inf: struct have args
 * Return: 0
 */
int _mysetenv(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs("Incorrent number of arguments\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}
/**
 * _myunsetenv - funct an env var
 * @inf: struct have args
 * Return: 0
 */
int _myunsetenv(info_t *inf)
{
	int j;

	if (inf->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (j = 1; j <= inf->argc; j++)
		_unsetenv(inf, inf->argv[j]);

	return (0);
}
/**
 * populate_env_list - funct env list
 * @inf: str have poten args
 * Return: 0
 */
int populate_env_list(info_t *inf)
{
	list_t *nodd = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&nodd, environ[j], 0);
	inf->env = nodd;
	return (0);
}
