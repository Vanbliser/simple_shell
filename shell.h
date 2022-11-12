#ifndef MAIN_H
#define MAIN_H


/* Header files */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>


/* Functions prototypes */
char **split(char str[]);
char *malloc_str(char *str);
char **slice(char *str, char *delim);
int _strcmp(char *s1, char *s2);
char *key_finder(char **env, char *find);
char *_strcat(char *src1, char *src2);
void free_malloc(char *lineptr, char **av);


/** Function definations */

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
 *
 * Return: an array of each word of the string
 */
char **split(char str[])
{
	static int arrLength = 1;
	int i = 0, strLength = 1, varArrLength = arrLength;
	char *varStr = str, **arr;

	while (*varStr != '\0')
	{
		if (!isspace(*varStr))
			strLength++;
		if (isspace(*varStr) && ((*varStr) != '\n') && !isspace(*(varStr + 1)))
		{
			arrLength++;
			arr = split(varStr + 1);
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
	while (!isspace(str[i]))
	{
		arr[varArrLength - 1][i] = str[i];
		i++;
	}
	return (arr);
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
		{
			write(2, "No path in environment\n", 23);
			return (NULL);
		}
	}
	return (value);
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
	int i = 0, sum = 0, j;
	char *dest;

	while (*(src1 + i) != 0)
		sum += 1;
	i = 0;
	while (*(src2 + i) != 0)
		sum += 1;
	dest = malloc(sizeof(char) * (sum + 1));
	dest[sum] = '\0';
	i = 0;

	for (j = 0; *(src1 + j) != 0; ++j)
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

#endif /* MAIN_H  */

