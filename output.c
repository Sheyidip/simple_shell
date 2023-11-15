#include "shell.h"

/**
 * write_stdout - writes an array of characters to standard output
 * @str: pointer to the array of characters
 * Return: the number of bytes written, -1 on error
 */
int write_stdout(char *str)
{
	return (write(STDOUT_FILENO, str, str_length(str)));
}

/**
 * write_stderr - writes an array of characters to standard error
 * @str: pointer to the array of characters
 * Return: the number of bytes written, -1 on error
 */
int write_stderr(char *str)
{
	return (write(STDERR_FILENO, str, str_length(str)));
}

/**
 * print_error_message - prints error messages to standard error
 * @error_code: error code to print
 * @shell_data: pointer to the shell's data structure
 * Return: 0 on success, -1 on error
 */
int print_error_message(int error_code, shellData *data)
{
	char counter_as_string[10] = {'\0'};

	long_to_string((long)data->execution_counter, counter_as_string, 10);

	if (error_code == 2 || error_code == 3)
	{
		write_stderr(data->program_name);
		write_stderr(": ");
		write_stderr(counter_as_string);
		write_stderr(": ");
		write_stderr(data->tokens[0]);
		if (error_code == 2)
			write_stderr(": Illegal number: ");
		else
			write_stderr(": can't cd to ");
		write_stderr(data->tokens[1]);
		write_stderr("\n");
	}
	else if (error_code == 127)
	{
		write_stderr(data->program_name);
		write_stderr(": ");
		write_stderr(counter_as_string);
		write_stderr(": ");
		write_stderr(data->command_name);
		write_stderr(": not found\n");
	}
	else if (error_code == 126)
	{
		write_stderr(data->program_name);
		write_stderr(": ");
		write_stderr(counter_as_string);
		write_stderr(": ");
		write_stderr(data->command_name);
		write_stderr(": Permission denied\n");
	}
	return (0);
}

