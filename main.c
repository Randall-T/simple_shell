#include "shell.h"

/**
 * sigint_handler - Signal handler for Ctrl+C
 * @signum: Stores signal
 */

void sigint_handler(int signum __attribute__((unused)))
{
	int ctrl_c_pressed = 1;
	exit(0);
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
	signal(SIGINT, sigint_handler);

	if (argc == 2)
	{
		handle_script_file(argv[1]);
	}
	else
	{
		handle_user_input();
	}

	return (0);
}
