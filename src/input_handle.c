#include "input_handle.h"

int		ft_input_handle(int keysym, t_game *game)
{
	if (keysym == KEY_W)
		ft_player_movement(game, game->map.player.y -1, game->map.player.x, BACK);
	if (keysym == KEY_A)
		ft_player_movement(game, game->map.player.y, game->map.player.x - 1, LEFT);
	if (keysym == KEY_D)
		ft_player_movement(game, game->map.player.y, game->map.player.x + 1, RIGHT);
	if (keysym == KEY_S)
		ft_player_movement(game, game->map.player.y + 1, game->map.player.x, FRONT);
	if (keysym == KEY_ESC)
		ft_close_game(game);
	return 0;
}

// input_handle.c
static int in_bounds(t_game *g, int y, int x)
{
	return (y >= 0 && x >= 0 && y < g->map.rows && x < g->map.col);
}

void ft_player_movement(t_game *game, int new_y, int new_x, int sprite_player)
{
	int old_x = game->map.player.x;
	int old_y = game->map.player.y;

	game->player_sprite = sprite_player;
	if (!in_bounds(game, new_y, new_x))
		return;
	if (game->map.full[new_y][new_x] == WALL)
		return;
	if (game->map.full[new_y][new_x] == MAP_EXIT && game->map.coins == 0)
		return (void)ft_close_game_win(game), (void)0;
	if (game->map.full[new_y][new_x] != FLOOR && game->map.full[new_y][new_x] != COINS)
		return;

	game->map.full[old_y][old_x] = FLOOR;
	if (game->map.full[new_y][new_x] == COINS)
		game->map.coins--;
	game->map.player.x = new_x;
	game->map.player.y = new_y;
	game->map.full[new_y][new_x] = PLAYER;
	game->movements++;
	ft_render_map(game);
}
