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
