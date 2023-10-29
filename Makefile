NAME = cub3D
CC = cc
CFLAGS =  -Wextra -Wall -Werror -Wunreachable-code -Ofast -g3 -fsanitize=address

CFILES = ./src/main.c ./src/parsing/parser.c ./src/parsing/parser_utils.c ./src/rendering/renderer.c ./src/rendering/renderer_utils.c

LIBMLX	:= ./MLX42
HEADERS	:= -I ./inc -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit -lm

DEPS = ./inc/common.h ./inc/parser.h ./inc/renderer.h

SOURCES = $(CFILES:.c=.o)

LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a

all: $(LIBFT) $(DEPS) $(NAME) 


libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(SOURCES) $(DEPS)
	$(CC) $(CFLAGS) $(SOURCES) $(LIBFT) $(LIBS) $(HEADERS) -o $@

src/%.o: src/%.c $(DEPS)
	$(CC) $(CFLAGS) $< -c -o $@ $(HEADERS)

src/parsing/%.o: src/parsing/%.c $(DEPS)
	$(CC) $(CFLAGS) $< -c -o $@

src/rendering/%.o: src/rendering/%.c $(DEPS)
	@$(CC) $(CFLAGS) $< -c -o $@

clean :
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -rf	$(SOURCES)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re