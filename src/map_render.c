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

void	ft_render_sprite(t_game *game, t_image sprite, int row, int col)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, sprite.xpm_ptr, col * sprite.x, row * sprite.y);
}

void	ft_render_player(t_game *game, int y, int x)
{
	if (game->player_sprite == FRONT)
		ft_render_sprite(game, game->player_front_img, y, x);
	if (game->player_sprite == BACK)
		ft_render_sprite(game, game->player_back_img, y, x);
	if (game->player_sprite == LEFT)
		ft_render_sprite(game, game->player_left_img, y, x);
	if (game->player_sprite == RIGHT)
		ft_render_sprite(game, game->player_right_img, y, x);
	//ft_print_movements(game);
	ft_printf("Movimientos: %d\n", game->movements);
}

void	ft_render_map_char(t_game *game, int y, int x)
{
	char	parameter;

	parameter = game->map.full[y][x];
	if (parameter == WALL)
		ft_render_sprite (game, game->wall_img, y, x);
	else if (parameter == FLOOR)
		ft_render_sprite (game, game->floor_img, y, x);
	else if (parameter == COINS)
		ft_render_sprite (game, game->coin_img, y, x);
	else if (parameter == MAP_EXIT)
	{
		if (game->map.coins == 0)
			ft_render_sprite (game, game->gate_open_img, y, x);
		else
			ft_render_sprite (game, game->gate_closed_img, y, x);
	}
	else if (parameter == PLAYER)
		ft_render_player (game, y, x);
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
			ft_render_map_char(game, y, x);
			x++;
		}
		y++;
	}
	return 0;
}