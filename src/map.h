#ifndef MAP_H
# define MAP_H

# include "so_long.h"
# include "so_long_utils.h"
# include "exit_game.h"
# include "../utils/get_next_line/get_next_line.h"

void	ft_line_check(char *map, t_game *game);
t_game	*ft_init_map(int fd);

#endif