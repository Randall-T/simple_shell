#include "shell.h"

volatile sig_atomic_t ctrl_c_pressed = 0;

/**
 * sigint_handler - Signal handler for Ctrl+C
 * @signum: Stores signal
 */

void sigint_handler(int signum __attribute__((unused)))
{
	ctrl_c_pressed = 1;
}


/**
 * display_prompt - Displays a $ prompt
 */

void display_prompt(void)
{
	printf("$ ");
}

/**
 * main - Simple Unix interpreter
 * @argc: Argument count
 * @argv: Argument vector
 * Return: 0
 */

int main(int argc, char **argv)
{
	char *line;
	char **args;
	int status;
	signal(SIGINT, sigint_handler);
	
/**
 * printf("Current PATH: %s\n", getenv("PATH"));
 * setenv("PATH", "/bin:/usr/bin:/usr/local/bin", 1);
 * printf("Updated PATH: %s\n", getenv("PATH"));
*/
	if (argc == 2)
	{
		FILE *script_file = fopen(argv[1], "r");

		if (!script_file)
		{
			perror("shell");
			exit(EXIT_FAILURE);
		}

		while ((line = read_line(script_file)) != NULL)
		{
			args = parse_line(line);
			status = execute_command(args);

			free(line);
			free(args);

			if (!status || ctrl_c_pressed)
			{
				break;
			}
		}

		fclose(script_file);
	}
	else

	{

		do {
			display_prompt();
			fflush(stdout);

			line = read_line(stdin);
			if (line == NULL)
			{
				break;
			}
			args = parse_line(line);
			status = execute_command(args);

			free(line);
			free(args);
		} while (!ctrl_c_pressed);

		printf("Shell terminated by Ctrl+C\n");
	}

	return (0);
}
