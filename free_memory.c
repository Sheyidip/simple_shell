#include "shell.h"

/**
 * releaseMemory - Free memory of individual data fields
 * @data: Pointer to the program's data struct
 *
 * Returns: None
 */
void releaseMemory(shellData *data)
{
	if (data->tokens)
		freeTokenArray(data->tokens);
	if (data->inputLine)
		free(data->inputLine);
	if (data->commandName)
		free(data->commandName);

	data->inputLine = NULL;
	data->commandName = NULL;
	data->tokens = NULL;
}

/**
 * freeAllData - Free all dynamically allocated data in the program's struct
 * @data: Pointer to the program's data struct
 *
 * Returns: None
 */
void freeAllData(shellData *data)
{
	if (data->fileDescriptor != 0)
	{
		if (close(data->fileDescriptor))
			perror(data->programName);
	}
	releaseMemory(data);
	freeTokenArray(data->env);
	freeTokenArray(data->aliasList);
}

/**
 * freeTokenArray - Free memory of an array of tokens
 * @array: Array of tokens
 *
 * Returns: None
 */
void freeTokenArray(char **array)
{
	int i = 0;

	if (array != NULL)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

