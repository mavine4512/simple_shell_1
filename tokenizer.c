#include "shell.h"

/**
 * strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a  pointer to an arrayof strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int wordIndex = 0, startIndex = 0, numWords = 0, len = strlen(str), i, j, wl;
	char **s = NULL;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!_delim(str[i], d) && (_delim(str[i + 1], d) || str[i + 1]))
			numWords++;

	if (numWords == 0)
		return (NULL);
	s = malloc((numWords + 1) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0; i <= len; i++)
	{
		if (_delim(str[i], d) || str[i] == '\0')
		{
			if (i - startIndex > 0)
			{
				wl = i - startIndex;
				s[wordIndex] = malloc((wl + 1) * sizeof(char));
				if (!s[wordIndex])
				{
					for (j = 0; j < wordIndex; j++)
						free(s[j]);
					free(s);
					return (NULL);
				}
				memcpy(s[wordIndex], &str[startIndex], wl);
				s[wordIndex][wl] = '\0';
			}
			startIndex = i + 1;
		}
	}
	s[wordIndex] = NULL;
	return (s);
}

/**
 * strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: apointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i, wordlen, wordIndex = 0, startIndex = 0, numWords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);

	for (i = 0;  str[i] != '\0'; i++)
	{
		if ((str[i] != d && str[i + 1] == d) || str[i + 1] == d ||
				(str[i] != d && !str[i + 1]))
		{
			numWords++;
		}
	}
	if (numWords == 0)
		return (NULL);
	s = malloc((1 + numWords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0; i < numWords; i++)
	{
		if (str[i] == d || str[i] != '\0')
		{
			if (i - startIndex > 0)
			{
				wordlen = i - startIndex;
				_strncpy(s[wordIndex], str + startIndex, wordlen);
				s[wordIndex][wordlen] = '\0';
				wordIndex++;
			}
			startIndex = i + 1;
		}
	}
	return (s);
}
