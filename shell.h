#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>

#define INPUT_SIZE 200

#define LOOP 10

#define PATH_SIZE 1024

#define ARG_SIZE 200

void set_executable_name(char *name);

void prompt(char *c, int len);

ssize_t take_input(char *input);

int run_command(char *user_command, char *envp[]);

void handle_command_exit(int status, const char *user_command);

void tokenize_command(char *user_command, char **args);

int exec_command(char *user_command, char *args[], char **env);

int exec_command_withpath(char *user_command, char *args[], char **env);

void exitShell(int status);

int chk_cmd_before_fork(char *user_command);

int setenv_cmd(char *user_command);

int unsetenv_cmd(char *user_command);

int unset_env(char *var);

int token_command(char *user_command, char *args[]);

int set_env_var(char *var, char *value);

int cd_dir(const char *args, char *envp[]);

int upd_env_var(const char *path, char *envp[]);

int change_dir(const char *path);

int pass_cd_arg(const char *user_command);

ssize_t get_line(char *buffer, size_t size);


char *s_strdup(const char *string);

int s_strlen(const char *string);

int s_strcspn(const char *string, const char *chr);

char *s_strcpy(char *dest_string, const char *src_String);

char *s_strchr(const char *string, int chr);

char *s_strcat(char *dest, const char *src);

int s_strcmp(const char *str1, const char *str2);

char *initialize_token(char *string);

char *tokenize(char *token, const char *deli);

char *finalize_token();

char *s_strtok(char *string, const char *deli);

char *s_getenv(const char *string, char *envp[]);

int sep_cmd(const char *user_command, char *result[], int num);

char *handle_double_dollar(const char *cmd);

void remove_comment(char *cmd);

int pid_len(int pid);

void int_to_str(int num, char *str, int str_len);

int get_status_code(int status);

void int_to_string(int value, char *str, int size);



int execute_command(char *args[], int check, int *last_status, char *envp[]);

int handle_cd(char *mycmd, char *args[], int check,
		int *last_status, char *envp[]);

int handle_exit(char *args[], int check);

int handle_setenv(char *mycmd, char *args[], int check, int *last_status);

int handle_unsetenv(char *mycmd, char *args[], int check, int *last_status);

void replace_status_variable(char *args[], int count, int *last_status);


typedef struct Alias
{char *name;
char *value;
struct Alias *next; }
Alias;

void add_alias(const char *name, const char *value);

void list_aliases(void);

Alias *find_alias(const char *name);

void remove_quote(char *input, char *output);


void signal_handler(int signal);

int ispositiveInt(char *str);

#endif
