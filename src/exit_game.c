#include "exit_game.h"


int ft_close_game_win(t_game *game)
{
	ft_printf("\nMovimientos: %d\n", ++game->movements);
	ft_free_all_allocated_memory(game);	
	exit(0);
}

int ft_close_game(t_game *game)
{
	ft_free_all_allocated_memory(game);
	exit(0);
}

int ft_error_msg(char *msg, t_game *game)
{
	ft_printf("Error\n>%s<\n", msg);
	if (game)
		ft_free_all_allocated_memory(game);
	exit(1);
}