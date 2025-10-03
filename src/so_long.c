#include "so_long.h"
#include "map.h"
#include "start_game.h"
#include "map_check.h"
#include "map_render.h"
#include "input_handle.h"
#include "free_memory.h"

int main(int argc, char **argv)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (!game)
	{
		return(1);
	}
	
	ft_argv_check(argc, argv, game);
	ft_init_map(game, argv[1]);
	ft_init_params(game);
	//ft_map_check(game);
	ft_check_map(game);
	ft_init_mlx(game);
	ft_init_sprites(game);
	ft_render_map(game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, ft_input_handle, game);
	mlx_hook(game->win_ptr, DestroyNotify, ButtonPressMask, ft_close_game, game);
	mlx_hook(game->win_ptr, Expose, ExposureMask, ft_render_map, game);
	mlx_loop(game->mlx_ptr);
	ft_free_all_allocated_memory(game);	
	return 0;
}
