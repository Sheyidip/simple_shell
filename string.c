#include "shell.h"

/**
 * string_length - returns the length of a string.
 * @str: pointer to the string.
 * Return: length of the string.
 */
int string_length(char *str)
{
	int len = 0;

	if (str == NULL)
		return (0);

	while (str[len++] != '\0')
	{
	}
	return (--len);
}

/**
 * string_duplicate - duplicates a string.
 * @str: string to be copied
 * Return: pointer to the duplicated string
 */
char *string_duplicate(char *str)
{
	char *result;
	int length, i;

	if (str == NULL)
		return (NULL);

	length = string_length(str) + 1;
	result = malloc(sizeof(char) * length);

	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < length ; i++)
	{
		result[i] = str[i];
	}

	return (result);
}

/**
 * string_compare - Compare two strings
 * @str1: first string
 * @str2: second string
 * @num: number of characters to be compared, 0 for infinite
 * Return: 1 if strings are equal, 0 if different
 */
int string_compare(char *str1, char *str2, int num)
{
	int i;

	if (str1 == NULL && str2 == NULL)
		return (1);

	if (str1 == NULL || str2 == NULL)
		return (0);

	if (num == 0)
	{
		if (string_length(str1) != string_length(str2))
			return (0);
		for (i = 0; str1[i]; i++)
		{
			if (str1[i] != str2[i])
				return (0);
		}
		return (1);
	}
	else
	{
		for (i = 0; i < num ; i++)
		{
			if (str1[i] != str2[i])
				return (0);
		}
		return (1);
	}
}

/**
 * string_concatenate - concatenates two strings.
 * @str1: first string
 * @str2: second string
 * Return: pointer to the concatenated string
 */
char *string_concatenate(char *str1, char *str2)
{
	char *result;
	int len1 = 0, len2 = 0, i;

	if (str1 == NULL)
		str1 = "";
	len1 = string_length(str1);

	if (str2 == NULL)
		str2 = "";
	len2 = string_length(str2);

	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (result == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (i = 0; str1[i] != '\0'; i++)
		result[i] = str1[i];

	free(str1);

	for (len2 = 0; str2[len2] != '\0'; len2++)
	{
		result[i] = str2[len2];
		i++;
	}
	result[i] = '\0';
	return (result);
}

/**
 * string_reverse - reverses a string.
 * @str: string to be reversed.
 * Return: void.
 */
void string_reverse(char *str)
{
	int i = 0, len = string_length(str) - 1;
	char temp;

	while (i < len)
	{
		temp = str[i];
		str[i++] = str[len];
		str[len--] = temp;
	}
}

