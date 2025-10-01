#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../utils/Libft/libft.h"



# define IMG_WIDTH 32
# define IMG_HEIGHT 32

# define WALL		'1'
# define FLOOR		'0'
# define COINS		'C'
# define PLAYER		'P'
# define MAP_EXIT	'E'

#define WALL_XPM			"assets/sprites/wall.xpm"
#define FLOOR_XPM			"assets/sprites/floor.xpm"
#define COIN_XPM			"assets/sprites/coin.xpm"
#define PLAYER_FRONT_XPM	"assets/sprites/player/front.xpm"
#define PLAYER_LEFT_XPM		"assets/sprites/player/left.xpm"
#define PLAYER_RIGHT_XPM	"assets/sprites/player/right.xpm"
#define PLAYER_BACK_XPM		"assets/sprites/player/back.xpm"
#define GATE_OPEN_XPM		"assets/sprites/gate_open.xpm"
#define GATE_CLOSED_XPM		"assets/sprites/gate_closed.xpm"

# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_ESC	65307

# define FRONT 1
# define LEFT 2
# define RIGHT 3
# define BACK 4

typedef enum e_bool { false, true} t_bool;

typedef struct s_position
{
	int	x;
	int	y;
} t_position;


typedef struct s_image
{
	void	*xpm_ptr;
	int		x;
	int		y;
}	t_image;

typedef struct s_map
{
	char	**full;
	int		rows;
	int		col;
	int		coins;
	int		exit;
	int		players;
	t_position player;
} t_map;

typedef struct s_game
{
	void *mlx_ptr;
	void *win_ptr;
	int movements;
	int player_sprite;
	t_map map;
	t_bool map_alloc_bool;
	t_image wall_img;
	t_image floor_img;
	t_image coin_img;
	t_image gate_open_img;
	t_image gate_closed_img;
	t_image player_front_img;
	t_image player_left_img;
	t_image player_right_img;
	t_image player_back_img;
} t_game;

#endif

/*
todo:
usar nuestro propio map_check
arreglar leak con ruta de sprite incorrecta
ver por que no nos esta cogiendo el mapa
ver lo que hace append en init_map
comparar las funciones con el original, no deberia de hacer falta nuevo codigo
*/