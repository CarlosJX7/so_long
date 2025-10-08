#ifndef EXIT_GAME_H
# define EXIT_GAME_H

# include "so_long.h"
# include "so_long_utils.h"
# include "free_memory.h"

int	ft_close_game_win(t_game *game);
int	ft_close_game(t_game *game);
int	ft_error_msg(char *msg, t_game *game);

#endif