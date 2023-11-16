#include "shell.h"

/**
 * shell_env - Gets builtin environment
 *
 * Return: 1
 */

int shell_env(void)

{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}

	return (1);
}

/**
 * shell_getenv - Gets the environment variable
 * @args: Pointer to args
 *
 * Return: 1
 */

void shell_getenv(char **args)
{
	char *value = getenv(args[1]);

	if (args[1] == NULL)
	{
		fprintf(stderr, "shell: getenv: missing argument\n");
	}
	else
	{
		if (value != NULL)
		{
			printf("%s\n", value);
		}
	}
}


/**
 * shell_setenv - Sets the environment variable
 * @args: Pointer to args
 *
 * Return: 1
 */

int shell_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "shell: setenv: missing arguments\n");
	}
	else
	{
		if (setenv(args[1], args[2], 1) != 0)
			perror("shell");
	}
	return (1);
}


/**
 * shell_unsetenv - Unsets the environment variable
 * @args: Pointer to args
 *
 * Return: 1
 */

int shell_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "shell: unsetenv: missing argument\n");
	}
	else
	{
		if (unsetenv(args[1]) != 0)
		{
			perror("shell");
		}
	}
	return (1);
}

