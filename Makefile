# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 12:34:53 by dphyliss          #+#    #+#              #
#    Updated: 2020/06/24 17:29:58 by dphyliss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

SRC = ft_printf.c print_e.c print_f.c numb_sys.c parser.c print_char.c data_man.c

OBJ = $(SRC:.c=.o)

NAME = libftprintf.a

LIB = libft/libft.a

HEADER = ./includes/ft_printf.h

all: $(LIB) $(NAME)

$(LIB):
	make -C ./libft

$(NAME): $(OBJ) $(LIB)
	ar rc $(NAME) $(OBJ) libft/*.o

%.o: sources/%.c $(HEADER)
	gcc -Wall -Wextra -Werror -c -O2 $<

clean:
	make clean -C ./libft
	rm -rf $(OBJ)

fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)

re: fclean all
