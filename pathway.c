#include "main.h"
/**
 * _execvepath - executes a command in the path
 * @line: full path to the command
 * @r: pointer to struct of variables
 *
 * Return: 0 on success, 1 on failure
 */
int _execvepath(char *line, env_t *r)
{
	pid_t child_pid;

	if (access(line, X_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == -1)
			write_error(r, NULL);
		if (child_pid == 0)
		{
			if (execve(line, r->av, r->en) == -1)
				write_error(r, NULL);
		}
		else
		{
			wait(&r->status);
			if (WIFEXITED(r->status))
				r->status = WEXITSTATUS(r->status);
			else if (WIFSIGNALED(r->status) && WTERMSIG(r->status) == SIGINT)
				r->status = 130;
			return (0);
		}
		r->status = 127;
		return (1);
	}
	else
	{
		write_error(r, ": Permission denied\n");
		r->status = 126;
	}
	return (0);
}

/**
 * for_path - finds the PATH variable
 * @en: array of environment variables
 *
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */
char *for_path(char **en)
{
	char *path = "PATH=";
	unsigned int i, j;

	for (i = 0; en[i] != NULL; i++)
	{
		for (j = 0; j < 5; j++)
			if (path[j] != en[i][j])
				break;
		if (j == 5)
			break;
	}
	return (en[i]);
}
/**
 * _ispath - checks if the command is in the PATH
 * @r: variables
 *
 * Return: void
 */
void _ispath(env_t *r)
{
	char *path, *path_dup = NULL, *c = NULL;
	unsigned int a = 0, f = 0;
	char **pt;
	struct stat vars;

	if (_isdir(r->av[0]))
		f = _execvecwd(r);
	else
	{
		path = for_path(r->en);
		if (path != NULL)
		{
			path_dup = _strcp(path + 5);
			pt = split_line(path_dup, ":");
			for (a = 0; pt && pt[a]; a++, free(c))
			{
				c = str_cat(pt[a], r->av[0]);
				if (stat(c, &vars) == 0)
				{
					f = _execvepath(c, r);
					free(c);
					break;
				}
			}
			free(path_dup);
			if (pt == NULL)
			{
				r->status = 127;
				_exit_(r);
			}
		}
		if (path == NULL || pt[f] == NULL)
		{
			write_error(r, ": not found\n");
			r->status = 127;
		}
		free(pt);
	}
	if (f == 1)
		_exit_(r);
}
/**
 * _execvecwd - executes the command in the current working directory
 * @r: pointer to struct of variables
 *
 * Return: 0 on success, 1 on failure
 */
int _execvecwd(env_t *r)
{
	pid_t child_pid;
	struct stat strs;

	if (stat(r->av[0], &strs) == 0)
	{
		if (access(r->av[0], X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
				write_error(r, NULL);
			if (child_pid == 0)
			{
				if (execve(r->av[0], r->av, r->en) == -1)
					write_error(r, NULL);
			}
			else
			{
				wait(&r->status);
				if (WIFEXITED(r->status))
					r->status = WEXITSTATUS(r->status);
				else if (WIFSIGNALED(r->status) && WTERMSIG(r->status) == SIGINT)
					r->status = 130;
				return (0);
			}
			r->status = 127;
			return (1);
		}
		else
		{
			write_error(r, ": Permission denied\n");
			r->status = 126;
		}
		return (0);
	}
	write_error(r, ": not found\n");
	r->status = 127;
	return (0);
}
/**
 * _isdir - checks if the command is a part of a path
 * @arr: command
 *
 * Return: 1 on success, 0 on failure
 */
int _isdir(char *arr)
{
	unsigned int a = 0;

	while (arr[a])
	{
		if (arr[a] == '/')
			return (1);
		a++;
	}
	return (0);
}
