#include "check_path.h"

static void	dfs_visit(t_game *g, int x, int y, char *vis)
{
	int	cols;
	int	rows;
	int	idx;

	cols = g->map.col;
	rows = g->map.rows;
	if (!in_bounds(x, y, cols, rows))
		return ;
	if (!is_passable(g->map.full[y][x]))
		return ;
	idx = y * cols + x;
	if (vis[idx])
		return ;
	vis[idx] = 1;
	dfs_visit(g, x + 1, y, vis);
	dfs_visit(g, x - 1, y, vis);
	dfs_visit(g, x, y + 1, vis);
	dfs_visit(g, x, y - 1, vis);
}

static int	in_bounds_check(int x, int y, t_game *g, char *vis)
{
	if (in_bounds(x + 1, y, g->map.col, g->map.rows)
		&& vis[y * g->map.col + (x + 1)])
		return (1);
	if (in_bounds(x - 1, y, g->map.col, g->map.rows)
		&& vis[y * g->map.col + (x - 1)])
		return (1);
	if (in_bounds(x, y + 1, g->map.col, g->map.rows)
		&& vis[(y + 1) * g->map.col + x])
		return (1);
	if (in_bounds(x, y - 1, g->map.col, g->map.rows)
		&& vis[(y - 1) * g->map.col + x])
		return (1);
	return (0);
}

static int	exit_adjacent_reached(t_game *g, char *vis)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->map.rows)
	{
		x = 0;
		while (x < g->map.col)
		{
			if (g->map.full[y][x] == MAP_EXIT)
			{
				if (in_bounds_check(x, y, g, vis))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

static int	count_reached_coins(t_game *g, char *vis)
{
	int	x;
	int	y;
	int	cols;
	int	cnt;

	cols = g->map.col;
	cnt = 0;
	y = 0;
	while (y < g->map.rows)
	{
		x = 0;
		while (x < g->map.col)
		{
			if (g->map.full[y][x] == COINS && vis[y * cols + x])
				cnt++;
			x++;
		}
		y++;
	}
	return (cnt);
}

int	run_dfs_check(t_game *g)
{
	int		start;
	char	*vis;
	int		reach_c;

	vis = calloc(g->map.col * g->map.rows, sizeof(char));
	if (!vis)
		ft_error_msg("DFS ft_calloc error", g);
	start = g->map.player.y * g->map.col + g->map.player.x;
	dfs_visit(g, start % g->map.col, start / g->map.col, vis);
	reach_c = count_reached_coins(g, vis);
	if (!(reach_c == g->map.coins && exit_adjacent_reached(g, vis)))
	{
		free(vis);
		return (0);
	}
	free(vis);
	return (1);
}
