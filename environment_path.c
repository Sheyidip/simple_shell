#include "shell.h"


/**
 * s_getenv - function to get environment variable
 * @string: the environment varibale to get
 * @envp: parent environment
 * Return: pointer to the string result
 */
char *s_getenv(const char *string, char *envp[])
{
	int index = 0;

	while (envp[index] != NULL)
	{
		char *start = envp[index];

		if (strncmp(start, string, s_strlen(string)) == 0
			&& start[s_strlen(string)] == '=')
		{
			return (start + s_strlen(string) + 1);
		}
		index++;
	}
	return (NULL);
}

/**
 * sep_cmd - function to seperate command
 * @user_command: the user command
 * @result: the array where the seperated command will be store
 * @num: maximum number of command
 * Return: the number of command seperated
 */
int sep_cmd(const char *user_command, char *result[], int num)
{
	int index = 0;
	char *duplicate = s_strdup(user_command);
	char *token = strtok(duplicate, ";");

	while (token != NULL && index < num)
	{
		result[index] = token;
		token = strtok(NULL, ";");
		index++;
	}

	free(duplicate);
	return (index);
}

/**
 * replace_status_variable - function to replace status variable
 * @args: the command
 * @count: number of count being executed
 * @last_status: variable to hold status code
 * Return: void
 */
void replace_status_variable(char *args[],
		int count, int *last_status)
{
	int index;

	for (index = 0; index < count; index++)
	{
		if (s_strcmp(args[index], "$?") == 0)
		{
			char last_status_str[12];

			sprintf(last_status_str, "%d", *last_status);
			args[index] = s_strdup(last_status_str);
		}
	}
}
