#include "shell.h"
/**
 * _strtok - Separates strings with delimiters
 * @line: Pointer to the array received in getline
 * @delim: Characters that mark off string in parts
 *
 * Return: A pointer to the created token
 */
char *_strtok(char *line, char *delim)
{
	int j;
	static char *str;
	char *copyStr;

	if (line != NULL)
		str = line;

	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
				break;
		}
		if (delim[j] == '\0')
			break;
	}


	copyStr = str;

	if (*copyStr == '\0')
		return (NULL);

	for (; *str != '\0'; str++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (*str == delim[j])
			{
				*str = '\0';
				str++;
				return (copyStr);
			}
		}
	}
	return (copyStr);
}

