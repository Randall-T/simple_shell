#include "shell.h"

/**
 * parse_line - Parses input from read line and tokenizes them
 * @line: Pointer to input
 *
 * Return: Tokenized strings
 */

char **parse_line(char *line)
{
	int bufsize = MAX_ARG_NUM;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "shell: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\n\r\a;");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += MAX_ARG_NUM;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "shell: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \t\n\r\a;");
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * read_line - Gets user input from from user
 *
 * Return: Input from user
 */

#define MAX_INPUT_SIZE 1024

char *read_line(FILE *source)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, source) == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}

/**
 * handle_script_file - Handles scripts or files as command line arguments
 * @script_filename: Name of the file or script passed
 */

void handle_script_file(char *script_filename)
{
	char *line;
	char **args;
	int status;
	int ctrl_c_pressed = 1;

	FILE *script_file = fopen(script_filename, "r");

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
			break;
	}
	fclose(script_file);
}

/**
 * handle_user_input - Handles user input from STDIN
 */

void handle_user_input(void)
{
	char *line;
	char **args;
	int ctrl_c_pressed = 1;

	do {
		display_prompt();
		fflush(stdout);

		line = read_line(stdin);
		if (line == NULL)
			break;

		args = parse_line(line);
		execute_command(args);

		free(line);
		free(args);
	} while (!ctrl_c_pressed);

	printf("\nShell terminated by Ctrl+C\n");
}
