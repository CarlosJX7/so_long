#ifndef MAP_CHECK_H
# define MAP_CHECK_H

#include "so_long.h"
#include "exit_game.h"

void	ft_check_map(t_game *game);
void	ft_check_rows(t_game *game);
void	ft_check_columns(t_game *game);
void	ft_count_map_parameters(t_game *game);
void	ft_verify_map_parameters(t_game *game);

#endif