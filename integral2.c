#include "main.h"

/**
 * new_envvar - create a new environment variable
 * @r: pointer to struct of variables
 *
 * Return: void
 */
void new_envvar(env_t *r)
{
	unsigned int b;
	char **str;

	for (b = 0; r->en[b] != NULL; b++)
		;
	str = malloc(sizeof(char *) * (b + 2));
	if (str == NULL)
	{
		write_error(r, NULL);
		r->status = 127;
		_exit_(r);
	}
	for (b = 0; r->en[b] != NULL; b++)
		str[b] = r->en[b];
	str[b] = create_envvarstr(r->av[1], r->av[2]);
	if (str[b] == NULL)
	{
		write_error(r, NULL);
		free(r->arr);
		free(r->lines);
		free(r->av);
		_freeEnv(r->en);
		free(str);
		exit(127);
	}
	str[b + 1] = NULL;
	free(r->en);
	r->en = str;
}

/**
 * find_envvar - finds an environment variable
 * @en: array of environment variables
 * @y: environment variable to find
 *
 * Return: pointer to address of the environment variable
 */
char **find_envvar(char **en, char *y)
{
	unsigned int b, a, count;

	count = str_len(y);
	for (b = 0; en[b] != NULL; b++)
	{
		for (a = 0; a < count; a++)
			if (y[a] != en[b][a])
				break;
		if (a == count && en[b][a] == '=')
			return (&en[b]);
	}
	return (NULL);
}

/**
 * create_envvarstr - create a new environment variable string
 * @y: variable name
 * @v: variable value
 *
 * Return: pointer to the new string;
 */
char *create_envvarstr(char *y, char *v)
{
	unsigned int a, b, r, k;
	char *str;

	a = str_len(y);
	b = str_len(v);
	str = malloc(sizeof(char) * (a + b + 2));
	if (str == NULL)
		return (NULL);
	for (r = 0; y[r] != '\0'; r++)
		str[r] = y[r];
	str[r] = '=';
	for (k = 0; v[k] != '\0'; k++)
		str[r + 1 + k] = v[k];
	str[r + 1 + k] = '\0';
	return (str);
}

/**
 * for_atoi - converts a string into an integer
 * @arr: string to convert
 *
 * Return: the integer value, or -1 if an error occurs
 */
int for_atoi(char *arr)
{
	unsigned int n, num;
	int x = 0, trial;

	trial = INT_MAX;
	for (num = 0; trial != 0; num++)
		trial /= 10;
	for (n = 0; arr[n] != '\0' && n < num; n++)
	{
		x *= 10;
		if (arr[n] < '0' || arr[n] > '9')
			return (-1);
		if ((n == num - 1) && (arr[n] - '0' > INT_MAX % 10))
			return (-1);
		x += arr[n] - '0';
		if ((n == num - 2) && (arr[n + 1] != '\0') && (x > INT_MAX / 10))
			return (-1);
	}
	if (n > num)
		return (-1);
	return (x);
}
