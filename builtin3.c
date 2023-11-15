#include "shell.h"

/**
 * execute_command - function that create fork and execute command
 * @args: the command to execute
 * @check: the number of token return
 * @last_status: the variable that keeps the value of return
 * @envp: parent environment
 * Return: 0 for success
 */
int execute_command(char *args[], int check, int *last_status, char *envp[])
{
	int j;
	pid_t child_pid = fork();

	if (child_pid < 0)
		return (-1);
	if (child_pid == 0)
	{
		char **exec_Args = malloc((check + 1) * sizeof(char *));

		if (exec_Args == NULL)
			return (-1);
		for (j = 0; j < check; j++)
		{
			exec_Args[j] = s_strdup(args[j]);

			if (exec_Args[j] == NULL)
				return (-1);
		}
		exec_Args[check] = NULL;

		if (exec_command(exec_Args[0], exec_Args, envp) == -1)
		{
			perror(exec_Args[0]);
			exit(2);
		}
		for (j = 0; j < check; j++)
			free(exec_Args[j]);
		free(exec_Args);
	}

	else
	{
		int status;

		waitpid(child_pid, &status, 0);
		*last_status = status;
	}
	return (0);
}

/**
 * handle_cd - function to handle CD command
 * @mycmd: the command at the first index
 * @args: the command to execute
 * @check: the number of token return
 * @last_status: the variable that keeps the value of return
 * @envp: parent environment
 * Return: 0 for success
 */
int handle_cd(char *mycmd, char *args[], int check,
		int *last_status, char *envp[])
{
	if (chk_cmd_before_fork(mycmd) == 1 && check > 0 &&
		s_strcmp(args[0], "cd") == 0)
	{
		int outcome = cd_dir(args[1], envp);

		if (outcome == 0)
		{
			*last_status = 0;
			return (0);
		}
		*last_status = -1;
		return (-1);
	}
	return (1);
}

/**
 * handle_exit - funcnction to handle exit command
 * @args: the command pass to execute
 * @check: the number of token return
 * Return: 0 for success and 1 otherwise
 */
int handle_exit(char *args[], int check)
{
	if (check > 0 && s_strcmp(args[0], "exit") == 0)
	{
		if (check == 1)
			exit(0);
		else if (check == 2)
		{
			char *exitarg = args[1];

			if (ispositiveInt(exitarg))
			{
				int code = atoi(exitarg);

				if (code >= 0)
					exit(code);
			}

			exit(2);
		}
	}
	return (1);
}

/**
 * handle_setenv - function to handle setenv command
 * @mycmd: the command at first index
 * @args: the command to execute
 * @check: the number of token return
 * @last_status: the variable that keeps the value of return
 * Return: 0 on success
 */
int handle_setenv(char *mycmd, char *args[],
		int check, int *last_status)
{
	if (chk_cmd_before_fork(mycmd) == 1 && check > 0 &&
		s_strcmp(args[0], "setenv") == 0)
	{
		int env_rs = setenv_cmd(mycmd);

		if (env_rs == 0)
		{
			*last_status = 0;
			return (0);
		}
		*last_status = -1;
		return (-1);
	}
	return (1);
}

/**
 * handle_unsetenv - function to handle unsetenv command
 * @mycmd: the command at first index
 * @args: the command to execute
 * @check: the number of token return
 * @last_status: the variable that keeps the value of return
 * Return: 0 on success
 */
int handle_unsetenv(char *mycmd, char *args[],
		int check, int *last_status)
{
	if (chk_cmd_before_fork(mycmd) == 1 && check > 0 &&
		s_strcmp(args[0], "unsetenv") == 0)
	{
		int unset_rs = unsetenv_cmd(mycmd);

		if (unset_rs == 0)
		{
			*last_status = 0;
			return (0);
		}
		*last_status = -1;
		return (-1);
	}
	return (1);
}
