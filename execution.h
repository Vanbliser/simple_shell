#ifndef EXECUTION_H
#define EXECUTION_H

/* Helper function definition */
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
	char **fulpath, **av, **tmp, **array = malloc(sizeof(char *) * array_size);

	array[1] = NULL;
	array[0] = lineptr;
	while ((nread = getline(&lineptr, &n, stdin)) != -1)
	{
		if (*lineptr == '\n')
			break;
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
		fulpath = itexist(av);
		if (isbuiltin(av[0]))
			printf("builtin\n");
		else if (fulpath != NULL)
			terminal(wstatus, fulpath);
		else
			dprintf(STDOUT_FILENO, "%s: No such file\n", av[0]);
	}
	av = split(array[i], 1);
	fulpath = itexist(av);
	if (isbuiltin(av[0]))
		printf("builtin\n");
	else if (fulpath != NULL)
		execute(fulpath);
	else
		dprintf(STDOUT_FILENO, "%s: No such file\n", av[0]);
}

void execute(char **av)
{
	int exe;

	exe = execve(av[0], av, NULL);
	if (exe == -1)
		perror(av[0]);
}

int isbuiltin(char *ar0)
{
	int i;
	char *builtin_cmd[] = {"exit", "env", "setenv", "unsetenv", "cd", NULL};

	for (i = 0; builtin_cmd[i] != NULL; ++i)
		if (_strcmp(builtin_cmd[i], ar0) == 0)
			return (1);
	return (0);
}

char **itexist(char **av)
{
	int check, i = 0;
	char *value, **paths, *fullpath, *concat;
	char root[] = "/";

	if (isbuiltin(av[0]))
	{
		return (NULL);
	}
	else if (av[0][0] == '/')
	{
		check = access(av[0], F_OK);
	}
	else
	{
		value = key_finder(environ, "PATH");
		if (value == NULL)
			return (av);
		paths = slice(value, ":");
		concat = _strcat(root, av[0]);
		while (paths[i] != NULL)
		{
			fullpath = _strcat(paths[i], concat);
			check = access(fullpath, F_OK);
			if (check == 0)
			{
				av[0] = fullpath;
				break;
			}
			++i;
		}
	}
	if (check == 0)
		return (av);
	else
		return (NULL);
}

#endif /* EXECUTION_H */

