# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dphyliss <admin@21-school.ru>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 12:34:53 by dphyliss          #+#    #+#              #
#    Updated: 2020/01/09 12:34:55 by dphyliss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

SRC = ft_printf.c

OBJ = $(SRC:.c=.o)

NAME = ft_printf

LIB = libft/libft.a

HEADER = ./includes/ft_printf.h

all: $(LIB) $(NAME)

$(LIB):
	make -C ./libft
$(NAME): $(OBJ) includes/ft_printf.h
	gcc -Wall -Wextra -Werror -o $(NAME) -I $(HEADER) $(LIB) -lmlx $(OBJ)
%.o: sources/%.c $(HEADER)
	gcc -c $<
clean:
	make clean -C ./libft
	rm -rf $(OBJ)
fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)
re: fclean all