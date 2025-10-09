/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:24:25 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/10/09 18:24:27 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "map_create.h"
#include "start_game.h"
#include "map_check.h"
#include "map_render.h"
#include "input_handle.h"
#include "free_memory.h"
#include "check_path.h"
#include <fcntl.h>

void	ft_argv_checker(int argc, char **argv)
{
	char	*slash;
	char	*name;
	int		len;

	if (argc != 2)
	{
		ft_printf("Error\n>Cantidad args incorrecto<\n");
		return (0);
	}
	slash = ft_strrchr(argv[1], '/');
	if (slash)
		name = slash + 1;
	else
		name = argv[1];
	len = ft_strlen(name);
	if (len <= 4 || ft_strncmp(name + (len - 4), ".ber", 4) != 0)
	{
		ft_printf("Error\n>Extension no valida<\n");
		return (0);
	}
}

int	main(int argc, char **argv)
{
	t_game	*game;
	int		fd;

	ft_argv_checker(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error_msg(">Error al abrir el archivo<", NULL);
	game = ft_init_map(fd);
	ft_map_check(game);
	if (!ft_run_dfs_check(game))
		ft_error_msg("Error, no hay ruta válida a los objetivos", game);
	ft_init_params(game);
	ft_init_mlx(game);
	ft_init_sprites(game);
	ft_render_map(game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, ft_input_handle, game);
	mlx_hook(game->win_ptr, 17, 0L, ft_close_game, game);
	mlx_loop(game->mlx_ptr);
	ft_free_all_allocated_memory(game);
	return (0);
}
