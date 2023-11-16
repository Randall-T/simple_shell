#include "shell.h"

/**
 * execute_builtin - Execute a shell builtin
 * @args: Pointer to arg
 *
 * Return: Builtin or 0
 */

int execute_builtin(char **args)
{
	int cd_result = shell_cd(args);

	if (args == NULL || args[0] == NULL)
	{
		return (1);
	}
	else if (strcmp(args[0], "exit") == 0)
	{
		shell_exit(args);
			return (0);
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		if (cd_result != 0)
		{
			fprintf(stderr, "shell: cd: error changing directory\n");
		}
		return (1);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		shell_env();
		return (0);
	}
	else if (strcmp(args[0], "setenv") == 0)
	{
		return (shell_setenv(args));
	}
	else if (strcmp(args[0], "getenv") == 0)
	{
		shell_getenv(args);
			return (0);
	}
	else if (strcmp(args[0], "unsetenv") == 0)
	{
		shell_unsetenv(args);
			return (0);
	}

	return (1);
}

/**
 * shell_exit - Exits shell with status
 * @args: Pointer to arg
 *
 * Return: 0 or status
 */

int shell_exit(char **args)
{
	int status = 0;

	if (args[1] != NULL)
	{
		status = atoi(args[1]);

		if (status == 0 && args[1][0] != '0')
		{
			fprintf(stderr, "shell: exit: invalid status: %s\n", args[1]);
			return (1);
		}
		exit(status);
	}
	else
	{
		exit(0);
	}
}

/**
 * shell_cd - Builtin change directory
 * @args: Pointer to arg
 * Return: 1
 */

int shell_cd(char **args)
{
	char *target_dir = args[1];
	char *current_dir = getcwd(NULL, 0);

	if (target_dir == NULL)
	{
		target_dir = getenv("HOME");
		if (target_dir == NULL)
		{
			fprintf(stderr, "shell: cd: HOME not set\n");
			return (1);
		}
	}
	else if (strcmp(target_dir, "-") == 0)
	{
		target_dir = getenv("OLDPWD");
		if (target_dir == NULL)
		{
			fprintf(stderr, "shell: cd: OLDPWD not set\n");
			return (1);
		}
	}

	if (current_dir == NULL)
	{
		perror("shell");
		return (1);
	}

	if (chdir(target_dir) != 0)
	{
		perror("shell");
		free(current_dir);
		return (1);
	}

	if (setenv("OLDPWD", current_dir, 1) != 0)
	{
		perror("shell");
	}

	free(current_dir);

	return (0);
}

