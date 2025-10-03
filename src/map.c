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



void	ft_argv_check(int argc, char **argv, t_game *game)
{
	int map_len;
	//char *extension;

	game->map_alloc_bool = false;
	if (argc > 2)
	{
		ft_error_msg("Tamaño incorrecto de argumentos\n", game); //Seguramente podamos liberar mejor
	}
	if (argc < 2)
		ft_error_msg("Necesario añadir el parametro de mapa\n", game);
	map_len = ft_strlen(argv[1]);
	//extension = argv[1] + map_len - ft_strlen(".ber");
	//if (!ft_strnstr(extension, ".ber", 4))
	if (map_len < 4 || ft_strncmp(argv[1] + (map_len - 4), ".ber", 4) != 0)
		ft_error_msg("Extension del mapa incorrecta\n", game);	
}

void	ft_line_check(char *map, t_game *game)
{
	//int i;
	int len;

	//i = 0;
	len = ft_strlen(map);
	if (map[0] == '\n' || ft_strnstr(map, "\n\n", len) || map[len - 1] == '\n')
	{
		free(map);
		ft_error_msg("Se ha encontrado una linea vacia en el mapa\n", game);
	}
}

void	ft_init_map(t_game *game, char *argv)
{
	char *map_temp;
	char *line_temp;
	int map_fd;
	char *tmp;

	map_fd = open(argv, O_RDONLY);
	if (map_fd == -1)
		ft_error_msg("Error al abrir el mapa1\n", game);
	map_temp = ft_strdup(""); //malloc
	if (!map_temp)
	{
		close(map_fd);
		ft_error_msg("Error al iniciar el mapa2\n", game);
	}
	game->map.rows = 0;
	while (true) // por que funciona con true?
	{
		line_temp = get_next_line(map_fd);
		if (!line_temp)
			break ;
		tmp = ft_strjoin_free(map_temp, line_temp); //malloc
		free(line_temp);
		if (!tmp)
		{
			close(map_fd);
			ft_error_msg("Error al iniciar el mapa3\n", game);
		}
		map_temp = tmp; //que pasaria com temp?
		game->map.rows++;
	}
	close(map_fd);
	ft_line_check(map_temp, game);
	game->map.full = ft_split(map_temp, '\n'); //el append tiene ** nosotros solo *
	if (!game->map.full)
	{
		free(game->map.full);
		ft_error_msg("Error al iniciar el mapa4", game);
	}
	game->map_alloc_bool = true;
	free(map_temp);
	//free(line_temp);
}