#include "shell.h"

/**
 * main - Entry point of the custom shell program.
 * @argc: Number of command line arguments.
 * @argv: Array of command line arguments.
 * @envp: Array of environment variables.
 * Return: 0 on success.
 */
int main(int argc, char *argv[], char *envp[])
{
	shellData data;
	char *customPrompt = "";

	init_shellData(&data, argc, argv, envp);
	signal(SIGINT, handleCtrlC);

	if (isInteractiveMode() && argc == 1)
	{
		errno = 2;
		customPrompt = "CustomShell > ";
	}
	errno = 0;
	runShell(customPrompt, &data);
	return (0);
}

/**
 * handleCtrlC - Handle the SIGINT signal (Ctrl+C) gracefully.
 * @unused: Unused parameter.
 */
void handleCtrlC(int unused)
{
	_print("\n");
	_print("CustomShell > ");
}

/**
 * init_ShellData - Initialize the ShellData structure.
 * @data: Pointer to the ShellData structure.
 * @argc: Number of command line arguments.
 * @argv: Array of command line arguments.
 * @envp: Array of environment variables.
 */
void init_shellData(shellData *data, int argc, char *argv[], char *envp[])
{
	int i = 0;

	data->programName = argv[0];
	data->inputLine = NULL;
	data->commandName = NULL;
	data->executionCounter = 0;

	if (argc == 1)
	{
		data->fileDescriptor = STDIN_FILENO;
	}
	else
	{
		data->fileDescriptor = openFileDescriptor(argv[1]);
	}

	data->tokens = NULL;
	data->environment = createEnvironment(envp);
	data->aliasList = createAliasList();

	for (; i < 20; i++)
	{
		data->aliasList[i] = NULL;
	}
}

/**
 * runShell - Main loop, displaying the prompt and processing user input.
 * @prompt: The prompt string to display.
 * @data: Pointer to the ShellData structure.
 */
void runShell(char *prompt, shellData *data)
{
	int errorCode = 0;
	int stringLength = 0;

	while (++(data->executionCounter))
	{
		_print("%s", prompt);
		errorCode = stringLength = readInputLine(data);

		if (errorCode == EOF)
		{
			freeShellData(data);
			exit(errno);
		}

		if (stringLength >= 1)
		{
			expandAliases(data);
			expandVariables(data);
			tokenizeInput(data);

			if (data->tokens[0])
			{
				errorCode = executeCommand(data);

				if (errorCode != 0)
				{
					printErrorMessage(errorCode, data);
				}
			}

			freeTokenData(data);
		}
	}
}
