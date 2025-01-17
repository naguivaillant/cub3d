# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsalhi <nsalhi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 14:39:48 by nassm             #+#    #+#              #
#    Updated: 2024/01/08 15:32:06 by nsalhi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX = -I . -L./include/minilibx-linux -lmlx -L/usr/X11/lib -lXext -lX11 -lm
LIBFT_PATH = ./include/libft/
LIBFT = $(LIBFT_PATH)libft.a
MINILIBXPATH = ./include/minilibx-linux/
MINILIBX = $(MINILIBXPATH)libmlx.a

SRC = ./src/main.c \
	./src/angle_convert.c \
	./src/check.c \
	./src/end_game.c \
	./src/frames.c \
	./src/get_a.c \
	./src/get_b.c \
	./src/init.c \
	./src/map_bis.c \
	./src/map_utils.c \
	./src/map.c \
	./src/mini_map.c \
	./src/mlx_hook_utils.c \
	./src/mlx_hook.c \
	./src/precalcul.c \
	./src/render_box.c \
	./src/render.c \
	./src/texture_utils.c \
	./src/texture.c \
	./src/utils.c \
	./src/utils_bis.c \

BONUS_SRC = ./bonus/main_bonus.c \
	./bonus/angle_convert_bonus.c \
	./bonus/check_bonus.c \
	./bonus/end_game_bonus.c \
	./bonus/frames_bonus.c \
	./bonus/get_a_bonus.c \
	./bonus/get_b_bonus.c \
	./bonus/init_bonus.c \
	./bonus/map_bis_bonus.c \
	./bonus/map_utils_bonus.c \
	./bonus/map_bonus.c \
	./bonus/mini_map_bonus.c \
	./bonus/mlx_hook_utils_bonus.c \
	./bonus/mlx_hook_bonus.c \
	./bonus/precalcul_bonus.c \
	./bonus/render_box_bonus.c \
	./bonus/render_bonus.c \
	./bonus/texture_utils_bonus.c \
	./bonus/texture_bonus.c \
	./bonus/utils_bonus.c \
	./bonus/utils_bis_bonus.c \

OBJ = $(SRC:.c=.o)

BONUSOBJ = $(BONUS_SRC:.c=.o)

$(NAME): $(OBJ) $(MINILIBX)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

$(NAME_BONUS) : $(BONUSOBJ) $(MINILIBX)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(BONUSOBJ) $(LIBFT) $(MLX) -o $(NAME_BONUS)

$(MINILIBX): 
	$(MAKE) -C $(MINILIBXPATH)

bonus : $(NAME_BONUS)

all: $(NAME)

clean:
	rm -rf $(OBJ) $(BONUSOBJ)
	make clean -C $(LIBFT_PATH)
	$(MAKE) -C $(MINILIBXPATH) clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re bonus
