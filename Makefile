# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 12:34:53 by dphyliss          #+#    #+#              #
#    Updated: 2020/06/23 19:21:14 by dphyliss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

SRC = ft_printf.c print_e.c print_f.c numb_sys.c parser.c

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
	# make -C ./pft
#libft/*.o
$(MAIN): $(NAME) $(OBJ1)
	gcc -g sources/main.c sources/ft_printf.c -o ft_printf  libftprintf.a
	gcc sources/main.c -o $(MAIN) -lmlx $(NAME)
	# ./pft/test
#-Wall -Wextra -Werror
%.o: sources/%.c $(HEADER)
	gcc -c -O2 $<
clean:
	make clean -C ./libft
	rm -rf $(OBJ) $(OBJ1) ft_printf
fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME) $(MAIN)
re: fclean all
