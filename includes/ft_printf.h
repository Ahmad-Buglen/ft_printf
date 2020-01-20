#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdarg.h>

# define BUFF 1024

typedef enum  s_bool
{
              false = 0, 
              true = 1
}             t_bool;

typedef struct s_printf
{
  char        data[BUFF];
  int         i;
  int         print_size;
  t_bool      f_minus;
  t_bool      f_plus;
  t_bool      f_space;
  t_bool      f_lattice;
  t_bool      f_zero;
  t_bool      format;
  t_bool      f_prec;
  t_bool      f_width;
  size_t      width;
  size_t      precision;
  va_list     argptr
}             t_printf;


#endif