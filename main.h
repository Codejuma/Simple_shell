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
/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096
/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;
/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

/** all prototype with initials*/
int _myenv(info_t *inf);
char *_getenv(info_t *inf, const char *nam);
int _mysetenv(info_t *inf);
int _myunsetenv(info_t *inf);
int populate_env_list(info_t *inf);
int interactive(info_t *inf);
int is_delim(char b, char *del);
int _isalpha(int b);
int _atoi(char *str);
char *_strchr(char *str, char b);
char *_strncat(char *destin, char *sr, int m);
char *_strncpy(char *destin, char *sr, int m);
void sigintHandler(__attribute__((unused))int signo);
int _getline(info_t *inf, char **ptrr, size_t *leng);
ssize_t read_buf(info_t *inf, char *buff, size_t *j);
ssize_t get_input(info_t *inf);
ssize_t input_buf(info_t *inf, char **buff, size_t *length);
void free_info(info_t *inf, int fd);
void set_info(info_t *inf, char **avg);
void clear_info(info_t *inf);
int renumber_history(info_t *inf);
int build_history_list(info_t *inf, char *buff, int lcont);
int read_history(info_t *inf);
char *get_history_file(info_t *inf);
int write_history(info_t *inf);
ssize_t get_node_index(list_t *hd, list_t *nodd);
list_t *node_starts_with(list_t *nodd, char *prfx, char b);
size_t print_list(const list_t *fn);
char **list_to_strings(list_t *fn);
size_t list_len(const list_t *fn);
int bfree(void **ptrr);
char *_strcat(char *destin, char *srb);
char *starts_with(const char *hystk, const char *ndl);
int _strcmp(char *str1, char *str2);
int _strlen(char *str);
void *_realloc(void *ptrr, unsigned int pr_size, unsigned int nxt_size);
void ffree(char **strs);
char *_memset(char *st, char a, unsigned int m);
int _putchar(char c);
void _puts(char *s);
char *_strdup(const char *s);
char *_strcpy(char *destin, char *srb);
char **strtow2(char *s, char del);
char **strtow(char *s, char *del);
int unset_alias(info_t *inf, char *s);
int set_alias(info_t *inf, char *s);
int print_alias(lists_t *n);
int _myalias(info_t *inf);
int _exit(info_t *inf);
int change_dir(info_t *inf);
int display_help(info_t *inf);
int _erratoi(char *str);
void print_error(info_t *inf, char es);
int print_d(int ip, int fd);
char *convert_number(long int n, int b, int flags);
void remove_comments(char *buff);
int _myenv(info_t *inf);
char *_getenv(info_t *inf, const char *nam);
int _mysetenv(info_t *inf);
int _myunsetenv(info_t *inf);
int populate_env_list(info_t *inf);
void _eputs(char *s);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *s, int fd);
char **_copyenviron(info_t *inf);
int free_envi(inf, char *var);
int get_envi(info_t *inf, char *var, char *val);
list_t *add_list_node(list_t **head, const char *name, int val);
list_t *add_node_end(list_t **head, const char *name, int val);
size_t print_list_name(const list_t *h1);
int delete_node_at_index(list_t **head, unsigned int idx);
void free_list(list_t **head_p);
int main(int ac, char **av);
int exe_cmd(info_t *inf, char *p);
char *dup_char(char *ps, int s1, int s2);
char *find_cmdp(info_t *inf, char *ps, char *cmd)
int hsh(info_t *inf, char **av);
int find_builtin(info_t *inf);
void find_cmd(info_t *inf);
void fork_cmd(info_t *inf);
int is_chain(info_t *inf, char buf, size_t *pos);
void check_chain(info_t *inf, char *buf, size_t *pos, size_t s1, size_t len);
int replace_alias(info_t *inf);
int replace_var(info_t *inf);
int replace_string(char **str1, char *str2);
int main(int ac, char **av);

#endif
