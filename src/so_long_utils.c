#include "so_long_utils.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len1 + 1);
	ft_strlcat(str, s2, len1 + len2 + 1);
	free(s1);
	return (str);
}

int	count_lines_split(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	is_passable(char c)
{
	if (c == FLOOR || c == COINS || c == PLAYER)
		return (1);
	return (0);
}

int	in_bounds(int x, int y, int w, int h)
{
	if (x < 0 || y < 0)
		return (0);
	if (x >= w || y >= h)
		return (0);
	return (1);
}