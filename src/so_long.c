#include "so_long.h"
#include "map.h"
#include "start_game.h"
#include "map_check.h"
#include "map_render.h"
#include "input_handle.h"
#include "free_memory.h"
#include "check_path.h"

int main(int argc, char **argv)
{
	t_game *game;

	ft_argv_checker(argc, argv);
	//game = malloc(sizeof(t_game));
	//if (!game)
	//{
	//	return(1);
	//}
	
	//ft_argv_check(argc, argv, game);
	game = ft_init_map(argv[1]);
	//ft_map_check(game);
	map_check(game);
	check_path(game);
	ft_init_params(game);
	//ft_check_map(game);
	ft_init_mlx(game);
	ft_init_sprites(game);
	ft_render_map(game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, ft_input_handle, game);
	mlx_hook(game->win_ptr, DestroyNotify, ButtonPressMask, ft_close_game, game);
	// so_long.c
	mlx_hook(game->win_ptr, 17, 0L, ft_close_game, game);

	//mlx_hook(game->win_ptr, Expose, ExposureMask, ft_render_map, game);
	mlx_loop(game->mlx_ptr);
	ft_free_all_allocated_memory(game);	
	return 0;
}
