#include "main.h"

void execute(char **av);
void terminal(int *wstatus, char **av);
void non_terminal(int *wstatus, char *lineptr);

int main(void)
{
	ssize_t nread;
	char *lineptr = NULL, **av = NULL;
	size_t n = 0;
	int wstatus;

	while (1)
	{
		if (isatty(0))
		{
			write(1, "#cisfun$ ", 9);
			nread = getline(&lineptr, &n, stdin);
			if (nread == -1)
			{
				free_malloc(lineptr, NULL);
				exit(EXIT_FAILURE);
			}
			if (*lineptr == '\n')
				continue;
			av = split(lineptr, 1);
			terminal(&wstatus, av);
		}
		else
		{
			nread = getline(&lineptr, &n, stdin);
			if (nread == -1)
				exit(EXIT_FAILURE);
			if (*lineptr == '\n')
				continue;
			non_terminal(&wstatus, lineptr);
		}
		free_malloc(lineptr, av);
	}
	exit(EXIT_SUCCESS);
}

int isexist(char *lineptr)
{
	char **av = split(lineptr, 1);
	int check = access(av[0], F_OK);

	if (check == 0)
		return (1);
	else
		return (0);
}

void terminal(int *wstatus, char **av)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		execute(av);
	}
	else
	{
		wait(wstatus);
	}
}

void non_terminal(int *wstatus, char *lineptr)
{
	ssize_t nread;
	size_t n = 0, j = 0, i = 0, array_size = 2;
	char **av, **tmp, **array = malloc(sizeof(char *) * array_size);

	array[1] = NULL;
	array[0] = lineptr;
	while ((nread = getline(&lineptr, &n, stdin)) != -1)
	{
		tmp = array;
		array = malloc(sizeof(char *) * (++array_size));
		for (j = 0; tmp[j] != NULL; ++j)
			array[j] = tmp[j];
		array[j] = lineptr;
		array[j + 1] = NULL;
		free(tmp);
	}
	for (i = 0; i < j; ++i)
	{
		av = split(array[i], 1);
		terminal(wstatus, av);
	}
	av = split(array[i], 1);
	execute(av);
}

void execute(char **av)
{
	int exe;

	printf("execute");
	exe = execve(av[0], av, NULL);
	if (exe == -1)
	{
		perror(av[0]);
		exit(EXIT_FAILURE);
	}
}

