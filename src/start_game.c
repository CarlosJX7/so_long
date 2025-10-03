#include "start_game.h"

void	ft_init_params(t_game *game)
{
	//game->map_alloc_bool = false;
	game->map.coins = 0;
	game->map.exit = 0;
	game->map.players = 0;
	game->movements = 0;
	game->map.col = (int)ft_strlen(game->map.full[0]); 
	//game->map.col = ft_strlen(game->map.full[0]) - 1;
	game->player_sprite = RIGHT;
}

void	ft_init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
	{
		//free(game->mlx_ptr);
		ft_error_msg("Error al iniciar la MLX", game);
	}
	game->win_ptr = (mlx_new_window(game->mlx_ptr, game->map.col * IMG_WIDTH, game->map.rows * IMG_HEIGHT, "so_long"));
	if (!game->win_ptr)
	{
		//mlx_destroy_display(game->mlx_ptr);
		//free(game->mlx_ptr);
		ft_error_msg("Error al crear la ventana\n", game);
	}
}

t_image	ft_new_sprite(void *mlx, char *path, t_game *game) // checkear por que aqui no usamos un puntero
{
	t_image sprite;

	sprite.xpm_ptr = mlx_xpm_file_to_image(mlx, path, &sprite.x, &sprite.y);//liberar
	if (!sprite.xpm_ptr)
		ft_error_msg("Error al generar el sprite\n", game);
	return sprite;
}

void	ft_init_sprites(t_game *game)
{
	void *mlx;

	mlx = game->mlx_ptr;
	game->wall_img = ft_new_sprite(mlx, WALL_XPM, game);
	game->floor_img = ft_new_sprite(mlx, FLOOR_XPM, game);
	game->coin_img = ft_new_sprite(mlx, COIN_XPM, game);
	game->player_back_img = ft_new_sprite(mlx, PLAYER_BACK_XPM, game);
	game->player_front_img = ft_new_sprite(mlx, PLAYER_FRONT_XPM, game);
	game->player_left_img = ft_new_sprite(mlx, PLAYER_LEFT_XPM, game);
	game->player_right_img = ft_new_sprite(mlx, PLAYER_RIGHT_XPM, game);
	game->gate_open_img = ft_new_sprite(mlx, GATE_OPEN_XPM, game);
	game->gate_closed_img = ft_new_sprite(mlx, GATE_CLOSED_XPM, game);
}