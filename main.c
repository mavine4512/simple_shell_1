#include "shell.h"

/**
 * main - the startof the main function
 * @agc: integer input
 * @agv: character input
 * Return: Always 0
 */
int main(int agc, char **agv)
{
	info_t info[] = { INFO_INIT };
	int pd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (pd)
			: "r" (pd));
	if (agc == 2)
	{
		pd = open(agv[1], O_RDONLY);
		if (pd == -1)
		{
			if (errno == EACCES)
			{
				exit(126);
			}
			if (errno == ENOENT)
			{
				_eputs(agv[0]);
				_eputs(": 0: Close ");
				_eputs(agv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->readpd = pd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, agv);
	return (EXIT_SUCCESS);
}
