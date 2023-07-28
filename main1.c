#include "main.h"
/**
 * main - entr pt
 * @ac: arg ct
 * @av: arg vc
 * Return: 0 otherwise 1
 */
int main(int ac, char **av)
{
	info_t inf[] = { INFO_INIT };
	int j = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (j)
			: "r" (j));

	if (ac == 2)
	{
		j = open(av[1], O_RDONLY);
		if (j == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->readfd = j;
	}
	populate_env_list(inf);
	read_history(inf);
	hsh(inf, av);
	return (EXIT_SUCCESS);
}
