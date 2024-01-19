NAME = cub3D

SRCS =	cub3D.c\
		parsing/parsing.c\
		parsing/map_utils.c\
		parsing/parsing_etc.c\
		parsing/map_check.c\
		parsing/etc_utils.c\
		exec/exec.c\
		exec/Camera.c\
		exec/color_utils.c\
		exec/error.c\
		exec/getters.c\
		exec/keybinds.c\
		exec/loaders.c\
		exec/map_drawers.c\
		exec/math_utils.c\
		exec/raycaster.c\
		exec/raycasting_utils.c\

LIBFT = libft.a

LIBMLX = libmlx.a

HEADERS = 	includes/cub3D.h\
			includes/libft.h\

CFLAGS = -Wall -Wextra -Werror -DDEBUG=1

INCLUDES = -I ./includes

VPATH = src

LIBS = -L /usr/local/lib libmlx.a -lXext -lX11 -ldl -pthread -lm

all: $(NAME) 

$(NAME): $(SRCS) $(LIBFT) $(LIBMLX)
	@$(CC) $(CFLAGS) $^ $(INCLUDES) $(LIBFT) $(LIBMLX) $(LIBS) -o $(NAME) -g
	@echo "Compilation OK."

bonus: $(B_SRCS) $(LIBFT) $(LIBMLX) $(HEADERS)
	@$(CC) $(CFLAGS) $^ $(INCLUDES) $(LIBFT) $(LIBMLX) $(LIBS) -o $(NAME) -g
	@echo "Compilation OK."

$(LIBFT):
	@echo "Compiling libft."
	$(MAKE) -C libft
	@mv libft/$(LIBFT) .
	@$(MAKE) -s -C libft clean
	@echo "Libft OK."

$(LIBMLX):
	@echo "Compiling libmlx."
	@$(MAKE) -s -C minilibx-linux
	@mv minilibx-linux/$(LIBMLX) .
	@echo "Libmlx OK."

clean:
	@echo "Removing ./cub_3D."
	@rm -f $(NAME)

fclean:
	@echo "Removing ./cub_3D, libft.a and libmlx.a."
	@rm -f $(NAME) $(LIBFT) $(LIBMLX)

re: fclean all

# valgrind: clean all
# 	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes -s ./$(NAME) $(map)

.PHONY: all clean fclean re bonus