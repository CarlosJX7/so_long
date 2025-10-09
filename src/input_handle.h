/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:16:18 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/10/09 18:16:19 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_HANDLE_H
# define INPUT_HANDLE_H

# include "so_long.h"
# include "exit_game.h"
# include "map_render.h"

int		ft_input_handle(int keysym, t_game *game);
void	ft_player_movement(t_game *game, int new_x, int new_y, int sprite_p);

#endif
