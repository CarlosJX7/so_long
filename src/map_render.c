#include "map_render.h"

void	ft_print_movements(t_game *game) //aun por usar 
{
	char *movs;
	char *cadena;

	movs = ft_itoa(game->movements);
	cadena = ft_strjoin("Cantidad de movimientos: ", movs);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 40, 20, 99999, cadena);
	free(movs);
	free(cadena);
}

void	ft_render_sprite(t_game *game, t_image sprite, int col, int row)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, sprite.xpm_ptr, col * sprite.x, row * sprite.y);
}

void	ft_render_player(t_game *game, int x, int y)
{
	if (game->player_sprite == FRONT)
		ft_render_sprite(game, game->player_front_img, x, y);
	if (game->player_sprite == BACK)
		ft_render_sprite(game, game->player_back_img, x, y);
	if (game->player_sprite == LEFT)
		ft_render_sprite(game, game->player_left_img, x, y);
	if (game->player_sprite == RIGHT)
		ft_render_sprite(game, game->player_right_img, x, y);
}

void	ft_render_map_char(t_game *game, int x, int y)
{
	char map_char;

	map_char = game->map.full[y][x];
	if (map_char == WALL)
		ft_render_sprite(game, game->wall_img, x, y);
	else if (map_char == FLOOR)
		ft_render_sprite(game, game->floor_img, x, y);
	else if (map_char == COINS)
		ft_render_sprite(game, game->coin_img, x, y);
	else if (map_char == MAP_EXIT)
	{
		if (game->map.coins == 0)
			ft_render_sprite(game, game->gate_open_img, x, y);
		else
			ft_render_sprite(game, game->gate_closed_img, x, y);
	}
	else if (map_char == PLAYER)
		ft_render_player(game, x, y);
}

int	ft_render_map(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (x < game->map.col)
		{
			ft_render_map_char(game, x, y);
			x++;
		}
		y++;
	}
	return 0;
}