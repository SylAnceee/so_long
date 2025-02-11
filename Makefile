# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I./includes -I./libft -I./mlx

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = lib/mlx
MLX = $(MLX_DIR)/libmlx.a

MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11

NAME = so_long

SRCS = src/main.c \
		src/parsing.c \
		src/utils.c \
		src/pathfinding.c \
		src/rendering.c \
		src/moves.c \
		src/utils_2.c 

OBJS = $(SRCS:.c=.o)

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

.PHONY: all clean fclean re bonus