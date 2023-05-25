#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: source string
 * @n: the amout of characters to be copied
 * Return: concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, x;
	char *s = dest;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	if (i < n)
	{
		for (x = i; x < n; x++)
		{
			dest[x] = '\0';
		}
	}
	return (s);
}
/**
 * _strncat - concatenated two string
 * @dest: first string
 * @src: second string
 * @n: the amount of bytes to be maximally used
 * Return: concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	char *s = dest;

	/*Move dest pointer to end of string*/
	while (*dest != '\0')
		dest++;

	/*Copy src to dest until n characters hv been copied*/
	/*or the end of src is reached*/
	while (*src != '\0' && n--)
		*dest++ = *src++;

	*dest = '\0';
	return (s);
}

/**
 * _strchr - locates a character in a string
 * @s: string to be parsed
 * @c: character to look for
 * Return: (s) pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
