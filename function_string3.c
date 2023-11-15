#include "shell.h"

/**
 * s_strcat - function to concatenate two strings
 * @dest: the destination string
 * @src: the source string to append to dest
 * Return: pointer to the destination string 'dest'
 */
char *s_strcat(char *dest, const char *src)
{
	char *temp = dest;

	while (*temp != '\0')
	{
		temp++;
	}

	while (*src != '\0')
	{
		*temp = *src;
		temp++;
		src++;
	}
	*temp = '\0';

	return (dest);
}

/**
 * s_strcmp - function to compare two strings
 * @str1: the first string
 * @str2: the second string
 * Return: 0 if 'str1' and 'str2' are equal, a negative
 * value if 'str1' < 'str2', or a positive value if 'str1' > 'str2'
 */
int s_strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}

	return (*str1 - *str2);
}

