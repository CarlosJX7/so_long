#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "so_long.h"

void	ft_destroy_images_mlx(t_game *game);
void	ft_free_map(t_game *game);
void ft_free_all(t_game *game);
int	ft_printf(const char *str, ...);
//5/5
#endif