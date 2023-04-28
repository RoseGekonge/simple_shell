#include "main.h"

/**
 * _putstr - writes a string to standard output
 * @arr: string to write
 *
 * Return: number of chars printed or -1 on failure
 */
ssize_t _putstr(char *arr)
{
	ssize_t digit, count;

	digit = str_len(arr);
	count = write(STDOUT_FILENO, arr, digit);
	if (count != digit)
	{
		perror("Fatal Error");
		return (-1);
	}
	return (count);
}

/**
 * _strcp - returns pointer to new mem alloc space which contains copy
 * @str: string to be duplicated
 *
 * Return: a pointer to the new duplicated string
 */
char *_strcp(char *str)
{
	char *cp;

	int c, j;

	if (str == 0)
		return (NULL);

	for (c = 0; str[c]; c++)
		;
	cp = malloc((c + 1) * sizeof(char));

	for (j = 0; j <= c; j++)
		cp[j] = str[j];

	return (cp);
}

/**
 * _strcmpr - compares two strings
 * @s1: first string, of two, to be compared in length
 * @s2: second string, of two, to be compared
 * Return: 0 on success, anything else is a failure
 */
int _strcmpr(char *s1, char *s2)
{
	int r = 0;
	while (s1[r] == s2[r])
	{
		if (s1[r] == '\0')
			return (0);
		r++;
	}
	return (s1[r] - s2[r]);
}

/**
 * str_cat - concatenates two strings
 * @str1: first string
 * @str2: second string
 * Return: pointer
 */

char *str_cat(char *str1, char *str2)
{
	char *string;
	unsigned int b, a, count, x, m;

	a = 0;
	b = 0;
	if (str1 == NULL)
		b = 0;
	else
	{
		b = 0;
		while (str1[b])
			b++;
	}
	if (str2 == NULL)
		a = 0;
	else
	{
		a = 0;
		while (str2[a])
			a++;
	}
	count = a + b + 2;
	string = malloc(count * sizeof(char));
	if (string == NULL)
		return (NULL);
	for (x = 0; x < b; x++)
		string[x] = str1[x];
	string[x] = '/';
	for (m = 0; m < a; m++)
		string[x + 1 + m] = str2[m];
	string[a + b + 1] = '\0';
	return (string);
}

/**
 * str_len - returns the length of a string
 * @arr: string to be measured
 * Return: length of string
 */
unsigned int str_len(char *arr)
{
	unsigned int count = 0;

	while (arr[count])
		count++;
	return (count);
}
