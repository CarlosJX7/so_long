#include "map.h"

/* Concatena s1 + s2 devolviendo nuevo buffer y libera s1 */
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

/* Validación mínima de argumentos: exactamente 1 mapa y extensión .ber */
void	ft_argv_checker(int argc, char **argv)
{
	char	*slash;
	char	*name;
	int		len;

	if (argc != 2)
	{
		ft_printf("Error\nCantidad args incorrecto\n");
		exit(1);
	}
	slash = ft_strrchr(argv[1], '/');
	if (slash)
		name = slash + 1;
	else
		name = argv[1];
	len = ft_strlen(name);
	if (len <= 4 || ft_strncmp(name + (len - 4), ".ber", 4) != 0)
	{
		ft_printf("Error\nExtension\n");
		exit(1);
	}
}

/* Cuenta líneas en el buffer crudo sin sobrecontar si termina en '\n' */
static int	count_lines_raw(const char *s)
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

/* Cuenta líneas del split */
static int	count_lines_split(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

/* Lee el mapa, valida casos básicos y construye game->map.full */
t_game	*ft_init_map(char *path)
{
	t_game	*game;
	char	*map_temp;
	char	*line_temp;
	char	*tmp;
	int		fd;
	int		raw_lines;
	int		split_lines;
	int		line_count;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nAl abrir el fichero\n");
		exit(1);
	}
	map_temp = ft_strdup("");
	if (!map_temp)
	{
		close(fd);
		ft_printf("Error\n");
		exit(1);
	}
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		close(fd);
		free(map_temp);
		ft_printf("Error\n");
		exit(1);
	}
	game->map_alloc_bool = false;
	line_count = 0;
	while (1)
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
			ft_error_msg("Error al iniciar el mapa3\n", game);
		}
		map_temp = tmp;
		line_count++;
	}
	close(fd);
	if (line_count == 0)
	{
		free(map_temp);
		free(game);
		ft_printf("Error\nMapa vacio\n");
		exit(1);
	}
	raw_lines = count_lines_raw(map_temp);
	game->map.full = ft_split(map_temp, '\n');
	if (!game->map.full)
	{
		free(map_temp);
		ft_error_msg("Error al iniciar el mapa4\n", game);
	}
	split_lines = count_lines_split(game->map.full);
	if (raw_lines != split_lines)
	{
		free(map_temp);
		ft_error_msg("Se ha encontrado una linea vacia en el mapa\n", game);
	}
	game->map.rows = split_lines;
	game->map_alloc_bool = true;
	free(map_temp);
	return (game);
}
