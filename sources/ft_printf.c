
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
  char  c;
  char   buf;

  c = (char)va_arg(p->argptr, int);
  buf = (p->f_zero) ? '0' : ' ';
  p->data[p->i++] = (p->f_minus) ? c : buf;
  --p->width;
  while (--p->width)
  {
    p->data[p->i] = buf;
    ++p->i;
  }
  p->data[p->i] = (p->f_minus) ? buf : c;
  ++p->i;
}

void data_release(t_printf *p)
{
  if (p->i)
  {
    p->print_size += p->i;
    write(1, p->data, p->i);
    p->i = 0;
  }
}

int  distribution(t_printf *p, char c)
{
  // c = \0 ?
  if ('c' == c)
    print_c(p);
  if ('p' == c)
    print_c(p);
  return 1;
}
void  data_record(t_printf *p, char *str)
{
  size_t length;

  length = ft_strlen(str);
  if (BUFF <= p->i + length) // ?
  {
    data_release(p);
    if (BUFF < length)
    {
      write(1, str, length);
      p->print_size += length;
    }
    else
    {
      ft_strcpy(p->data, str);
      p->i += length;
    }
  }
  else
  {
    ft_strcpy(p->data[p->i], str);
    p->i += length;
  }
}

void flags_check(t_printf *p, char *str)
{
  while (('-' == str[p->j]) || ('+' == str[p->j]) ||
    (' ' == str[p->j]) || ('#' == str[p->j]) || ('0' == str[p->j]))
  {
    p->f_minus = ('-' == str[p->j]) ? true : p->f_minus; 
    p->f_plus = ('+' == str[p->j]) ? true : p->f_plus;
    p->f_space = (' ' == str[p->j]) ? true : p->f_space;
    p->f_lattice = ('#' == str[p->j]) ? true : p->f_lattice;
    p->f_zero = ('0' == str[p->j]) ? true : p->f_zero;
    ++p->j;
  }
  // ft_putstr("flags_check\n");
  // ft_putnbr(p->j);
  // write(1, "\n", 1);
}

void wid_and_prec_check(t_printf *p, char *str)
{
  if (('0' <= *(str + p->j)) && (*(str + p->j) <= '9'))
  {
    p->width = ft_atoi(str + p->j); // как обработать? 
    p->f_width = true;
    while (('0' <= str[p->j]) && (str[p->j] <= '9'))
      ++p->j;
  }
  if ('.' == str[p->j])
  {
    ++p->j;
    p->precision = ft_atoi(str + p->j); // как обработать?
    p->f_prec = true;
    while (('0' <= str[p->j]) && (str[p->j] <= '9'))
      ++p->j;
  }
}

void parser(char *str, t_printf *p)
{
  size_t i;

  p->j = 0;
  p->i = 0;
  while (str[p->j])
  {
    if ('%' == str[p->j])
    {
      ++p->j;
      flags_check(p, str);
      wid_and_prec_check(p, str);
      p->format = true;
      distribution(p, (str[p->j]));
      printf_init(p);
    }
    else
      data_record(p, str[p->j]);
    ++p->j;
  }
}


int ft_printf(char * format, ...)
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
  int c = 0;
  //ft_printf("%c %s %% ", 't', "strint");
  printf("%10.10000d\n", 10);
   printf("%10.10f\n", 10.10);
    printf("%10.10ld\n", 99999999999);
     printf("%10.10s\n", "asdfasfasfasfasfasdfasdf");
 // ft_printf("%1000000c\n", &c);
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

  //printf("---");
  //ft_printf("---");

  // ft_printf("1 %10c\n", c);
  // ft_printf("2 %09c\n", c);
  // ft_printf("3 %-7c\n", c);
  // ft_printf("4 %+3c\n", c);
  // ft_printf("5 % 12c\n", c);
  // ft_printf("6 %#13c\n", c);
  // ft_printf("7 %033c\n", c);
  // ft_printf("8 %+-6c\n", c);
  // ft_printf("9 % #9c\n", c);
  // ft_printf("10 %0-10c\n", c);
  // ft_printf("11 %+021c\n", c);
  // ft_printf("12 %#-23c\n", c);

  return 0;
}