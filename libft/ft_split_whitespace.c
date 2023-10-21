#include "libft.h"

static bool	char_is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\f')
		return (true);
	return (false);
}

static	int	segments_count(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (char_is_whitespace(s[i]))
			i++;
		if (s[i] != '\0')
			count++;
		while (!char_is_whitespace(s[i]) && s[i] != '\0')
			i++;
	}
	return (count);
}

static	char	**undo_magic(char **result, int index)
{
	while (index > 0)
	{
		index--;
		free(result[index]);
	}
	free(result);
	return (NULL);
}

static	char	*do_magic(char const *s)
{
	int		j;
	char	*clone;

	j = 0;
	while (!char_is_whitespace(s[j]) && s[j] != '\0')
		j++;
	clone = (char *)malloc(j + 1);
	if (!clone)
		return (NULL);
	ft_strlcpy(clone, s, j + 1);
	return (clone);
}

static	void	init(int *var)
{
	var[0] = 0;
	var[1] = 0;
}

char	**ft_split_whitespace(char const *s)
{
	char	**result;
	int		var[2];

	if (!s)
		return (NULL);
	result = (char **)malloc((segments_count(s) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	init(var);
	while (s[var[0]] != '\0')
	{
		while (char_is_whitespace(s[var[0]]))
			var[0]++;
		if (s[var[0]] != '\0')
		{
			result[var[1]] = do_magic(&s[var[0]]);
			if (!result[var[1]])
				return (undo_magic(result, var[0]));
			var[1]++;
		}
		while (s[var[0]] && !char_is_whitespace(s[var[0]]))
			var[0]++;
	}
	result[var[1]] = NULL;
	return (result);
}