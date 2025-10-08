# =======================
#  so_long (Linux + MLX)
# =======================

# --- Binario ---
NAME        := so_long

# --- Directorios ---
SRC_DIR     := src
OBJ_DIR     := build

# MiniLibX (en ./mlx, gestionada por reglas explícitas)
MLX_DIR     := mlx
MLX_REPO    := https://github.com/42Paris/minilibx-linux.git
MLX_HDR     := $(MLX_DIR)/mlx.h
MLX_LIB     := $(MLX_DIR)/libmlx_Linux.a

# Libft (se compila automáticamente)
LIBFT_DIR   := utils/Libft
LIBFT       := $(LIBFT_DIR)/libft.a

# --- Fuentes (enumera todas las .c del proyecto) ---
SRCS := \
	so_long.c \
	start_game.c \
	input_handle.c \
	map_render.c \
	map.c \
	map_check.c \
	free_memory.c \
	ft_printf.c \
	exit_game.c \
	check_path.c \
	so_long_utils.c

SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# --- Compilación / Enlace (Linux) ---
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -MMD -MP \
           -I$(SRC_DIR) -I$(MLX_DIR) -I/usr/include -I$(LIBFT_DIR)
LDFLAGS := -L$(MLX_DIR) -L/usr/lib
LDLIBS  := -lmlx_Linux -lXext -lX11 -lm -lz -lbsd

# =======================
#        Reglas
# =======================

.PHONY: all clean fclean re mlx mlx_clean check_mlx

all: $(NAME)

# Enlace final (sin relinks si nada ha cambiado)
$(NAME): $(OBJS) $(LIBFT) | check_mlx
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) $(LDLIBS) -o $@

# Compilación con dependencias automáticas; check_mlx como prerequisito de orden
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) check_mlx
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# =======================
#   Aviso si falta MLX
# =======================
check_mlx:
	@if [ ! -f "$(MLX_HDR)" ] || [ ! -f "$(MLX_LIB)" ]; then \
		printf "\033[1;33m[WARN]\033[0m MiniLibX no encontrada en '$(MLX_DIR)'.\n"; \
		printf "Ejecuta: \033[1mmake mlx\033[0m  (clonar y compilar MLX) o ajusta -I/-L.\n"; \
		exit 1; \
	fi

# =======================
#   Gestión de MiniLibX
# =======================
mlx:
	@if [ -d "$(MLX_DIR)" ]; then \
		echo "mlx ya existe en $(MLX_DIR)"; \
	else \
		git clone --depth=1 "$(MLX_REPO)" "$(MLX_DIR)" && \
		$(MAKE) -C "$(MLX_DIR)"; \
	fi

mlx_clean:
	@rm -rf "$(MLX_DIR)"

# =======================
#      Libft helpers
# =======================
$(LIBFT):
	$(MAKE) -C "$(LIBFT_DIR)" all

# =======================
#        Limpieza
# =======================
clean:
	$(RM) -r "$(OBJ_DIR)"

fclean: clean
	$(RM) "$(NAME)"

re: fclean all

# Incluir dependencias generadas por -MMD
-include $(DEPS)
