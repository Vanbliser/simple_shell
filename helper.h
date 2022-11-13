#ifndef HELPER_H
#define HELPER_H

/** Helper function definations */

/**
 * malloc_str - a function duplicates a string into a dynamic memory
 * @str: the string to duplicate
 *
 * Return: returns a pointer to the duplicated string
 */
char *malloc_str(char *str)
{
	int len;
	char *str_var;

	for (len = 0; str[len] != '\0'; ++len)
		;

	str_var = malloc(sizeof(char) * (len + 1));
	str_var[len] = '\0';

	for (len = 0; str[len] != '\0'; ++len)
		str_var[len] = str[len];

	return (str_var);
}

/**
 * split - a function that splits a string and returns an array of each word of
 * the string.
 * @str: the string to print
 * @arrLength: initial length of the array
 *
 * Return: an array of each word of the string
 */
char **split(char *str, int arrLength)
{
	int i = 0, strLength = 1, varArrLength = arrLength;
	char *varStr = str, **arr;

	while (*varStr != '\0')
	{
		if (!isspace(*varStr))
			strLength++;
		if (isspace(*varStr) && !isspace(*(varStr + 1)) && *(varStr + 1) != '\0')
		{
			arrLength++;
			arr = split(varStr + 1, arrLength);
			break;
		}
		varStr++;
	}
	if (*varStr == '\0')
	{
		arr = malloc(sizeof(char *) * (varArrLength + 1));
		if (arr == NULL)
			exit(1);
		arr[varArrLength] = NULL;
	}
	arr[varArrLength - 1] = malloc(sizeof(char) * (strLength + 1));
	while (!isspace(str[i]) && str[i] != '\0')
	{
		arr[varArrLength - 1][i] = str[i];
		i++;
	}
	arr[varArrLength - 1][i] = '\0';
	return (arr);
}

/**
 * _strcmp - a function that compares two strings.
 * @s1: input parameter
 * @s2: input parameter
 *
 * Return: 0 if equal or b if is different
 */
int _strcmp(char *s1, char *s2)
{
	int a = 0;
	int b = 0;

	while (s1[a] != '\0' && b == 0)
	{
		b = s1[a] - s2[a];
		a++;
	}
	return (b);
}

/**
 * _strcat - a function that concatenates two strings
 * @src1: pointer to a string.
 * @src2: pointer to a string.
 *
 * Return: return a pointer to a string
 */
char *_strcat(char *src1, char *src2)
{
	int i, sum = 0, j;
	char *dest;

	for (i = 0; src1[i] != '\0'; ++i)
		sum += 1;
	for (i = 0; src2[i] != '\0'; ++i)
		sum += 1;
	dest = malloc(sizeof(char) * (sum + 1));
	dest[sum] = '\0';
	i = 0;

	for (j = 0; src1[j] != '\0'; ++j)
	{
		*(dest + i) = *(src1 + j);
		++i;
	}
	for (j = 0; *(src2 + j) != 0; ++j)
	{
		*(dest + i) = *(src2 + j);
		++i;
	}
	return (dest);
}

/**
 * free_malloc - a function that frees mallocs
 * @lineptr: pointer to be freed
 * @av: an array of strings to be freed as well as the array
 */
void free_malloc(char *lineptr, char **av)
{
	int i = 0;

	free(lineptr);
	if (av != NULL)
	{
		while (av[i] != NULL)
		{
			free(av[i]);
			i++;
		}
		free(av);
	}
}

#endif /* HELPER_H */

