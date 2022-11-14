#ifndef CUSTOM_H
#define CUSTOM_H

/**
 * _getline - gets the next line of input from STDIN
 */
/* Helper function definition */

ssize_t _getline(char **lineptr, size_t *n)
{
	ssize_t nread;

	nread = getline(lineptr, n, stdin);
	if (nread == -1)
	{
		free_malloc(*lineptr, NULL);
		exit(EXIT_FAILURE);
	}
	if (**lineptr == '\n')
		return (-1);

	return (nread);
}

/**
 * slice - a function that slices a string
 * @str: the string to slice
 * @delim: the delimiter to slice the string with
 *
 * Return: return an array of the sliced string
 */
char **slice(char *str, char *delim)
{
	int array_size = 1, j;
	char **array, **tmp, *var, *str_var = malloc_str(str);

	array = malloc(sizeof(char *) * array_size);
	array[0] = NULL;
	for (var = strtok(str_var, delim); var != NULL; var = strtok(NULL, delim))
	{
		tmp = array;
		array = malloc(sizeof(char *) * (++array_size));
		for (j = 0; tmp[j] != NULL; ++j)
			array[j] = tmp[j];
		array[j] = var;
		array[j + 1] = NULL;
		free(tmp);
	}

	return (array);
}

/**
 * key_finder - a function that finds a key in a array of maps
 * @env: the array of maps
 * @find: the key to find
 *
 * Return: return an array of the key's value
 */
char *key_finder(char **env, char *find)
{
	char *key, *value;
	int i = 0;

	while (env[i] != NULL)
	{
		key = strtok(env[i], "=");
		if ((_strcmp(key, find)) == 0)
		{
			value = strtok(NULL, "=");
			break;
		}
		++i;
		if (env[i] == NULL)
			return (NULL);
	}
	return (value);
}

#endif /* CUSTOM_H */

