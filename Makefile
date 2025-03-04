# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albelope <albelope@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 20:15:52 by pablogon          #+#    #+#              #
#    Updated: 2025/02/27 19:36:51 by albelope         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
##                              COMPILATION INFO                              ##
################################################################################

NAME:= cub3D

CFLAGS:= -g -Wall -Werror -Wextra \
		# -g -fsanitize=address,undefined \
		#-Wunreachable-code -Ofast \

CUB3D = include/

MLX_DIR = ./MLX42/build
MLX		= $(MLX_DIR)/libmlx42.a
MLX_BUILD := $(MLX_DIR)/libmlx42.a
LINK	= -ldl -lglfw -lpthread -lm

LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a

HEADERS := -I include -I$(LIBFT_DIR) -I$(MLX)

################################################################################
##                              SOURCE AND OBJECTS                            ##
################################################################################

SRCS	:=	src/check_color.c \
			src/check_file.c \
			src/check_map.c \
			src/create_game.c \
			src/error.c \
			src/free.c \
			src/ft_dda_algorithm.c \
			src/init_and_memory.c \
			src/main.c\
			src/map.c \
			src/moving.c \
			src/player_position.c \
			src/raycasting.c \
			src/textures.c \
			src/utils.c \


OBJS	:= ${SRCS:.c=.o}

################################################################################
##                                   COLORS                                   ##
################################################################################

END=\033[0m
BOLD=\033[1m
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[33m
BLUE=\033[0;34m
MAGENTA=\033[35m
CYAN=\033[36m
WHITE=\033[37m

################################################################################
##                                   RULES                                    ##
################################################################################

all: head libft mlx42 line $(NAME)

head:
	@echo "$(CYAN)$(BOLD)"
	@echo "\t ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ "
	@echo "\t██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗"
	@echo "\t██║     ██║   ██║██████╔╝ █████╔╝██║  ██║"
	@echo "\t██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║"
	@echo "\t╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝"
	@echo "\t ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ "
	@echo "$(END)"
	@echo "$(YELLOW)$(BOLD)\t🛠️ 42MLG: $(END)$(WHITE)albelope & pablogon$(END)"
	@echo "$(PURPLE)\t📂 Project:$(END) $(CYAN)cub3d$(END)"
	@echo "$(GREEN)\t🔹 Commands: $(BOLD)all clean fclean re$(END)"
	@echo "$(BLUE)\t🧰 Compiler: $(BOLD)$(CC)$(END)\n"

libft:
	@echo "$(CYAN)🔧 Building Libft...$(END)\n"
	@make -s -C $(LIBFT_DIR)

mlx42: $(MLX_BUILD)

$(MLX_BUILD):
	@echo "$(CYAN)🔧 Building mlx42...$(END)\n"
	@if [ ! -d "$(MLX_DIR)" ]; then \
		mkdir -p $(MLX_DIR) && cmake -B $(MLX_DIR) MLX42; \
	fi
	@make -C $(MLX_DIR) -j4

$(NAME): $(OBJS)
	@echo "$(BLUE)✦ ---------------------- ✦$(END)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(HEADERS) $(LINK) -lreadline -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) built successfully!$(END)\n"

%.o: %.c $(CUB3D)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@echo "$(GREEN) ✓ Compiled: $(notdir $<)$(END)" 

line:
	@echo "$(GREEN)$(BOLD)"
	@echo " 🚀 COMPILING CUB3D...$(END) $(GREEN)"
	@echo "✦ ---------------------- ✦$(END)"

clean:
	@echo "\n$(YELLOW)🧹 Cleaning up object files...$(END)"
	@$(RM) $(OBJS)
	@echo "$(RED)✓ Removed objects from $(NAME)$(END)"
	@make clean -s -C $(LIBFT_DIR)
	@make clean -s -C $(MLX_DIR)

fclean: clean
	@echo "\n$(YELLOW)🗑️ Full cleanup: removing $(NAME) executable...$(END)"
	@$(RM) $(NAME)
	@make fclean -s -C $(LIBFT_DIR)
	@make clean -s -C $(MLX_DIR)
	@echo "$(RED)✓ Removed $(NAME) executable$(END)\n"

re: fclean all

.PHONY: all clean fclean re libft