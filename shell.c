#include "main.h"
#include "prototype.h"
#include "execution.h"
#include "custom.h"
#include "helper.h"

int main(void)
{
	ssize_t nread;
	char *lineptr = NULL, **av = NULL, **fullpath;
	size_t n = 0;
	int wstatus;

	while (1)
	{
		if (isatty(0))
		{
			write(1, "#cisfun$ ", 9);
			nread = _getline(&lineptr, &n);
			if (nread == -1)
				continue;
			av = split(lineptr, 1);
			fullpath = itexist(av);
			if (isbuiltin(av[0]))
				printf("builtin\n");
			else if (fullpath != NULL)
				terminal(&wstatus, fullpath);
			else
				dprintf(STDOUT_FILENO, "%s: No such file\n", av[0]);
		}
		else
		{
			nread = _getline(&lineptr, &n);
			if (nread == -1)
				continue;
			non_terminal(&wstatus, lineptr);
		}
	}
	exit(EXIT_SUCCESS);
}

