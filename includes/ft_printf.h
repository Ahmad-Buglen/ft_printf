/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:12:57 by dphyliss          #+#    #+#             */
/*   Updated: 2020/06/24 17:11:05 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdarg.h>
# include "../libft/libft.h"

# define BUFF		1024
# define FLAGS		"cp%sdiouxXfFeEbr"
# define LOWERCASE	"0123456789abcdef"
# define UPPERCASE	"0123456789ABCDEF"
# define WHOLE_LEN	1
# define PREC		19

/*
** Text colors
*/

# define BLACK		"\e[30;1m"
# define RED		"\e[31;1m"
# define GREEN		"\e[32;1m"
# define BROWN		"\e[33;1m"
# define BLUE		"\e[34;1m"
# define PURPLE		"\e[35;1m"
# define CYAN		"\e[36;1m"
# define LIGRAY		"\e[37;1m"

/*
** Background colors
*/

# define BLACK_B	"\e[40;1m"
# define RED_B		"\e[41;1m"
# define GREEN_B	"\e[42;1m"
# define BROWN_B	"\e[43;1m"
# define BLUE_B		"\e[44;1m"
# define PURPLE_B	"\e[45;1m"
# define CYAN_B		"\e[46;1m"
# define LIGRAY_B	"\e[47;1m"

/*
** Font type
*/

# define NORM		"\e[0;1m"
# define BOLD		"\e[1;1m"
# define UNDERLINED	"\e[4;1m"
# define FLASHING	"\e[5;1m"
# define INVERSION	"\e[7;1m"

typedef enum			e_bool
{
	false = 0,
	true = 1
}						t_bool;

typedef struct			s_printf
{
	char				data[BUFF];
	char				temp[BUFF];
	int					width;
	int					prec;
	char				*format;
	va_list				argptr;
	size_t				di;
	size_t				ti;
	size_t				fi;
	size_t				print_size;
	t_bool				flag;
	t_bool				f_minus;
	t_bool				f_plus;
	t_bool				f_space;
	t_bool				f_lattice;
	t_bool				f_zero;
	t_bool				f_prec;
	t_bool				f_width;
	t_bool				f_h;
	t_bool				f_hh;
	t_bool				f_l;
	t_bool				f_ll;
	t_bool				f_lbig;
}						t_printf;

typedef struct			s_option
{
	unsigned long long	whol;
	unsigned long long	frac;
	unsigned long long	temp;
	int					width;
	int					prec;
	int					buf;
	int					crutch;
	int					short_note;
	int					flag;
	int					sign;
	int					len;
	int					dot;
	int					zero;
	int					exp;
	int					count;
	int					lattice;
}						t_option;

void					print_e(t_printf *const p, const long double number);
unsigned long long		rounding(t_printf *const p, t_option *const o);
void					print_f(t_printf *const p, const long double number);
void					print_u(t_printf *const p,
									const unsigned long long number);
void					print_p(t_printf *const p, const long long n);
void					print_b(t_printf *const p,
									const unsigned long long number);
void					print_o(t_printf *const p,
									const unsigned long long number);
void					print_x(t_printf *const p,
									const unsigned long long number);
void					prec_check(t_printf *const p);
void					flags_and_wid_check(t_printf *const p);
void					modif_check(t_printf *const p);
int						print_ub(t_printf *const p);
void					printf_init(t_printf *const p, const int start);
void					print_s(t_printf *const p, char const *str);
void					print_r(t_printf *const p, const char c);
void					print_c(t_printf *const p, const char c);
void					print_per(t_printf *const p);
void					ull_to_p_base(t_printf *const p,
							unsigned long long number, const int base);
void					data_release(t_printf *const p);
void					data_record(t_printf *const p);
void					parser(t_printf *const p);
int						distribution(t_printf *const p, const char c);
int						ft_printf(char *const format, ...);
void					print_d(t_printf *const p, long long number);

#endif
