/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:12:46 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/10/09 18:12:53 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_path.h"

static void	ft_dfs_visit(t_game *g, int x, int y, char *vis)
{
	int	cols;
	int	rows;
	int	idx;

	cols = g->map.col;
	rows = g->map.rows;
	if (!ft_in_bounds(x, y, cols, rows))
		return ;
	if (!ft_is_passable(g->map.full[y][x]))
		return ;
	idx = y * cols + x;
	if (vis[idx])
		return ;
	vis[idx] = 1;
	ft_dfs_visit(g, x + 1, y, vis);
	ft_dfs_visit(g, x - 1, y, vis);
	ft_dfs_visit(g, x, y + 1, vis);
	ft_dfs_visit(g, x, y - 1, vis);
}

static int	ft_in_bounds_check(int x, int y, t_game *g, char *vis)
{
	if (ft_in_bounds(x + 1, y, g->map.col, g->map.rows)
		&& vis[y * g->map.col + (x + 1)])
		return (1);
	if (ft_in_bounds(x - 1, y, g->map.col, g->map.rows)
		&& vis[y * g->map.col + (x - 1)])
		return (1);
	if (ft_in_bounds(x, y + 1, g->map.col, g->map.rows)
		&& vis[(y + 1) * g->map.col + x])
		return (1);
	if (ft_in_bounds(x, y - 1, g->map.col, g->map.rows)
		&& vis[(y - 1) * g->map.col + x])
		return (1);
	return (0);
}

static int	ft_exit_adjacent_reached(t_game *g, char *vis)
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
				if (ft_in_bounds_check(x, y, g, vis))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

static int	ft_count_reached_coins(t_game *g, char *vis)
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

int ft_run_dfs_check(t_game *g)
{
    char *vis = ft_calloc(g->map.col * g->map.rows, sizeof(char));
    int  reach_c;

    if (!vis)
        ft_error_msg("DFS ft_calloc error", g);
    ft_dfs_visit(g, g->map.player.x, g->map.player.y, vis);
    reach_c = ft_count_reached_coins(g, vis);
    if (!(reach_c == g->map.coins && ft_exit_adjacent_reached(g, vis)))
    {
        free(vis);
        return 0;
    }
    free(vis);
    return 1;
}
