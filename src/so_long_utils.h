/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:24:40 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/10/09 18:24:43 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_UTILS_H
# define SO_LONG_UTILS_H

# include <unistd.h>
# include "../utils/Libft/libft.h"
# include "so_long.h"

char	*ft_strjoin_free(char *s1, char *s2);
int		ft_count_lines_split(char **arr);
int		ft_is_passable(char c);
int		ft_in_bounds(int x, int y, int w, int h);

#endif
