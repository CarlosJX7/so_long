#ifndef SO_LONG_UTILS_H
# define SO_LONG_UTILS_H

# include <unistd.h>
# include "../utils/Libft/libft.h"
# include "so_long.h"

char	*ft_strjoin_free(char *s1, char *s2);
int		count_lines_split(char **arr);
int		is_passable(char c);
int		in_bounds(int x, int y, int w, int h);

#endif