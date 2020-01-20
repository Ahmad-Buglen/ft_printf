
#include "../includes/ft_printf.h"

void printf_init(t_printf *p)
{
  p->f_minus = false;
  p->f_plus = false;
  p->f_space = false;
  p->f_lattice = false;
  p->f_zero = false;
  p->format = false;
  p->f_width = false;
  p->f_prec = false;
}

void print_c(t_printf *p)
{
  char c;

  c = va_arg(p->argptr, char);
  // data release ? 
  if (p->f_width)
  {
    if (p->f_minus)
      p->data[p->i] = c;
      p->i += 1;
    while (p->f_width > 1)
    {
      p->data[p->i] = (p->f_zero) ? '0' : ' ';
      p->i += 1;
      p->f_width -= 1;
    }
    p->data[p->i] = (p->f_minus) ? p->data[p->i - 1] : c;
  }

}

int data_release(t_printf *p)
{
  p->print_size += p->i;
  write(1, p->data, p->i);
  p->i = 0;
}

int  data_record(t_printf *p, char c)
{
  if (p->format)
  {
    if ('c' == c)
      print_c(p);
  }
  else 
  {
    if (BUFF <= p->i + 1) // ?
      data_release(p);
    p->data[p->i] = c;
    p->i += 1;
  }
  return 1;
}

int flags_check(t_printf *p, char *str, int *i)
{
  while (('-' == str[*i]) || ('+' == str[*i]) || (' ' == str[*i]) ||
                ('#' == str[*i]) || ('0' == str[*i]))
  {
    if ('-' == str[*i]) 
      p->f_minus = true;
    if ('+' == str[*i]) 
      p->f_plus = true;
    if (' ' == str[*i]) 
      p->f_space = true;
    if ('#' == str[*i]) 
      p->f_lattice = true;
    if ('0' == str[*i]) 
      p->f_zero = true;
    ++(*i);
  }
  ft_putstr("flags_check\n");
  ft_putnbr(*i);
  write(1, "\n", 1);
}

int wid_and_prec_check(t_printf *p, char *str, int *i)
{
  if (('0' >= str[*i]) && ('9' <= str[*i]))
  {
    p->width = ft_atoi(str[*i]); // как обработать? 
    p->f_width = true;
    while (('0' >= str[*i]) && ('9' <= str[*i]))
      ++(*i);
  }
  if ('.' == str[*i])
  {
    ++(*i);
    p->precision = ft_atoi(str[*i]); // как обработать?
    p->f_prec = true;
    while (('0' >= str[*i]) && ('9' <= str[*i]))
      ++(*i);
  }
  ft_putstr("wid_and_prec_check\n");
  ft_putnbr(*i);
  write(1, "\n", 1);
}

size_t parser(char *str, t_printf *p)
{
  size_t i;

  i = 0;
  p->i = 0;
  while (str[i])
  {
    if ('%' == str[i])
    {
      ft_putstr("parser 1 \n");
      ft_putnbr(i);
      write(1, "\n", 1);
      flags_check(p, str, &i);
      wid_and_prec_check(p, str, &i);
      ft_putstr("parser 2 \n");
      ft_putnbr(i);
      write(1, "\n", 1);
      p->format = true;
    }
    data_record(p, (char )(str[i]));
    printf_init(&p);
    ++i;
  }
}


int ft_printf(const char * format, ...)
{
  t_printf p;


  /* инициализация argptr */
  va_start (p.argptr, format);

  p.print_size = 0;
  printf_init(&p);
  parser(format, &p);
  //va_arg(argptr, int);
  data_release(&p);
  /* завершение */
  va_end(p.argptr);
  return (p.print_size);
}

int main(int ac, char **av)
{
  char c = 'c';
  //ft_printf("%c %s %% ", 't', "strint");
  // printf("1 %10c\n", c);
  // printf("2 %09c\n", c);
  // printf("3 %-7c\n", c);
  // printf("4 %+3c\n", c);
  // printf("5 % 12c\n", c);
  // printf("6 %#13c\n", c);
  // printf("7 %033c\n", c);
  // printf("8 %+-6c\n", c);
  // printf("9 % #9c\n", c);
  // printf("10 %0-10c\n", c);
  // printf("11 %+021c\n", c);
  // printf("12 %#-23c\n", c);

  // printf("---");
  ft_printf("---");

  ft_printf("1 %10c\n", c);
  ft_printf("2 %09c\n", c);
  ft_printf("3 %-7c\n", c);
  ft_printf("4 %+3c\n", c);
  ft_printf("5 % 12c\n", c);
  ft_printf("6 %#13c\n", c);
  ft_printf("7 %033c\n", c);
  ft_printf("8 %+-6c\n", c);
  ft_printf("9 % #9c\n", c);
  ft_printf("10 %0-10c\n", c);
  ft_printf("11 %+021c\n", c);
  ft_printf("12 %#-23c\n", c);

  return 0;
}