#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * get_line - Read a line of input from the user.
 * @buffer: A pointer to the buffer to store the input.
 * @size: The size of the buffer.
 * Return: The number of bytes read or -1 on failure.
 */
ssize_t get_line(char *buffer, size_t size)
{
	ssize_t total_bytes = 0;
	ssize_t bytes_read;
	char ch;

	if (buffer == NULL || size == 0)
	{
		return (-1);
	}
	while (total_bytes < (ssize_t)(size - 1))
	{
		bytes_read = read(STDIN_FILENO, &ch, 1);
		if (bytes_read < 0)
		{
			perror("Error reading input");
			return (-1);
		}
		else if (bytes_read == 0 || ch == '\n')
		{
			buffer[total_bytes] = '\0';
			return (total_bytes);
		}
		else
		{
			buffer[total_bytes] = ch;
			total_bytes++;
		}
	}
	buffer[total_bytes] = '\0';
	return (total_bytes);
}
