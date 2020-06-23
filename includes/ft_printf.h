/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:12:57 by dphyliss          #+#    #+#             */
/*   Updated: 2020/06/23 19:19:50 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdarg.h>
# include "../libft/libft.h"


# define BUFF		1024
# define FLAGS	   "cp%sdiouxXfFeEbr"
# define LOWERCASE   "0123456789abcdef"
# define UPPERCASE   "0123456789ABCDEF"
# define WHOLE_LEN   1
# define PREC		19

/*
** Text colors
*/

# define BLACK		  "\e[30;1m"
# define RED			"\e[31;1m"
# define GREEN		  "\e[32;1m"
# define BROWN		  "\e[33;1m"
# define BLUE		   "\e[34;1m"
# define PURPLE		 "\e[35;1m"
# define CYAN		   "\e[36;1m"
# define LIGHTGRAY	  "\e[37;1m"

/*
** Background colors
*/

# define BLACK_BACK		  "\e[40;1m"
# define RED_BACK			"\e[41;1m"
# define GREEN_BACK		  "\e[42;1m"
# define BROWN_BACK		  "\e[43;1m"
# define BLUE_BACK		   "\e[44;1m"
# define PURPLE_BACK		 "\e[45;1m"
# define CYAN_BACK		   "\e[46;1m"
# define LIGHTGRAY_BACK	  "\e[47;1m"

/*
** Font type
*/

# define NORM			 "\e[0;1m"
# define BOLD			 "\e[1;1m"
# define UNDERLINED	   "\e[4;1m"
# define FLASHING		 "\e[5;1m"
# define INVERSION		"\e[7;1m"

typedef enum  s_bool
{
							false = 0,
							true = 1
}			 t_bool;

// typedef union			u_cast_d
// {
// 	long double			d;
// 	struct
// 	{
// 		unsigned long	mantisa : 64;
// 		unsigned long	exponent : 15;
// 		unsigned long	sign : 1;
// 	}					d_parts;
// }						t_cast_d;

typedef struct s_printf
{
	char		*format;
	char		data[BUFF];
	char		temp[BUFF];
	size_t	  di;
	size_t	  ti;
	size_t	  fi;
	size_t	  print_size;
	t_bool	  flag;
	t_bool	  f_minus;
	t_bool	  f_plus;
	t_bool	  f_space;
	t_bool	  f_lattice;
	t_bool	  f_zero;
	t_bool	  f_prec;
	t_bool	  f_width;
	t_bool	  f_h;
	t_bool	  f_hh;
	t_bool	  f_l;
	t_bool	  f_ll;
	t_bool	  f_L;
	int		 width;
	int		 prec;
	va_list	 argptr;
}			 t_printf;

typedef struct s_option
{
	unsigned long long whol;
	unsigned long long frac;
	unsigned long long temp;
	int			width;
	int			prec;
	int			buf;
	int			crutch;
	int			short_note;
	int		 flag;
	int		 sign;
	int		 length;
	int		 dot;
	int		 zero;
	int		 exp;
	int		 count;
	int		 lattice;
}			 t_option;


void 				print_e(t_printf *const p, const long double number);
unsigned long long	rounding(t_printf *const p, t_option *const o);
void 				print_f(t_printf *const p, const long double number);
void				print_u(t_printf *const p, const unsigned long long number);
void				print_p(t_printf *const p, const long long n);
void				print_b(t_printf *const p, const unsigned long long number);
void				print_o(t_printf *const p, const unsigned long long number);
void				print_x(t_printf *const p, const unsigned long long number);
void				prec_check(t_printf *const p);
void				flags_and_wid_check(t_printf *const p);
void				modif_check(t_printf *const p);
int					print_ub(t_printf *const p);
void				printf_init(t_printf *const p, const int start);
#endif
