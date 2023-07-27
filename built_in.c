#include "main.h"
/**
 * func_printenv - funct that print env
 * @environ: the var envion
 */
void func_printenv(char **environ)
{
	int j = 0;

	for (; environ[j] ; j++)
		_puts(environ[j]); /* impime TODO el environ */
}
