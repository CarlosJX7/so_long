#include "free_memory.h"



void	ft_destroy_images(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->wall_img.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->floor_img.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->coin_img.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_back_img.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_front_img.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_left_img.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_right_img.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->gate_closed_img.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->gate_open_img.xpm_ptr);
}

void	ft_free_map(t_game *game)
{
	int actual_row;
	actual_row = 0;
	
	while (actual_row < game->map.rows)
	{
		free(game->map.full[actual_row]);
		actual_row++;
	}
	free(game->map.full);
}


void	ft_free_all_allocated_memory(t_game *game)
{
	if (!game)
	{
		return ;
	}
	
	ft_destroy_images(game);
	ft_free_map(game);
	if (game->mlx_ptr && game->win_ptr)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	free(game);
}