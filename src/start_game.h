/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:24:58 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/10/09 18:24:59 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef START_GAME_H
# define START_GAME_H

# include "so_long.h"
# include "start_game.h"
# include "exit_game.h"

void		ft_init_params(t_game *game);
void		ft_init_mlx(t_game *game);
t_image		ft_new_sprite(void *mlx, char *path, t_game *game);
void		ft_init_sprites(t_game *game);

#endif
