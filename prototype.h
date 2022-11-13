#ifndef PROTOTYPE_H
#define PROTOTYPE_H

/* Helper function prototypes */

/*a function that splits a string into an array of each word of the string.*/
char **split(char str[], int arrLength);

/*a function duplicates a string into a dynamic memory */
char *malloc_str(char *str);

/*a function that slices a string by the delim into an array of the slices.*/
char **slice(char *str, char *delim);

/*a function that returns 0 if string s1 & s2 are equal, else the difference*/
int _strcmp(char *s1, char *s2);

/*a function that finds a key in a array of maps & returns the value of key*/
char *key_finder(char **env, char *find);

/*a function that concatenates two strings & returns dynamic memory to it*/
char *_strcat(char *src1, char *src2);

/*a function that frees an array of strings(av) malloc & a string(lineptr)*/
void free_malloc(char *lineptr, char **av);

void terminal(int *wstatus, char **av);
void non_terminal(int *wstatus, char *lineptr);
void execute(char **av);
int isbuiltin(char *ar0);
char **itexist(char **av);

ssize_t _getline(char **lineptr, size_t *n);

#endif /* PROTOTYPE_H */

