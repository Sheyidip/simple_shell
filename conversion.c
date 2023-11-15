#include "shell.h"

/**
 * convert_to_string - converts a number to a string representation.
 * @num: the number to be converted
 * @str: buffer to store the resulting string
 * @base: the base for the conversion
 *
 * Return: void
 */
void convert_to_string(long num, char *str, int base)
{
	int index = 0, isNegative = 0;
	long quotient = num;
	char charset[] = "0123456789abcdef";

	if (quotient == 0)
		str[index++] = '0';

	if (str[0] == '-')
		isNegative = 1;

	while (quotient)
	{
		if (quotient < 0)
			str[index++] = charset[-(quotient % base)];
		else
			str[index++] = charset[quotient % base];
		quotient /= base;
	}
	if (isNegative)
		str[index++] = '-';

	str[index] = '\0';
	reverse_string(str);
}

/**
 * string_to_integer - converts a string to an integer.
 * @s: pointer to the source string.
 *
 * Return: the converted integer or 0.
 */
int string_to_integer(char *s)
{
	int sign = 1;
	unsigned int num = 0;

	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	while ('0' <= *s && *s <= '9' && *s != '\0')
	{
		num = (num * 10) + (*s - '0');
		s++;
	}
	return (num * sign);
}

/**
 * count_occurrences - counts the occurrences of a character in a string.
 * @str: pointer to the source string.
 * @ch: character to count occurrences.
 *
 * Return: number of occurrences of the character in the string.
 */
int count_occurrences(char *str, char *ch)
{
	int i = 0, count = 0;

	for (; str[i]; i++)
	{
		if (str[i] == ch[0])
			count++;
	}
	return (count);
}

