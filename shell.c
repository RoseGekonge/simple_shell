#include "main.h"

/* global variable for ^C handling */
unsigned int flag;

/**
 * for_sig - handles ^C signal interupt
 * @uuv: unused variable (required for signal function prototype)
 *
 * Return: void
 */
static void for_sig(int uuv)
{
	(void) uuv;
	if (flag == 0)
		_putstr("\n$ ");
	else
		_putstr("\n");
}

/**
 * main - main function for the shell
 * @argc: number of arguments passed to main
 * @argv: array of arguments passed to main
 * @environment: array of environment variables
 *
 * Return: 0 or exit status, or ?
 */
int main(int argc __attribute__((unused)), char **argv, char **environ)
{
	size_t l = 0;
	unsigned int _ispipe = 0, i;
	env_t vars = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	vars.argv = argv;
	vars.en = create_env(environ);
	signal(SIGINT, for_sig);
	if (!isatty(STDIN_FILENO))
		_ispipe = 1;
	if (_ispipe == 0)
		_putstr("$ ");
	flag = 0;
	while (getline(&(vars.arr), &l, stdin) != -1)
	{
		flag = 1;
		vars.len++;
		vars.lines = split_line(vars.arr, ";");
		for (i = 0; vars.lines && vars.lines[i] != NULL; i++)
		{
			vars.av = split_line(vars.lines[i], "\n \t\r");
			if (vars.av && vars.av[0])
				if (check_for_builtins(&vars) == NULL)
					_ispath(&vars);
			free(vars.av);
		}
		free(vars.arr);
		free(vars.lines);
		flag = 0;
		if (_ispipe == 0)
			_putstr("$ ");
		vars.arr = NULL;
	}
	if (_ispipe == 0)
		_putstr("\n");
	_freeEnv(vars.en);
	free(vars.arr);
	exit(vars.status);
}
