#include "shell.h"
/**
 * pid_len - function to get the length of pid
 * @pid: the pid to get the lenght
 * Return: the length
 */
int pid_len(int pid)
{
	int len = 0;

	while (pid > 0)
	{
		len++;
		pid /= 10;
	}
	return (len);
}
/**
 * int_to_str - function to convert int to str
 * @num: the number to convert
 * @str: where to store it in string
 * @str_len: the length of the string
 * Return: void
 */
void int_to_str(int num, char *str, int str_len)
{
	int index = str_len - 1;

	str[index] = '\0';
	while (index > 0)
	{
		index--;
		str[index] = '0' + (num % 10);
		num /= 10;
		if (num == 0)
			break;
	}
}
/**
 * handle_double_dollar - function to handle dollar sign
 * @cmd: the user command
 * Return: the result
 */
char *handle_double_dollar(const char *cmd)
{
	char *output = malloc(s_strlen(cmd) + 1);
	int i = 0;
	int j = 0;
	int c_pid = getpid();
	char pid_buff[16];
	int pid_length = pid_len(c_pid);

	int_to_str(getpid(), pid_buff, pid_length + 1);
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '$' && cmd[i + 1] == '$')
		{
			int k = 0;

			while (k < pid_length)
			{
				output[j++] = pid_buff[k];
				k++;
			}
			i += 2;
		}
		else
			output[j++] = cmd[i++];
	}
	output[j] = '\0';
	return (output);
}
/**
 * remove_comment - function to remove comment
 * @cmd: the user command
 * Return: void
 */
void remove_comment(char *cmd)
{
	int index = 0;
	int qou = 0;

	while (cmd[index] != '\0')
	{
		if (cmd[index] == '"')
			qou = !qou;
		if (!qou && cmd[index] == '#')
		{
			cmd[index] = '\0';
			break;
		}
		index++;
	}
}
/**
 * int_to_string - function to convert integer to string
 * @value: the integer
 * @str: the string where to store
 * @size: the length
 * Return: void
 */
void int_to_string(int value, char *str, int size)
{
	int index = size - 1;

	str[index] = '\0';
	do {
		index--;
		str[index] = '0' + (value % 10);
		value /= 10;
	} while (value != 0 && index > 0);
}
