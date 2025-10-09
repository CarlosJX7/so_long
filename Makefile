# =======================
#  so_long (Linux + MLX)
# =======================

NAME      := so_long

# Directorios
SRC_DIR   := src
OBJ_DIR   := build

# MiniLibX
MLX_DIR   := mlx
MLX_LIB   := $(MLX_DIR)/libmlx_Linux.a
MLX_HDR   := $(MLX_DIR)/mlx.h

# Libft
LIBFT_DIR := utils/Libft
LIBFT     := $(LIBFT_DIR)/libft.a

# Fuentes
SRCS := \
	so_long.c \
	start_game.c \
	input_handle.c \
	map_render.c \
	map.c \
	map_check.c \
	free_memory.c \
	exit_game.c \
	check_path.c \
	so_long_utils.c

SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# Compilación / Enlace
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -MMD -MP -I$(SRC_DIR) -I$(MLX_DIR) -I/usr/include -I$(LIBFT_DIR)
LDFLAGS := -L$(MLX_DIR) -L/usr/lib
LDLIBS  := -lmlx_Linux -lXext -lX11 -lm -lz -lbsd

.DEFAULT_GOAL := all

.PHONY: all clean fclean re mlx mlx_clean deep_clean

# Objetivo principal
all: $(NAME)

# Enlace final (sin relinks si nada ha cambiado)
$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) $(LDLIBS) -o $@

# Compilación con dependencias automáticas
# Nota: Añadimos la cabecera de MLX como prerequisito real para asegurar que existe.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(MLX_HDR) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# ---- MiniLibX ----
# Sentinel de cabecera: si falta, avisar y abortar (no ejecuta si el archivo existe).
$(MLX_HDR):
	@test -f "$(MLX_HDR)" || { \
		printf "\033[1;33m[AVISO]\033[0m Falta '%s'. Ejecuta 'make mlx'.\n" "$(MLX_HDR)"; \
		exit 1; }

# Construcción de la librería: solo si hace falta y existe la carpeta.
$(MLX_LIB):
	@test -d "$(MLX_DIR)" || { \
		printf "\033[1;33m[AVISO]\033[0m Falta el directorio '%s'. Ejecuta 'make mlx'.\n" "$(MLX_DIR)"; \
		exit 1; }
	@$(MAKE) -C "$(MLX_DIR)" >/dev/null

# Clona y compila MLX bajo demanda
mlx:
	@if [ -d "$(MLX_DIR)" ]; then \
		$(MAKE) -C "$(MLX_DIR)"; \
	else \
		git clone --depth=1 https://github.com/42Paris/minilibx-linux.git "$(MLX_DIR)" && \
		$(MAKE) -C "$(MLX_DIR)"; \
	fi

mlx_clean:
	rm -rf "$(MLX_DIR)"

# ---- Libft ----
$(LIBFT):
	$(MAKE) -C "$(LIBFT_DIR)" all

# ---- Limpieza ----
clean:
	$(RM) -r "$(OBJ_DIR)"
	$(MAKE) -C "$(LIBFT_DIR)" clean

fclean: clean
	$(RM) "$(NAME)"
	$(MAKE) -C "$(LIBFT_DIR)" fclean

deep_clean: fclean
	-$(MAKE) -C "$(MLX_DIR)" clean
	rm -rf "$(MLX_DIR)"

re: fclean all

# Dependencias generadas por -MMD
-include $(DEPS)
