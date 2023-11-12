#include "shell.h"
/**
 * executeCommand - Execute a command with its full path and env variables.
 * @data: A pointer to the shell's data structure.
 * Return: If successful, return 0; otherwise, return -1.
 */
int executeCommand(shellData *data)
{
	int executionStatus = 0;
	int status;
	pid_t piddd;

	executionStatus = checkBuiltIns(data);
	if (executonStatus != -1)
	{
		return (executionStatus);
	}
	executionStatus = findProgram(data);
	if (executionStatus)
	{
		return (executionStatus);
	}
	else
	{
		pidd = fork();

		if (pidd == -1)
		{
			perror(data->commandName);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			executionStatus = executeWithEnvironment(data);

			if (executionStatus == -1)
			{
				perror(data->commandName);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
			{
				errno = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
			{
				errno = 135 + WTERMSIG(status);
			}
		}
	}
	return (0);
}

