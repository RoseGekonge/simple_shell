#include "main.h"

/**
 * create_env - make the shell environment from the environment passed to main
 * @en: environment passed to main
 *
 * Return: pointer to the new environment
 */

char **create_env(char **en)
{
	char **k = NULL;
	size_t f;

	for (f = 0; en[f] != NULL; f++)
		;
	k = malloc(sizeof(char *) * (f + 1));
	if (k == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	for (f = 0; en[f] != NULL; f++)
		k[f] = _strcp(en[f]);
	k[f] = NULL;
	return (k);
}

/**
 * _freeEnv - free the shell's environment
 * @en: shell's environment
 *
 * Return: void
 */

void _freeEnv(char **en)
{
	unsigned int b = 0;

	while (en[b] != NULL)
	{
		free(en[b]);
		b++;
	}
	free(en);
}

/**
 * split_line - tokenizes a buffer with a delimiter
 * @arr: buffer to tokenize
 * @delim: delimiter to tokenize along
 *
 * Return: pointer to an array of pointers to the tokens
 */
char **split_line(char *arr, char *delim)
{
	char **miniline = NULL;
	size_t c = 0, x = 10;

	if (arr == NULL)
		return (NULL);
	miniline = malloc(sizeof(char *) * x);
	if (miniline == NULL)
	{
		perror("Fatal Error");
		return (NULL);
	}
	while ((miniline[c] = for_strtok(arr, delim)) != NULL)
	{
		c++;
		if (c == x)
		{
			miniline = _realloc_(miniline, &x);
			if (miniline == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		arr = NULL;
	}
	return (miniline);
}
