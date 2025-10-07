/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student                                                           */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "map_check.h"
#include <unistd.h>
#include <stdlib.h>

/* Emite una sola línea y aborta; ajusta los textos si tu tester requiere otros */
static void die_line(char *s, t_game *game)
{
	ft_error_msg(s, game);
}

/* 1) Rectangularidad + caracteres + conteo y posición de P */
static void check_rect_and_count(t_game *g)
{
	int   i;
	int   j;
	int   cols;
	char  **m;
	char  c;

	m = g->map.full;
	if (!m || !m[0])
		die_line("Error", g); /* mapa vacío o split fallido */
	cols = (int)ft_strlen(m[0]);
	g->map.coins = 0;
	g->map.exit = 0;
	g->map.players = 0;
	i = 0;
	while (m[i])
	{
		if ((int)ft_strlen(m[i]) != cols)
			die_line("No rectangular", g);
		j = 0;
		while (m[i][j])
		{
			c = m[i][j];
			if (c != WALL && c != FLOOR && c != COINS
			 && c != PLAYER && c != MAP_EXIT)
				die_line("Wrong characters", g);
			if (c == COINS)
				g->map.coins++;
			else if (c == MAP_EXIT)
				g->map.exit++;
			else if (c == PLAYER)
			{
				g->map.players++;
				g->map.player.x = j;
				g->map.player.y = i;
			}
			j++;
		}
		i++;
	}
	g->map.rows = i;
	g->map.col = cols;
}

/* 2) Muros envolventes (y tamaño mínimo para poder cerrarlo) */
static void check_walls(t_game *g)
{
	int   i;
	int   cols = g->map.col;
	int   rows = g->map.rows;
	char  **m = g->map.full;

	if (rows < 3 || cols < 3)
		die_line("Not surrounded by walls", g);
	i = 0;
	while (i < cols)
	{
		if (m[0][i] != WALL || m[rows - 1][i] != WALL)
			die_line("Not surrounded by walls", g);
		i++;
	}
	i = 0;
	while (i < rows)
	{
		if (m[i][0] != WALL || m[i][cols - 1] != WALL)
			die_line("Not surrounded by walls", g);
		i++;
	}
}

/* 3) Cantidades exactas de entidades */
static void check_counts(t_game *g)
{
	if (g->map.players == 0)
		die_line("No player", g);
	if (g->map.players > 1)
		die_line("Duplicate player", g);
	if (g->map.exit == 0)
		die_line("No exit", g);
	if (g->map.exit > 1)
		die_line("Duplicate exit", g);
	if (g->map.coins < 1)
		die_line("No object", g);
}

/* Punto de entrada único; no llamar a otros validadores en paralelo */
void	map_check(t_game *game)
{
	check_rect_and_count(game);
	check_walls(game);
	check_counts(game);
	/* El pathfinding se añadirá más tarde */
}
