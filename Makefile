# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/09 12:34:53 by dphyliss          #+#    #+#              #
#    Updated: 2020/06/27 14:16:29 by dphyliss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

SRC = ft_printf.c print_e.c print_f.c numb_sys.c parser.c print_char.c data_man.c

DIR_LIB = libft/

SRC_LIB = $(addprefix $(DIR_LIB),\
		ft_abs.c\
		ft_atoi.c\
		ft_bzero.c\
		ft_cinstr.c\
		ft_count_p.c\
		ft_pow.c \
		ft_putnstr.c\
		ft_strlen.c\
		ft_strncpy.c)

SRC_LIB_OBJ = $(SRC_LIB:.c=.o)

OBJ = $(SRC:.c=.o)

NAME = libftprintf.a

LIB = libft/libft.a

HEADER = ./includes/ft_printf.h

all: $(LIB) $(NAME)

$(LIB): $(SRC_LIB_OBJ)

$(NAME): $(OBJ) $(LIB)
	ar rc $(NAME) $(OBJ) $(SRC_LIB_OBJ)

%.o: sources/%.c $(HEADER)
	gcc -Wall -Wextra -Werror -c -O2 $<

clean:
	make clean -C ./libft
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME) $(LIB)

# make fclean -C ./libft
re: fclean all
