#include "main.h"

/**
 * write_error - prints error messages to standard error
 * @r: pointer to struct of variables
 * @k: message to print out
 *
 * Return: void
 */
void write_error(env_t *r, char *k)
{
	char *len;

	print_strII(r->argv[0]);
	print_strII(": ");
	len = _uitoa(r->len);
	print_strII(len);
	free(len);
	print_strII(": ");
	print_strII(r->av[0]);
	if (k)
	{
		print_strII(k);
	}
	else
		perror("");
}

/**
 * print_strII - prints a string to standard error
 * @arr: string to print
 *
 * Return: void
 */
void print_strII(char *arr)
{
	ssize_t digit, x;

	digit = str_len(arr);
	x = write(STDERR_FILENO, arr, digit);
	if (x != digit)
	{
		perror("Fatal Error");
		exit(1);
	}

}

/**
 * _uitoa - converts an unsigned int to a string
 * @len: unsigned int to convert
 *
 * Return: pointer to the converted string
 */
char *_uitoa(unsigned int len)
{
	char *arrofnum;
	unsigned int p, z;

	p = len;
	for (z = 0; p != 0; z++)
		p /= 10;
	arrofnum = malloc(sizeof(char) * (z + 1));
	if (arrofnum == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	arrofnum[z] = '\0';
	for (--z; len; --z)
	{
		arrofnum[z] = (len % 10) + '0';
		len /= 10;
	}
	return (arrofnum);
}
