#include "map.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)ft_calloc((ft_strlen(s1) + ft_strlen(s2)) + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	free(s1);
	return (str);
}

/*
void	ft_argv_check(int argc, char **argv, t_game *game)
{
	int		map_len;
	//char *extension;

	game->map_alloc_bool = false;
	if (argc > 2)
		ft_error_msg("Tamaño incorrecto de argumentos\n", game); //Seguramente podamos liberar mejor
	if (argc < 2)
		ft_error_msg("Necesario añadir el parametro de mapa\n", game);
	map_len = ft_strlen(argv[1]);
	//extension = argv[1] + map_len - ft_strlen(".ber");
	//if (!ft_strnstr(extension, ".ber", 4))
	if (map_len < 4 || ft_strncmp(argv[1] + (map_len - 4), ".ber", 4) != 0)
		ft_error_msg("Extension del mapa incorrecta\n", game);
}
*/

void	ft_argv_checker(int argc, char **argv)
{
	char	*slash;
	char	*name;
	int		len;

	if (argc != 2)
	{
		ft_printf("Error\nCantidad args incorrecto\n");
		exit(0);
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
		exit(0);
	}
}



/* Cuenta las líneas del buffer bruto sin sobrecontar cuando acaba en '\n' */
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

/* Cuenta las líneas resultantes del split */
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

t_game	*ft_init_map(char *argv)
{
	t_game	*game;
	char	*map_temp;
	char	*line_temp;
	int		map_fd;
	char	*tmp;
	int		raw_lines;
	int		split_lines;

	map_fd = open(argv, O_RDONLY);
	if (map_fd == -1)
	{
		ft_printf("Error\nAl abrir el fichero");
		exit(1);
	}
	map_temp = ft_strdup("");
	if (!map_temp)
	{
		close(map_fd);
		ft_printf("Error\n");
		exit(1);
	}
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		ft_printf("Error\n");
		exit(1);
	}
	game->map_alloc_bool = false;
	game->map.rows = 0;
	while (true)
	{
		line_temp = get_next_line(map_fd);
		if (!line_temp && !game->map_alloc_bool)
		{
			close(map_fd);
			free(map_temp);
			free(game);
			ft_printf("Error\nMapa vacio\n");
			exit(1);
		}
		if (!line_temp && game->map_alloc_bool)
			break ;
		tmp = ft_strjoin_free(map_temp, line_temp);
		game->map_alloc_bool = true;
		free(line_temp);
		if (!tmp)
		{
			close(map_fd);
			ft_error_msg("Error al iniciar el mapa3\n", game);
		}
		map_temp = tmp;
		game->map.rows++;
	}
	close(map_fd);

	/* Comparación de líneas antes y después del split */
	raw_lines = count_lines_raw(map_temp);
	game->map.full = ft_split(map_temp, '\n');
	if (!game->map.full)
		ft_error_msg("Error al iniciar el mapa4", game);
	split_lines = count_lines_split(game->map.full);
	if (raw_lines != split_lines)
		ft_error_msg("Se ha encontrado una linea vacia en el mapa\n", game);

	game->map_alloc_bool = true;
	free(map_temp);
	return (game);
}
