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

# Utils (libft, ft_printf, get_next_line)
UTILS_DIR     := utils
LIBFT_DIR     := $(UTILS_DIR)/libft
FT_PRINTF_DIR := $(UTILS_DIR)/ft_printf
GNL_DIR       := $(UTILS_DIR)/get_next_line

LIBFT      := $(LIBFT_DIR)/libft.a
FT_PRINTF  := $(FT_PRINTF_DIR)/libftprintf.a

# Fuentes del proyecto
SRCS := \
    so_long.c \
    start_game.c \
    input_handle.c \
    map_render.c \
    map_create.c \
    map_check.c \
    free_memory.c \
    exit_game.c \
    check_path.c \
    so_long_utils.c

# Prefijo directorio src
SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))

# get_next_line (compilar cualquier .c dentro de utils/get_next_line)
GNL_SRCS := $(wildcard $(GNL_DIR)/*.c)
SRCS += $(GNL_SRCS)

# Objetos y dependencias (mirroring de carpetas dentro de build/)
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# Compilación / Enlace
CC       := cc
CFLAGS   := -Wall -Wextra -Werror -MMD -MP \
            -I$(SRC_DIR) -I$(MLX_DIR) -I/usr/include \
            -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I$(GNL_DIR)
LDFLAGS  := -L$(MLX_DIR) -L/usr/lib
LDLIBS   := -lmlx_Linux -lXext -lX11 -lm -lz -lbsd

.DEFAULT_GOAL := all

.PHONY: all clean fclean re mlx mlx_clean deep_clean

# Objetivo principal
all: $(NAME)

# Enlace final: objetos -> ft_printf -> libft -> MLX/X11 (orden importa)
$(NAME): $(OBJS) $(FT_PRINTF) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(FT_PRINTF) $(LIBFT) $(LDFLAGS) $(LDLIBS) -o $@

# Compilación con dependencias automáticas
# Regla genérica que replica la jerarquía de directorios en build/
$(OBJ_DIR)/%.o: %.c $(MLX_HDR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# ---- MiniLibX ----
# Sentinel de cabecera: si falta, avisar y abortar
$(MLX_HDR):
	@test -f "$(MLX_HDR)" || { \
		printf "\033[1;33m[AVISO]\033[0m Falta '%s'. Ejecuta 'make mlx'.\n" "$(MLX_HDR)"; \
		exit 1; }

# Construcción de la librería: solo si existe la carpeta
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
		git clone --depth=1 https://github.com/42paris/minilibx-linux "$(MLX_DIR)" && \
		$(MAKE) -C "$(MLX_DIR)"; \
	fi

mlx_clean:
	rm -rf "$(MLX_DIR)"

# ---- Libft / ft_printf ----
$(LIBFT):
	$(MAKE) -C "$(LIBFT_DIR)" all

$(FT_PRINTF):
	$(MAKE) -C "$(FT_PRINTF_DIR)" all

# ---- Limpieza ----
clean:
	$(RM) -r "$(OBJ_DIR)"
	$(MAKE) -C "$(LIBFT_DIR)" clean || true
	$(MAKE) -C "$(FT_PRINTF_DIR)" clean || true

fclean: clean
	$(RM) "$(NAME)"
	$(MAKE) -C "$(LIBFT_DIR)" fclean || true
	$(MAKE) -C "$(FT_PRINTF_DIR)" fclean || true

deep_clean: fclean
	-$(MAKE) -C "$(MLX_DIR)" clean || true
	rm -rf "$(MLX_DIR)"

re: fclean all

# Dependencias generadas por -MMD
-include $(DEPS)
