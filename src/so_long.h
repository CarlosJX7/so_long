/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:24:29 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/10/09 18:24:30 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdint.h>
# include "../utils/libft/libft.h"
# include "../utils/get_next_line/get_next_line.h"

# define IMG_WIDTH	32
# define IMG_HEIGHT	32

# define WALL		'1'
# define FLOOR		'0'
# define COINS		'C'
# define PLAYER		'P'
# define MAP_EXIT	'E'

# define WALL_XPM			"assets/sprites/muro.xpm"
# define FLOOR_XPM			"assets/sprites/suelo_verde.xpm"
# define COIN_XPM			"assets/sprites/monedas.xpm"
# define PLAYER_FRONT_XPM	"assets/sprites/capi_front.xpm"
# define PLAYER_LEFT_XPM	"assets/sprites/capi_left.xpm"
# define PLAYER_RIGHT_XPM	"assets/sprites/capi_right.xpm"
# define PLAYER_BACK_XPM	"assets/sprites/capi_back.xpm"
# define GATE_OPEN_XPM		"assets/sprites/open_salida.xpm"
# define GATE_CLOSED_XPM	"assets/sprites/closed_salida.xpm"

# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_ESC	65307

# define FRONT	1
# define LEFT	2
# define RIGHT	3
# define BACK	4

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_image
{
	void	*xpm_ptr;
	int		x;
	int		y;
}	t_image;

typedef struct s_map
{
	char		**full;
	int			rows;
	int			col;
	int			coins;
	int			exit;
	int			players;
	t_position	player;
}	t_map;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		movements;
	int		player_sprite;
	t_map	map;
	t_bool	map_alloc_bool;
	t_image	wall_img;
	t_image	floor_img;
	t_image	coin_img;
	t_image	gate_open_img;
	t_image	gate_closed_img;
	t_image	player_front_img;
	t_image	player_left_img;
	t_image	player_right_img;
	t_image	player_back_img;
}	t_game;

#endif
