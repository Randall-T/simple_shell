#ifndef SHELL_H
#define SHELL_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

extern char **environ;

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64
#define MAX_ARG_NUM 10

int execute_builtin(char **args);
int shell_exit(char **args);
int shell_cd(char **args);
int shell_env(void);
void shell_getenv(char **args);
int shell_setenv(char **args);
int shell_unsetenv(char **args);
int execute_command(char **args);
char **parse_line(char *line);
char *read_line(FILE *source);
void sigint_handler(int signum);
void display_prompt(void);
int main(int argc, char **argv);
void handle_script_file(char *script_filename);
void handle_user_input(void);


#endif /* SHELL_H */
