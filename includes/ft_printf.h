#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdarg.h>
# include "../libft/libft.h"

# define BUFF 65536

typedef enum  s_bool
{
              false = 0, 
              true = 1
}             t_bool;


typedef struct s_printf
{
  char        data[BUFF];
  char        temp[BUFF];
  size_t      di;
  size_t      ti;
  size_t      fi;
  size_t      print_size;
  t_bool      format;
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
  int         width;
  int         prec;
  va_list     argptr;
}             t_printf;


#endif