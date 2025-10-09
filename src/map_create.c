/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:23:59 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/10/09 18:24:03 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_create.h"

static int	ft_count_lines_raw(const char *s)
{
	int		i;
	int		lines;
	size_t	len;

	if (!s || s[0] == '\0')
		return (0);
	len = ft_strlen(s);
	lines = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			lines++;
		i++;
	}
	if (len > 0 && s[len - 1] != '\n')
		lines++;
	return (lines);
}

static void	ft_free_map_temp(char **map_temp, t_game *game)
{
	if (map_temp && *map_temp)
	{
		free(*map_temp);
		*map_temp = NULL;
	}
	ft_error_msg("Error al iniciar el mapa", game);
}

static void	ft_finalize_after_read(t_game *g, char **map_tmp, int ln_ct, int fd)
{
	int	raw_lines;
	int	split_lines;

	close(fd);
	if (ln_ct == 0)
		ft_free_map_temp(map_tmp, g);
	raw_lines = ft_count_lines_raw(*map_tmp);
	g->map.full = ft_split(*map_tmp, '\n');
	if (!g->map.full)
		ft_free_map_temp(map_tmp, g);
	split_lines = ft_count_lines_split(g->map.full);
	if (raw_lines != split_lines)
	{
		g->map_alloc_bool = true;
		ft_free_map_temp(map_tmp, g);
	}
	g->map.rows = split_lines;
	g->map_alloc_bool = true;
	free(*map_tmp);
	*map_tmp = NULL;
}

static void	ft_alloc_check(char **map_temp, t_game **game, int fd, int *ln_ct)
{
	*map_temp = ft_strdup("");
	if (!*map_temp)
	{
		close(fd);
		ft_printf("Error\n de Asignación de memoria\n");
		exit(1);
	}
	*game = ft_calloc(1, sizeof(t_game));
	if (!*game)
	{
		close(fd);
		free(*map_temp);
		ft_printf("Error\n Asignación de memoria\n");
		exit(1);
	}
	(*game)->map_alloc_bool = false;
	*ln_ct = 0;
}

t_game	*ft_init_map(int fd)
{
	t_game	*game;
	char	*map_temp;
	char	*line_temp;
	char	*tmp;
	int		line_count;

	ft_alloc_check(&map_temp, &game, fd, &line_count);
	while (true)
	{
		line_temp = get_next_line(fd);
		if (!line_temp)
			break ;
		tmp = ft_strjoin_free(map_temp, line_temp);
		free(line_temp);
		if (!tmp)
		{
			free(map_temp);
			close(fd);
			ft_error_msg("Error al iniciar el mapa", game);
		}
		map_temp = tmp;
		line_count++;
	}
	ft_finalize_after_read(game, &map_temp, line_count, fd);
	return (game);
}
