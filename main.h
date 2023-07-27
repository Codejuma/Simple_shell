#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <fcntl.h>
#define TOK_BUFSIZE 50
#define TOK_DELIM " \t\r\n\a"
extern char **environ;

/* toem_memory.c */
int bfree(void **);

/* toem_simple_shell.c*/
void execute_command(char *comm);
char **_split_string(char *s, char sp);
char **_which(char *fdp);
int child_process(char **av, char **args, char **env, int status_main, int cnt);
char **search_path(char **environ);

void *_calloc(unsigned int nmemb, unsigned int size);

int _stat(char **cmd, char **path);
void *_error(char *argv, int count, char *args);
void handle_signal(int sig);
void *_error(char *av, int cnt, char *args);
int main(int ac __attribute__((unused)), char **av, char **env);
void func_printenv(char **environ);
#endif
