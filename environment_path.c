#include "shell.h"
/**
 * getEnvKey - Get the value of an environment variable.
 * @key: The environment variable of interest.
 * @data: Pointer to the program's data structure.
 * Return: A pointer to the value of the variable or NULL if it doesn't exist.
 */
char *getEnvKey(char *key, shellData *data)
{
	int i, keyLen = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);

	keyLen = stringLength(key);

	for (i = 0; data->env[i]; i++)
	{
		if (compareStrings(key, data->env[i], keyLen) && data->env[i][keyLen] == '=')
		{
			return (data->env[i] + keyLen + 1);
		}
		return (NULL);
	}
/**
* setEnvKey - Overwrite the value of the environment variable
* or create it if it does not exist.
* @key: Name of the variable to set.
* @value: New value.
* @data: Pointer to the program's data structure.
* Return: 1 if the parameters are NULL, 2 if there is an error or 0 if success.
*/
int setEnvKey(char *key, char *value, shellData *data)
{
		int i, keyLen = 0, isNewKey = 1;

		if (key == NULL || value == NULL || data->env == NULL)
			return (1);

		keyLen = stringLength(key);

		for (i = 0; data->env[i]; i++)
		{

			if (compareStrings(key, data->env[i], keyLen) && data->env[i][keyLen] == '=')
			{

				isNewKey = 0;

				free(data->env[i]);
				break;
			}
		}
		data->env[i] = concatStrings(duplicateString(key), "=");
		data->env[i] = concatStrings(data->env[i], value);

		if (isNewKey)
		{
			data->env[i + 1] = NULL;
		}
		return (0);
}
/**
* removeEnvKey - Remove a key from the environment.
* @key: The key to remove.
* @data: Pointer to the program's data structure.
* Return: 1 if the key was removed, 0 if the key does not exist.
*/
int removeEnvKey(char *key, shellData *data)
{
		int i, keyLen = 0;

		if (key == NULL || data->env == NULL)
			return (0);
		keyLen = stringLength(key);

		for (i = 0; data->env[i]; i++)
		{
			if (compareStrings(key, data->env[i], keyLen) && data->env[i][keyLen] == '=')
			{
				free(data->env[i]);
				i++;
				for (; data->env[i]; i++)
				{
					data->env[i - 1] = data->env[i];
				}
				data->env[i - 1] = NULL;
				return (1);
			}
		}
		return (0);
}
/**
* printEnviron - Prints the current environment.
* @data: Pointer to the program's data structure.
*/
void printEnviron(shellData *data)
{
		int j;

		for (j = 0; data->env[j]; j++)
		{
			_print(data->env[j]);
			_print("\n");
		}
}

