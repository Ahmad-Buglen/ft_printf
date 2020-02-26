# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 12:34:53 by dphyliss          #+#    #+#              #
#    Updated: 2020/02/26 17:04:08 by dphyliss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

SRC = ft_printf.c

OBJ = $(SRC:.c=.o)

OBJ1 = main.o

NAME = libftprintf.a

MAIN = main

LIB = libft/libft.a

HEADER = ./includes/ft_printf.h

all: $(LIB) $(NAME) $(MAIN)

$(LIB):
	make -C ./libft
$(NAME): $(OBJ) $(LIB) 
	ar rc $(NAME) $(OBJ) libft/*.o
	make -C ./pft
#libft/*.o
$(MAIN): $(NAME) $(OBJ1)
	gcc sources/main.c -o $(MAIN) $(LIB) -lmlx $(NAME)
	./pft/test 1313 1347
	gcc -g sources/main.c sources/ft_printf.c -o ft_printf  libftprintf.a
#-Wall -Wextra -Werror
%.o: sources/%.c $(HEADER)
	gcc -c $<
clean:
	make clean -C ./libft
	rm -rf $(OBJ) $(OBJ1) ft_printf
fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME) $(MAIN)
re: fclean all