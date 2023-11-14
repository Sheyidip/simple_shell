#include "shell.h"
/**
 * showEnvironment - Display the current environment of the shell.
 * @data: Pointer to the shell's data structure.
 * Return: 0 on success, or another value if specified in the arguments.
 */
int showEnvironment(shellData *data)
{
	int index;
	char variableName[50] = {'\0'};
	char *variableCopy = NULL;

	if (data->tokens[1] == NULL)
	{
		displayEnvironment(data);
	}
	else
	{
		for (index = 0; data->tokens[1][index]; index++)
		{
			if (data->tokens[1][index] == '=')
			{
				variableCopy = duplicateEnvironmentVariable(variableName, data);

				if (variableCopy != NULL)
					modifyEnvironmentVariable(variableName, data->tokens[1] + index + 1, data);
				displayEnvironment(data);

				if (getEnvironmentVariable(variableName, data) == NULL)
				{
					printMessage(data->tokens[1]);
					printMessage("\n");
				}
				else
				{
					restoreEnvironmentVariable(variableName, variableCopy, data);
					free(variableCopy);
				}
				return (0);
			}
			variableName[index] = data->tokens[1][index];
		}
		setErrnoValue(2);
		printErrorMessage(data->commandName);
		setErrnoValue(127);
	}
	return (0);
}
/**
 * setEnvironmentVariable - Set a new environment variable.
 * @data: Pointer to the shell's data structure.
 * Return: 0 on success, or another value if specified in the arguments.
 */
int setEnvironmentVariable(shellData *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
	{
		return (0);
	}
	if (data->tokens[3] != NULL)
	{
		setErrnoValue(EDQUOT);
		printErrorMessage(data->commandName);
		return (42);
	}
	defineEnvironmentVariable(data->tokens[1], data->tokens[2], data);
	return (0);
}
/**
 * unsetEnvironmentVariable - Unset an environment variable.
 * @data: Pointer to the shell's data structure.
 * Return: 0 on success, or another value if specified in the arguments.
 */
int unsetEnvironmentVariable(shellData *data)
{
	if (data->tokens[1] == NULL)
	{
		return (0);
	}
	if (data->tokens[2] != NULL)
	{
		setErrnoValue(EINVAL);
		printErrorMessage(data->commandName);
		return (88);
	}
	eliminateEnvironmentVariable(data->tokens[1], data);
	return (0);
}

