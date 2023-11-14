#include "shell.h"
/**
 * executeExit - Exit the program with a status.
 * @data: Struct for the program's data.
 * Return: Zero on success or other number if declared in the arguments.
 */
int executeExit(shellData *data)
{
	int index;

	if (data->tokens[1] != NULL)
	{
		for (index = 0; data->tokens[1][index]; index++)
		{
			if ((data->tokens[1][index] < '0' || data->tokens[1][index] > '9') &&
					data->tokens[1][index] != '+') {
				setErrnoValue(2);
				return (2);
			}
		}
		setErrnoValue(_atoi(data->tokens[1]));
	}
	freeAllData(data);
	exit(getErrnoValue());
}
/**
 * executeChangeDirectory - Change the current directory.
 * @data: Struct for the program's data.
 * Return: Zero on success or other number if declared in the arguments.
 */
int executeChangeDirectory(shellData *data)
{
	char *homeDir = getEnvironmentVariable("HOME", data);
	char *oldDir = NULL;
	char oldDirectory[128] = {0};
	int errorCode = (0);

	if (data->tokens[1])
	{
		if (compareStrings(data->tokens[1], "-", 0))
		{
			oldDir = getEnvironmentVariable("OLDPWD", data);
			if (oldDir)
			{
				errorCode = setWorkingDirectory(data, oldDir);
			}
			printMessage(getEnvironmentVariable("PWD", data));
			printMessage("\n");
			return (errorCode);
		}
		else
		{
			return (setWorkingDirectory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!homeDir)
		{
			homeDir = getCwd(oldDirectory, 128);
		}
		return (setWorkingDirectory(data, homeDir));
	}
	return (0);
}
/**
 * setWorkingDirectory - Set the working directory.
 * @data: Struct for the program's data.
 * @newDir: Path to be set as the work directory.
 * Return: Zero on success or other number if declared in the arguments.
 */
int setWorkingDirectory(shellData *data, char *newDir)
{
	char oldDirectory[128] = {0};
	int errCode = 0;

	getCwd(oldDirectory, 128);

	if (!compareStrings(oldDirectory, newDir, 0))
	{
		errCode = changeDir(newDir);
		if (errCode == -1)
		{
			setErrnoValue(2);
			return (3);
		}
		setEnvironmentVariable("PWD", newDir, data);
	}
	setEnvironmentVariable("OLDPWD", oldDirectory, data);
	return (0);
}
/**
 * executeHelpCommand - Show help information.
 * @data: Struct for the program's data.
 * Return: Zero on success or other number if declared in the arguments.
 */
int executeHelpCommand(shellData *data)
{
	int i, length = 0;
	char *messages[6] = {NULL};

	messages[0] = "Help: ";
	messages[1] = "exit: Exit the shell";
	messages[2] = "env: Show the current environment";
	messages[3] = "setenv: Set an environment variable";
	messages[4] = "unsetenv: Unset an environment variable";
	messages[5] = "cd: Change the current directory";

	if (data->tokens[1] == NULL)
	{
		printMessage(messages[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		setErrnoValue(EDQUOT);
		printErrorMessage(data->commandName);
		return (5);
	}
	for (i = 0; messages[i]; i++)
	{
		length = strLength(data->tokens[1]);
		if (compareStrings(data->tokens[1], messages[i], length))
		{
			printMessage(messages[i] + length + 1);
			return (1);
		}
	}
	setErrnoValue(EINVAL);
	printErrorMessage(data->commandName);
	return (0);
}
/**
 * executeManageAliases - Add, remove, or show aliases.
 * @data: Struct for the program's data.
 * Return: Zero on success or other number if declared in the arguments.
 */
int executeManageAliases(shellData *data)
{
	int i = 0;

	if (data->tokens[1] == NULL)
	{
		return (printAlias(data, NULL));
	}

	while (data->tokens[++i])
	{
		if (countChars(data->tokens[i], "="))
		{
			setAlias(data->tokens[i], data);
		}
		else
		{
			printAlias(data, data->tokens[i]);
		}
	}
	return (0);
}

