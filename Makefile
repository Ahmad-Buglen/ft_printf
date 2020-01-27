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

OBJ1 = main.o

NAME = libftprintf.a

MAIN = main

LIB = libft/libft.a

HEADER = ./includes/ft_printf.h

all: $(LIB) $(NAME) $(PFT) $(MAIN)

$(LIB):
	make -C ./libft
$(NAME): $(OBJ) $(LIB) includes/ft_printf.h
	ar rc $(NAME) $(OBJ)
	make -C ./pft
$(MAIN): $(NAME) includes/ft_printf.h 
	gcc sources/main.c -o $(MAIN) $(LIB) -lmlx $(NAME)
	./pft/test c 
	gcc -g sources/main.c sources/ft_printf.c -o ft_printf -lmlx  libft/libft.a libftprintf.a
#-Wall -Wextra -Werror
%.o: sources/%.c $(HEADER)
	gcc -c $<
clean:
	make clean -C ./libft
	rm -rf $(OBJ) $(OBJ1)
fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME) $(MAIN)
re: fclean all