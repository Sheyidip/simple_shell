#include "shell.h"

/**
 * expandVars - Expand variables in the input line.
 * @data: Pointer to the program's data structure.
 */
void expandVars(shellData *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, exp[BUFFER_SIZE] = {'\0'}, *tmp;

	if (data->input_line == NULL)
		return;
	addBuffer(line, data->input_line);
	for (i = 0; line[i]; i++)
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			longToString(errno, exp, 10);
			addBuffer(line, exp);
			addBuffer(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			longToString(getpid(), exp, 10);
			addBuffer(line, exp);
			addBuffer(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				exp[j - 1] = line[i + j];
			tmp = getEnvKey(exp, data);
			line[i] = '\0', exp[0] = '\0';
			addBuffer(exp, line + i + j);
			tmp ? addBuffer(line, tmp) : 1;
			addBuffer(line, exp);
		}
	if (!compareStrings(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = duplicateString(line);
	}
}

/**
 * expandAlias - Expand aliases in the input line.
 * @data: Pointer to the program's data structure.
 */
void expandAlias(shellData *data)
{
	int i, j, expandedFlag = 0;
	char line[BUFFER_SIZE] = {0}, exp[BUFFER_SIZE] = {'\0'}, *tmp;

	if (data->input_line == NULL)
		return;

	addBuffer(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			exp[j] = line[i + j];
		exp[j] = '\0';

		tmp = getAlias(data, exp);
		if (tmp)
		{
			exp[0] = '\0';
			addBuffer(exp, line + i + j);
			line[i] = '\0';
			addBuffer(line, tmp);
			line[stringLength(line)] = '\0';
			addBuffer(line, exp);
			expandedFlag = 1;
		}
		break;
	}
	if (expandedFlag)
	{
		free(data->input_line);
		data->input_line = duplicateString(line);
	}
}

/**
 * addBuffer - Append string at end of the buffer.
 * @buffer: Buffer to be filled.
 * @strToAdd: String to be copied in the buffer.
 *
 * This function appends the given string at the end of the provided buffer.
 * It returns the length of the resulting buffer after the addition.
 */
int addBuffer(char *buffer, char *strToAdd)
{
	int len, i;

	len = stringLength(buffer);

	for (i = 0; strToAdd[i]; i++)
	{
		buffer[len + i] = strToAdd[i];
	}
	buffer[len + i] = '\0';
	return (len + i);
}

