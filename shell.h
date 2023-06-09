#ifndef _SHELL_H_
#define _SHELL_H_

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

/* for conver_number() */
#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

/* for command chaining */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: Points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo_arguements to pass into a function,
 *          allowing uniform prototype for function pointer struct
 * @arg: a string generted from getline containing arguements
 * @argv: an srray of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag:if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custon modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_swap: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointerto cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readpd: the fd from which to read line input
 * @histcount: the history line number count
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
	int env_swap;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readpd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}
/**
 *struct builtin - contains a builtin string and related function
 * @type: the builtin  command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/*task 0 */
int _isdigit(int c);

/*shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/*loopsh.c*/
int loophsh(char **);

/* errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* tokenizer.c */
char **strtow(char *, char *);
char **strtwo2(char *, char);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void s_free(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int _memfree(void **);

/* _atoi.c */
int inter_active(info_t *);
int _delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* errors1.c */
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

/* toem_getline.c */
ssize_t get_input(info_t *);
ssize_t getline_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(__attribute__((unused))int);

/* toem_getlininfo.c */
void init_info_struct(info_t *);
void init_set_info(info_t *, char **);

/*toe_getinfo*/
void clear_info(info_t *);
void set_info(info_t *, char**);
void free_info_struct(info_t *, int);

/* toem_getenv.c*/
char **get_environ_info(info_t *);
int get_unsetenv(info_t *, char *);
int get_setenv(info_t *, char *, char *);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_history */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int list_history(info_t *info, char *, int);
int reassign_history(info_t *);

/* toem_lists.c */
list_t *add_node_start(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list(const list_t *);
int delete_node_idx(list_t **, unsigned int);
void free_list_all(list_t **);

/* toem_lists2.c */
size_t list_length_linked(const list_t *);
char **list_strings(list_t *);
size_t print_list_all(const list_t *);
list_t *node_pointer(list_t *, char *, char);
ssize_t get_node(list_t *, list_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
