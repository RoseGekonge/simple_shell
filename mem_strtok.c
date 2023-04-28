#include "main.h"

/**
 * _realloc_ - reallocates a pointer to double the space
 * @r: pointer to the old array
 * @bit: pointer to number of elements in the old array
 *
 * Return: pointer to the new array
 */

char **_realloc_(char **r, size_t *bit)
{
	char **strs;
	size_t c;

	strs = malloc(sizeof(char *) * ((*bit) + 10));
	if (strs == NULL)
	{
		free(r);
		return (NULL);
	}
	for (c = 0; c < (*bit); c++)
	{
		strs[c] = r[c];
	}
	*bit += 10;
	free(r);
	return (strs);
}

/**
 * search_char - checks if a character matches any in a string
 * @letter: character to check
 * @arr: string to check
 *
 * Return: 1 if match, 0 if not
 */

unsigned int search_char(char letter, const char *arr)
{
	unsigned int c;

	for (c = 0; arr[c] != '\0'; c++)
	{
		if (letter == arr[c])
			return (1);
	}
	return (0);
}

/**
 * for_strtok - custom strtok
 * @arr: string to tokenize
 * @delim: delimiter to tokenize against
 *
 * Return: pointer to the next token or NULL
 */
char *for_strtok(char *arr, const char *delim)
{
	static char *begin;
	static char *after;
	unsigned int c;

	if (arr != NULL)
		after = arr;
	begin = after;
	if (begin == NULL)
		return (NULL);
	for (c = 0; after[c] != '\0'; c++)
	{
		if (search_char(after[c], delim) == 0)
			break;
	}
	if (after[c] == '\0' || after[c] == '#')
	{
		after = NULL;
		return (NULL);
	}
	begin = after + c;
	after = begin;
	for (c = 0; after[c] != '\0'; c++)
	{
		if (search_char(after[c], delim) == 1)
			break;
	}
	if (after[c] == '\0')
		after = NULL;
	else
	{
		after[c] = '\0';
		after= after + c + 1;
		if (*after == '\0')
			after = NULL;
	}
	return (begin);
}
