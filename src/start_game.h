#ifndef START_GAME_H
# define START_GAME_H

# include "so_long.h"
#include "start_game.h"
#include "exit_game.h"

void	ft_init_params(t_game *game);
void	ft_init_mlx(t_game *game);
t_image	ft_new_sprite(void *mlx, char *path, t_game *game); // checkear por que aqui no usamos un puntero
void	ft_init_sprites(t_game *game);

#endif