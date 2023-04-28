#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

/**
 * struct vars - variables
 * @av: command line arguments
 * @arr: buffer of command
 * @en: environment variables
 * @len: count of commands entered
 * @argv: arguments at opening of shell
 * @status: exit status
 * @lines: double pointer to commands
 */
typedef struct vars
{
	char **av;
	char *arr;
	char **en;
	size_t len;
	char **argv;
	int status;
	char **lines;
} env_t;

/**
 * struct builtins - struct for the builtin functions
 * @name: name of builtin command
 * @f: function for corresponding builtin
 */
typedef struct builtins
{
	char *name;
	void (*f)(env_t *);
} builtins_t;

char **create_env(char **en);
void _freeEnv(char **en);
ssize_t _putstr(char *arr);
char *_strcp(char *str);
int _strcmpr(char *s1, char *s2);
char *str_cat(char *str1, char *str2);
unsigned int str_len(char *arr);
char **split_line(char *arr, char *delim);
char **_realloc_(char **r, size_t *bit);
char *for_strtok(char *arr, const char *delim);
void (*check_for_builtins(env_t *r))(env_t *r);
void _exit_(env_t *r);
void for_env(env_t *r);
void put_env(env_t *r);
void del_env(env_t *r);
void new_envvar(env_t *r);
char **find_envvar(char **en, char *g);
char *create_envvarstr(char *g, char *val);
int for_atoi(char *arr);
void _ispath(env_t *r);
int _execvepath(char *line, env_t *r);
char *for_path(char **env);
int _execvecwd(env_t *r);
int _isdir(char *arr);
void write_error(env_t *r, char *k);
void print_strII(char *arr);
char *_uitoa(unsigned int len);

#endif
