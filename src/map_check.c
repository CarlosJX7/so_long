/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:23:38 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/10/09 18:23:42 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "map_check.h"

static void	ft_process_line_counts(t_game *g, const char *line, int row)
{
	int		j;
	char	c;

	j = 0;
	while (line[j])
	{
		c = line[j];
		if (c != WALL && c != FLOOR && c != COINS
			&& c != PLAYER && c != MAP_EXIT)
			ft_error_msg("Caracter invalido en el mapa", g);
		if (c == COINS)
			g->map.coins++;
		else if (c == MAP_EXIT)
			g->map.exit++;
		else if (c == PLAYER)
		{
			g->map.players++;
			g->map.player.x = j;
			g->map.player.y = row;
		}
		j++;
	}
}

static void	ft_check_rect_and_count(t_game *g)
{
	int		i;
	int		cols;
	char	**m;

	m = g->map.full;
	if (!m || !m[0])
		ft_error_msg("Mapa vacio", g);
	cols = (int)ft_strlen(m[0]);
	g->map.coins = 0;
	g->map.exit = 0;
	g->map.players = 0;
	i = 0;
	while (m[i])
	{
		if ((int)ft_strlen(m[i]) != cols)
			ft_error_msg("Mapa no rectangular", g);
		ft_process_line_counts(g, m[i], i);
		i++;
	}
	g->map.rows = i;
	g->map.col = cols;
}

/* 2) Muros envolventes (y tamaño mínimo para poder cerrarlo) */
static void	ft_check_walls(t_game *g)
{
	int		i;
	int		cols;
	int		rows;
	char	**m;

	cols = g->map.col;
	rows = g->map.rows;
	m = g->map.full;
	if (rows < 3 || cols < 3)
		ft_error_msg("Mapa demasiado pequeño", g);
	i = 0;
	while (i < cols)
	{
		if (m[0][i] != WALL || m[rows - 1][i] != WALL)
			ft_error_msg("No está rodeado de muros", g);
		i++;
	}
	i = 0;
	while (i < rows)
	{
		if (m[i][0] != WALL || m[i][cols - 1] != WALL)
			ft_error_msg("No está rodeado de muros", g);
		i++;
	}
}

/* 3) Cantidades exactas de entidades */
static void	ft_check_counts(t_game *g)
{
	if (g->map.players == 0)
		ft_error_msg("Jugador no encontrado", g);
	if (g->map.players > 1)
		ft_error_msg("Jugador duplicado", g);
	if (g->map.exit == 0)
		ft_error_msg("No se ha encontrado una salida", g);
	if (g->map.exit > 1)
		ft_error_msg("Salida duplicada", g);
	if (g->map.coins < 1)
		ft_error_msg("No se han encontrado objetos en el mapa", g);
}

/* Punto de entrada único; no llamar a otros validadores en paralelo */
void	ft_map_check(t_game *game)
{
	ft_check_rect_and_count(game);
	ft_check_walls(game);
	ft_check_counts(game);
}
