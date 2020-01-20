
#include "../includes/ft_printf.h"

void printf_init(t_printf *p)
{
  p->f_minus = false;
  p->f_plus = false;
  p->f_space = false;
  p->f_lattice = false;
  p->f_zero = false;

}

double ft_printf(char *str, ...)
{
  int sum = 0, t;
  va_list argptr;

  /* инициализация argptr */
  va_start (argptr, num);

  /* сумма последовательности */
  for(; num; num--) {
    t = va_arg(argptr, int);
    sum += t;
  }
  /* завершение */
  va_end(argptr);
  return sum;
}

int main(void)
{
  t_printf p;
  int d;

  d = ft_printf(7, 1, 2, 3, 4, 5, 6, 7);
  printf("%d\n",d);
  return 0;
}



