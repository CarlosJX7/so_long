# Nombre del programa
NAME := so_long

# Carpetas
SRC_DIR := src
INC_DIR := src
MLX_DIR := mlx
LIBFT_DIR := libraries/Libft
OBJ_DIR := build

# Fuentes (todas están en src/)
SRCS := so_long.c \
        start_game.c \
        input_handle.c \
        map_render.c \
        map.c \
        map_check.c \
        free_memory.c \
        so_long_utils.c \
        exit_game.c \
        check_path.c
SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))

# Objetos y dependencias
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# Compilador y flags
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -I$(INC_DIR) -I$(MLX_DIR)
LDFLAGS := -L$(MLX_DIR)
LDLIBS  := -lmlx_Linux -lXext -lX11 -lm -lz -lbsd

# Librerías
MLX_LIB := $(MLX_DIR)/libmlx_Linux.a
LIBFT   := $(LIBFT_DIR)/libft.a

# Regla por defecto
all: $(NAME)

# Enlazado: el binario depende de objetos y librerías
$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) $(LDLIBS) -o $@

# Compilación por archivo con dependencias automáticas (-MMD -MP)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Crear carpeta de objetos si no existe (prerrequisito de orden)
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Construir MLX solo si falta la librería
$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

# Construir libft (usa 'all' para evitar rehacer 'bonus' cada vez)
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

# Limpieza
clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# Incluir dependencias de headers (generadas por -MMD -MP)
-include $(DEPS)

.PHONY: all clean fclean re
