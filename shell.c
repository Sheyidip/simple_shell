#include "shell.h"

/**
 * main - main function Entry point
 * @argc: t keep count the number of argument
 * @argv: array to store the argument
 * @envp: the parent environment
 * Return: 0 for success 1 otherwise
 */
int main(int argc, char *argv[], char *envp[])
{
	char user_command[INPUT_SIZE];
	ssize_t input_byte;
	char *exp_cmd;
	int last_status;
	char afterquote[INPUT_SIZE];

	signal(SIGINT, signal_handler);
	while (argc)
	{
		prompt("$ ", s_strlen("$ "));
		input_byte = take_input(user_command);

		if (input_byte == -1)
			continue;
		else if (input_byte == 0)
		{
			prompt("\n", s_strlen("\n"));
			break;
		}

		/*user_command[strcspn(user_command, "\n")] = '\0';*/
		remove_quote(user_command, afterquote);
		remove_comment(afterquote);
		exp_cmd = handle_double_dollar(afterquote);

		last_status = run_command(exp_cmd, envp);

		if (last_status > 0)
		{
			int status;

			waitpid(last_status, &status, 0);
			handle_command_exit(status, argv[0]);
		}
		free(exp_cmd);

	}
	return (0);
}

/**
 * remove_quote - function to remove quote
 * @input: the inout string
 * @output: the result
 * Return: void
 */
void remove_quote(char *input, char *output)
{
	int i, j = 0;
	int insideqoute = 0;
	int length = s_strlen(input);

	for (i = 0; i < length; i++)
	{
		if (input[i] == '"' || input[i] == '\'')
			insideqoute = !insideqoute;
		else
		{
			output[j] = input[i];
			j++;
		}
	}
	output[j] = '\0';
}

/**
 * ispositiveInt - function to check if input is digit
 * @str: the string enter
 * Return: 1 if int
 */
int ispositiveInt(char *str)
{
	int index;

	for (index = 0; str[index] != '\0'; index++)
	{
		if (!isdigit(str[index]))
			return (0);
	}
	return (1);
}
