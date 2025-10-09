/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:15:38 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/10/09 18:15:39 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_game.h"

int	ft_close_game_win(t_game *game)
{
	ft_printf("Movimientos: %d\n", ++game->movements);
	ft_free_all_allocated_memory(game);
	exit(0);
}

int	ft_close_game(t_game *game)
{
	ft_printf("Se ha cerrado el juego\n");
	ft_free_all_allocated_memory(game);
	exit(0);
}

int	ft_error_msg(char *msg, t_game *game)
{
	ft_printf("Error\n>%s<\n", msg);
	if (game)
		ft_free_all_allocated_memory(game);
	exit(1);
}
