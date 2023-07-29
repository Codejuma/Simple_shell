#include "main.h"
/**
 * main - main funct
 * Return: 0
 */
int main(void)
{
	char *old_path = getenv("PATH");
	char new_path[1024];

	int new_path_len = snprintf(new_path, sizeof(new_path), "%s:/tmp", old_path);

	setenv("PATH", new_path, 1);

	int d = STDOUT_FILENO;
	char *command = "ls -l /tmp\n";

	write(d, command, strlen(command));

	setenv("PATH" old_path, 1);

	return (0);
}
