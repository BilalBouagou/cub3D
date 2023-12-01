# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-hadr < yel-hadr@student.1337.ma>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 12:14:02 by bbouagou          #+#    #+#              #
#    Updated: 2023/12/01 22:19:06 by yel-hadr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -O3

DEPS = libft.h

OBJ = ft_isalnum.o ft_isalpha.o ft_isascii.o ft_isdigit.o ft_strcmp.o ft_isprint.o\
ft_memset.o ft_strchr.o ft_strlen.o ft_strncmp.o ft_strrchr.o ft_toupper.o ft_tolower.o\
ft_memchr.o ft_bzero.o ft_memcmp.o ft_memcpy.o ft_memmove.o ft_strlcpy.o ft_strlcat.o\
ft_strnstr.o ft_atoi.o ft_calloc.o ft_strdup.o ft_substr.o ft_strjoin.o ft_strtrim.o\
ft_split.o ft_itoa.o ft_strmapi.o ft_strisdigit.o ft_striteri.o ft_putchar_fd.o ft_putstr_fd.o\
ft_putendl_fd.o ft_putnbr_fd.o ft_lstnew.o ft_lstadd_front.o ft_lstsize.o ft_lstlast.o\
ft_lstadd_back.o ft_lstclear.o\
get_next_line.o get_next_line_utils.o ft_split_whitespace.o char_is_whitespace.o

%.o: %.c $(DEPS)
	@$(CC) -c $< $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re