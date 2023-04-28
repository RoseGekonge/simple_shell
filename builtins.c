#include "main.h"

/**
 * check_for_builtins - checks if the command is a builtin
 * @r: variables
 *
 * Return: pointer to the function or NULL
 */
void (*check_for_builtins(env_t *r))(env_t *r)
{
	unsigned int n;
	builtins_t list[] = {
		{"exit", _exit_},
		{"env", for_env},
		{"setenv", put_env},
		{"unsetenv", del_env},
		{NULL, NULL}
	};

	for (n = 0; list[n].f != NULL; n++)
	{
		if (_strcmpr(r->av[0], list[n].name) == 0)
			break;
	}
	if (list[n].f != NULL)
		list[n].f(r);
	return (list[n].f);
}

/**
 * _exit_ - exit program
 * @r: variables
 *
 * Return: void
 */
void _exit_(env_t *r)
{
	int s;

	if (_strcmpr(r->av[0], "exit") == 0 && r->av[1] != NULL)
	{
		s = for_atoi(r->av[1]);
		if (s == -1)
		{
			r->status = 2;
			write_error(r, ": Illegal number: ");
			print_strII(r->av[1]);
			print_strII("\n");
			free(r->lines);
			r->lines = NULL;
			return;
		}
		r->status = s;
	}
	free(r->arr);
	free(r->av);
	free(r->lines);
	_freeEnv(r->en);
	exit(r->status);
}

/**
 * for_env - prints the current environment
 * @r: struct of variables
 *
 * Return: void.
 */
void for_env(env_t *r)
{
	unsigned int n;

	for (n = 0; r->en[n]; n++)
	{
		_putstr(r->en[n]);
		_putstr("\n");
	}
	r->status = 0;
}

/**
 * put_env - create a new environment variable, or edit an existing variable
 * @r: pointer to struct of variables
 *
 * Return: void
 */
void put_env(env_t *r)
{
	char **f;
	char *g;

	if (r->av[1] == NULL || r->av[2] == NULL)
	{
		write_error(r, ": Incorrect number of arguments\n");
		r->status = 2;
		return;
	}
	f = find_envvar(r->en, r->av[1]);
	if (f == NULL)
		new_envvar(r);
	else
	{
		g = create_envvarstr(r->av[1], r->av[2]);
		if (g == NULL)
		{
			write_error(r, NULL);
			free(r->arr);
			free(r->lines);
			free(r->av);
			_freeEnv(r->en);
			exit(127);
		}
		free(*f);
		*f = g;
	}
	r->status = 0;
}

/**
 * del_env - remove an environment variable
 * @r: pointer to a struct of variables
 *
 * Return: void
 */
void del_env(env_t *r)
{
	char **f, **var;

	unsigned int n, k;

	if (r->av[1] == NULL)
	{
		write_error(r, ": Incorrect number of arguments\n");
		r->status = 2;
		return;
	}
	f = find_envvar(r->en, r->av[1]);
	if (f == NULL)
	{
		write_error(r, ": No variable to unset");
		return;
	}
	for (n = 0; r->en[n] != NULL; n++)
		;
	var = malloc(sizeof(char *) * n);
	if (var == NULL)
	{
		write_error(r, NULL);
		r->status = 127;
		_exit_(r);
	}
	for (n = 0; r->en[n] != *f; n++)
		var[n] = r->en[n];
	for (k = n + 1; r->en[k] != NULL; k++, n++)
		var[n] = r->en[k];
	var[n] = NULL;
	free(*f);
	free(r->en);
	r->en = var;
	r->status = 0;
}
