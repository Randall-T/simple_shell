#include "shell.h"

int execute_builtin(char **args);

/**
 * execute_command - Runs the commands entered
 * @args: Pointer to args
 *
 * Return: 1
 */

int execute_command(char **args)
{
	int status;
	pid_t pid;

	if (args == NULL || args[0] == NULL)
	{
		return (1);
	}

	if (execute_builtin(args) == 0)
	{
		return (1);
	}
	if (access(args[0], X_OK) == -1)
	{
		fprintf(stderr, "shell: %s: command not found or executable\n", args[0]);
		return (1);
	}

	pid = fork();

	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror("shell");
			fprintf(stderr, "Error executing: %s\n", args[0]);
		}

	}
	else if (pid < 0)
	{
		perror("shell");
		return (-1);
	}
	else
	{
		waitpid(pid, &status, 0);

		if (WIFEXITED(status))
		{
			return (WEXITSTATUS(status));
		}
		else
		{
			fprintf(stderr, "Child process did not terminate normally\n");
			return (1);
		}
	}

	return (status);

}

