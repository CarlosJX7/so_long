#include "free_memory.h"



void ft_destroy_xpm(void *mlx_ptr, void *xpm_ptr)
{
	if (mlx_ptr && xpm_ptr)
		mlx_destroy_image(mlx_ptr, xpm_ptr);
}

void	ft_destroy_images(t_game *game)
{
	if (!game || !game->mlx_ptr)
		return ;
	ft_destroy_xpm(game->mlx_ptr, game->wall_img.xpm_ptr);
	ft_destroy_xpm(game->mlx_ptr, game->floor_img.xpm_ptr);
	ft_destroy_xpm(game->mlx_ptr, game->coin_img.xpm_ptr);
	ft_destroy_xpm(game->mlx_ptr, game->player_back_img.xpm_ptr);
	ft_destroy_xpm(game->mlx_ptr, game->player_front_img.xpm_ptr);
	ft_destroy_xpm(game->mlx_ptr, game->player_left_img.xpm_ptr);
	ft_destroy_xpm(game->mlx_ptr, game->player_right_img.xpm_ptr);
	ft_destroy_xpm(game->mlx_ptr, game->gate_closed_img.xpm_ptr);
	ft_destroy_xpm(game->mlx_ptr, game->gate_open_img.xpm_ptr);
}

void	ft_free_map(t_game *game)
{
	int i;

	if (!game || !game->map_alloc_bool || game->map.full)
		return ;
	i = 0;
	while (game->map.full[i])
	{
		free(game->map.full[i]);
		i++;
	}
	free(game->map.full);
	game->map.full = NULL;
	game->map_alloc_bool = false;
}


void	ft_free_all_allocated_memory(t_game *game)
{
	if (!game)
		return ;
	ft_destroy_images(game);
	ft_free_map(game);
	if (game->mlx_ptr && game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
		mlx_destroy_display(game->mlx_ptr);
	if (game->mlx_ptr)
	{
		free(game->mlx_ptr);
		game->mlx_ptr = NULL;
	}
	free(game);
}