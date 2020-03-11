#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdarg.h>
# include "../libft/libft.h"

# define BUFF 65536
# define FLAGS "cp%sdiouxXfFeEb"
# define  a  "0123456789abcdef"
# define  A  "0123456789ABCDEF"
# define PREC 19

/*
** Text colors
*/

# define BLACK          "\e[30;1m"
# define RED            "\e[31;1m"
# define GREEN          "\e[32;1m"
# define BROWN          "\e[33;1m"
# define BLUE           "\e[34;1m"
# define PURPLE         "\e[35;1m"
# define CYAN           "\e[36;1m"
# define LIGHTGRAY      "\e[37;1m"

/*
** Background colors
*/

# define BLACK_BACK          "\e[40;1m"
# define RED_BACK            "\e[41;1m"
# define GREEN_BACK          "\e[42;1m"
# define BROWN_BACK          "\e[43;1m"
# define BLUE_BACK           "\e[44;1m"
# define PURPLE_BACK         "\e[45;1m"
# define CYAN_BACK           "\e[46;1m"
# define LIGHTGRAY_BACK      "\e[47;1m"

/*
** Font type
*/

# define NORM             "\e[0;1m"
# define BOLD             "\e[1;1m"
# define UNDERLINED       "\e[4;1m"
# define FLASHING         "\e[5;1m"
# define INVERSION        "\e[7;1m"

typedef enum  s_bool
{
              false = 0, 
              true = 1
}             t_bool;

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
  char        *format;
  char        data[BUFF];
  char        temp[BUFF];
  size_t      di;
  size_t      ti;
  size_t      fi;
  size_t      print_size;
  t_bool      flag;
  t_bool      f_minus;
  t_bool      f_plus;
  t_bool      f_space;
  t_bool      f_lattice;
  t_bool      f_zero;
  t_bool      f_prec;
  t_bool      f_width;
  t_bool      f_h;
  t_bool      f_hh;
  t_bool      f_l;
  t_bool      f_ll;
  t_bool      f_L;
  int         width;
  int         prec;
  va_list     argptr;
}             t_printf;

typedef struct s_option
{
  int         width;
  int         prec;
  int         buf;
  int         crutch;
  int         short_note;
  int         flag;
  int         sign;
}             t_option;


#endif