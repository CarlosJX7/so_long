/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:09:34 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/05/12 16:31:07 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


static void	ft_strjoin_cpy(char *r, char const *s1, char const *s2, size_t l)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1 && i < l)
	{
		r[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		r[i + j] = s2[j];
		j++;
	}
	r[i + j] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_substr(s2, 0, ft_strlen(s2)));
	if (!s2)
		return (ft_substr(s1, 0, ft_strlen(s1)));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);
	ft_strjoin_cpy(res, s1, s2, len1);
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	char	find;
	int		i;

	find = (unsigned char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == find)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == find)
		return ((char *)s + i);
	return (0);
}

char	*ft_substr(char	const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *) malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}
