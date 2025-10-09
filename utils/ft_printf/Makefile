# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cinaquiz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 16:11:07 by cinaquiz          #+#    #+#              #
#    Updated: 2025/10/09 19:48:00 by cinaquiz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = libftprintf.a

# Rutas
LIBFT_DIR   = ../libft
LIBFT       = $(LIBFT_DIR)/libft.a

# Herramientas
CC          = cc
CFLAGS      = -Wall -Werror -Wextra -I$(LIBFT_DIR)
AR          = ar
ARFLAGS     = rcs

# Fuentes propias de ft_printf (sin duplicar funciones ya existentes en libft)
# Si tenías helpers duplicados en ft_utils.c, elimínalo de SRCS y usa libft.h.
SRCS        = ft_hex.c ft_unsigned.c ft_ptr.c ft_printf.c

OBJS        = $(SRCS:.c=.o)

# Objetivos
.PHONY: all clean fclean re libft

all: libft $(NAME)

# Construye la librería estática de ft_printf
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

# Asegura que la libft original existe y está actualizada
libft:
	$(MAKE) -C $(LIBFT_DIR) all

# Limpiezas
clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
