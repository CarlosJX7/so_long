#include "so_long_utils.h"
/*
static void	ft_destroy_images_mlx(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->wall_img.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->floor_img.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->coin_img.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_front_img.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_left_img.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_back_img.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_right_img.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->gate_closed_img.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->gate_open_img.xpm_ptr);
}
*/
/*
static void	ft_free_mapppp(t_game *game)
{
	int	string;
	
	string = 0;
	while (string < game->map.rows)
	free(game->map.full[string++]);
	free(game->map.full);
	
}

*/


/*
void ft_free_all(t_game *game)
{
	if(game)
		ft_free_all_allocated_memory(game);
	//ft_destroy_images_mlx(game);
	//ft_free_map(game);
	ft_destroy_images_mlx(game);
	ft_free_mapppp(game);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	free(game);
}

*/
static int	ft_check_arguments(va_list arg, char c)
{
	int	bytes;

	bytes = 0;
	if (c == '%')
		bytes += ft_argument_percent();
	if (c == 'c')
		bytes += ft_argument_c(va_arg(arg, int));
	if (c == 's')
		bytes += ft_argument_s(va_arg(arg, char *));
	if (c == 'p')
		bytes += ft_argument_p(va_arg(arg, unsigned long));
	if (c == 'd' || c == 'i')
		bytes += ft_arguments_d_i(va_arg(arg, int));
	if (c == 'u')
		bytes += ft_argument_u(va_arg(arg, int));
	if (c == 'x' || c == 'X')
		bytes += ft_arguments_x(va_arg(arg, unsigned int), c);
	return (bytes);
}

int ft_printf(const char *str, ...)
{
    va_list arg;
    int i;
    int bytes;

    i = 0;
    bytes = 0;
    va_start(arg, str);
    while (str && str[i])
    {
        if (str[i] == '%')
        {
            if (str[i + 1] == '\0')
                break;
            bytes += ft_check_arguments(arg, str[i + 1]);
            i += 2;
            continue;
        }
        bytes += write(1, &str[i], 1);
        i++;
    }
    va_end(arg);
    return (bytes);
}
