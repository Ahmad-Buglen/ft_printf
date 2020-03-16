
#include "../includes/ft_printf.h"
// #include <stdio.h>
// #include <math.h>

int ft_cinstr(char const *const storage, char const *const desire)
{
  int i;
  int j;

  i = 0;
  while(storage[i])
  {
    j = 0;
    while(desire[j])
    {
      if (storage[i] == desire[j])
        return (1);
      ++j;
    }
    ++i;
  }
  return (0);
}

void		ft_putnstr(char const *str, size_t length)
{
	if (str)
    write(1, str, length);
}

unsigned long long ft_pow(int number, int grade)
{
  unsigned long long rezult;

  if (0 == grade)
    return (1);
  rezult = number;
  while (--grade)
    rezult *= number;
  return (rezult);
}

static int			ft_count_p(unsigned long long number, int base)
{
	int				count;

	count = 1;
	while (number / base)
	{
		number /= base;
		count++;
	}
	return (count);
}

void ull_to_p_base(t_printf *p, unsigned long long number, int base)
{
  int length;
  int buf;
  length = ft_count_p(number, base);
  buf = length--;
  while (length >= 0)
	{
		p->temp[p->ti + length--] = ('X' == p->format[p->fi]) ?
                  UPPERCASE[(number % base)] : LOWERCASE[(number % base)];
		number /= base;
	}
  p->ti += buf;
}

void data_release(t_printf *p)
{
  if (p->di)
  {
    p->print_size += p->di;
    ft_putnstr(p->data, p->di);
    p->di = 0;
  }
}

void  data_record(t_printf *p)
{
  if (BUFF > p->di + p->ti)
  {
    ft_strncpy(p->data + p->di, p->temp, p->ti);
    p->di += p->ti;
  }
  else
  {
    data_release(p);
    if (BUFF > p->ti)
    {
      ft_strncpy(p->data, p->temp, p->ti);
      p->di += p->ti;
    }
    else
    {
      write(1, p->temp, p->ti);
      p->print_size += p->ti;
    }
  }
  p->ti = 0;
}

 void print_s(t_printf *p, char *str)
 {
  int length;
  int space;

  if (NULL == str)
    str = "(null)";
  length = ft_strlen(str);
  length = p->f_prec && p->prec < length ? p->prec : length;
  space = p->f_width ? p->width - length : 0;
  space = space < 0 ? 0 : space;
  while (!p->f_minus && (space-- > 0))
    p->temp[p->ti++] = ' ';
  ft_strncpy(p->temp + p->ti, str, length);
  p->ti += length;
  while (p->f_minus && (space-- > 0))
    p->temp[p->ti++] = ' ';
  data_record(p);
 }

void init_d_options(t_printf *p, long long *number, t_option *o)
{
  p->f_zero = p->f_minus || p->f_prec ? false : p->f_zero;
  o->flag = *number < 0 ? 1 : 0;
  *number = *number < 0 ? -(*number) : *number;
  o->sign = p->f_plus || o->flag ? 1 : 0;
  p->f_space = o->sign ? false : p->f_space;
  o->length = ft_count_p(*number, 10);
  o->length = 0 == *number && p->f_prec && 0 == p->prec ? 0 : o->length;
  o->buf = p->f_zero ? '0' : ' ';
  o->prec = (p->f_prec && (p->prec - o->length > 0)) ?  p->prec - o->length : 0;
  o->width = p->f_width ? p->width - (o->length + o->sign + p->f_space + o->prec) : 0;
  o->width = o->width > 0 ? o->width : 0;
}

void print_d(t_printf *p,  long long number)
{
  t_option o;

  init_d_options(p, &number, &o);
  if (o.sign && (p->f_minus || p->f_zero))
    p->temp[p->ti++] = o.flag ? '-' : '+';
  if (p->f_space)
    p->temp[p->ti++] = ' ';
  while (!p->f_minus && (o.width-- > 0))
    p->temp[p->ti++] = o.buf;
  if (o.sign && !(p->f_minus || p->f_zero))
    p->temp[p->ti++] = o.flag ? '-' : '+';
  while (o.prec-- > 0)
    p->temp[p->ti++] = '0';
  if (o.length > 0)
    ull_to_p_base(p, number, 10);
  while(p->f_minus && (o.width-- > 0))
    p->temp[p->ti++] = ' ';
  data_record(p);
}

void print_u(t_printf *p, unsigned long long number)
{
  int length;
  char buf;
  int prec;
  int width;

  p->f_zero = p->f_minus || p->f_prec ? false : p->f_zero;
  length = ft_count_p(number, 10);
  length = p->f_prec && 0 == p->prec ? 0 : length;
  buf = p->f_zero ? '0' : ' ';
  prec = (p->f_prec && (p->prec - length > 0)) ?  p->prec - length : 0;
  width = p->f_width ? p->width - (length + p->f_space + prec): 0;
  width = width > 0 ? width :0 ;
  while (!(p->f_minus) && width-- > 0)
    p->temp[p->ti++] = buf;
  while (prec-- > 0)
    p->temp[p->ti++] = '0';
  if (length > 0)
    ull_to_p_base(p, number, 10);
  while(p->f_minus && (width-- > 0))
    p->temp[p->ti++] = ' ';
  data_record(p);
}

unsigned long long rounding(t_printf *p, t_option *o)
{
  int extra;
  int digit;
  int zero;

  zero = ft_abs(ft_count_p(o->frac, 10) - PREC);
  extra = ft_abs(((o->prec >= PREC) ? PREC : o->prec + 1) -
            (zero + ft_count_p(o->frac, 10)));
  extra = 'f' == p->format[p->fi] ? extra : extra - 1;
  while (extra-- > 0)
    o->frac /= 10;
  digit = o->frac % 10;
  if (digit + 5 > 9)
  {
    o->frac -= digit;
    if ((ft_count_p(o->frac + 10, 10) > ft_count_p(o->frac, 10)) && (0 == zero))
    {
      o->whol += 1;
      o->frac = 0;
    }
    else
      o->frac += 10;
  }
  return(o->frac);
}

void init_f_options(t_printf *p, long double number, t_option *o)
{
  p->f_zero = p->f_minus ? false : p->f_zero;
  o->flag = number < 0 ? 1 : 0;
  number = number < 0 ? -(number) : number;
  p->f_space = p->f_plus || o->flag ? false : p->f_space;
  o->prec = p->f_prec ? p->prec : 6;
  o->frac = (number - (unsigned long long)number) * ft_pow(10, PREC);
  o->whol = number;
  o->frac = (o->prec >= PREC) ? o->frac : rounding(p, o); //&
  o->frac = (o->prec >= PREC) ? o->frac : o->frac / 10;
  o->zero = ft_abs(ft_count_p(o->frac, 10) - ((o->prec > PREC) ? PREC : o->prec));
  o->dot = ((p->f_prec && o->prec != 0) || !p->f_prec || p->f_lattice) ? 1 : 0;
  o->sign = o->flag || p->f_plus ? 1 : 0;
  o->buf = p->f_zero ? '0' : ' ';
  o->width = p->width - (o->dot + o->sign + ft_count_p(o->whol, 10) + p->f_space + o->prec);
  if (o->sign && p->f_zero)
    p->temp[p->ti++] = o->flag ? '-' : '+';
  if (p->f_space)
    p->temp[p->ti++] = ' ';
  while (!p->f_minus && (o->width-- > 0))
    p->temp[p->ti++] = o->buf;
}

void print_f(t_printf *p, long double number)
 {
  t_option o;

  init_f_options(p, number, &o);
  if (o.sign && (!p->f_zero))
    p->temp[p->ti++] = o.flag ? '-' : '+';
  ull_to_p_base(p, o.whol, 10);
  if (o.dot)
    p->temp[p->ti++] = '.';
  if (o.frac != 0)
  {
    while ((o.zero)-- > 0)
     p->temp[p->ti++] = '0';
    ull_to_p_base(p, o.frac, 10);
    o.prec = ((o.prec > PREC) ? o.prec - PREC : 0);
    while (o.prec-- > 0)
      p->temp[p->ti++] = '0';
  }
  while (o.prec-- > 0)
    p->temp[p->ti++] = '0';
  while(p->f_minus && (o.width-- > 0))
    p->temp[p->ti++] = ' ';
  data_record(p);
}

void init_e_options(t_printf *p, long double number, t_option *o)
{
  p->f_zero = p->f_minus ? false : p->f_zero;
  o->flag = number < 0 ? 1 : 0;
  number = number < 0 ? -number : number;
  p->f_space = p->f_plus || o->flag ? false : p->f_space;
  o->prec = p->f_prec ? p->prec : 6;
  o->temp = number;
  o->frac = (number - o->temp) * ft_pow(10, PREC);
  o->whol = number;
  o->count = 0;
  o->exp = 1;
  o->zero = (o->frac > 0) ? ft_abs(ft_count_p(o->frac, 10) - PREC) : 0;
  o->frac = (o->frac > 0) ? rounding(p, o) : 0;
  o->dot = (p->f_prec && o->prec != 0) || !p->f_prec || p->f_lattice ? 1 : 0;
  o->sign = o->flag || p->f_plus ? 1 : 0;
  o->width = p->f_width ? p->width - (o->dot + o->sign + WHOLE_LEN +
                                                  p->f_space - o->prec) : 0;
  if (o->sign && p->f_zero)
    p->temp[p->ti++] = o->flag ? '-' : '+';
  if (p->f_space)
    p->temp[p->ti++] = ' ';
  while (!p->f_minus && (o->width-- > 0))
    p->temp[p->ti++] = p->f_zero ? '0' : ' ';
  if (o->sign && !p->f_zero)
    p->temp[p->ti++] = o->flag ? '-' : '+';
}

void fract_conv(t_printf *p, long double number, t_option *o)
{
  if (o->whol > 9)
    {
      o->count += (ft_count_p(o->whol, 10) - 1);
      o->temp = o->whol % ft_pow(10, ft_count_p(o->whol, 10) - 1);
      o->whol = o->whol / ft_pow(10, ft_count_p(o->whol, 10) - 1);
      o->crutch = ft_count_p(o->temp, 10);
      while (o->crutch++ < PREC)
      {
        o->temp = (o->temp * 10) +
                  (o->frac / ft_pow(10, ft_count_p(o->frac, 10)));
        o->frac /= 10;
      }
      o->frac = o->temp;
    }
  else if (0 == o->whol)
  {
    o->count += ((number != 0) && !(o->zero > 0)) ? 1 : 0;
    while (o->zero-- > 0)
    {
      o->frac *= 10;
      ++o->count;
    }
    o->whol = o->frac / ft_pow(10, ft_count_p(o->frac, 10) - 1);
    o->frac = o->frac % ft_pow(10, ft_count_p(o->frac, 10) - 1);
    o->exp = (number != 0) ? 0 : 1;
  }
}

void print_e(t_printf *p, long double number)
 {
  t_option o;

  init_e_options(p, number, &o);
  fract_conv(p, number, &o);
  o.length = ft_count_p(o.frac, 10);
  o.frac = o.length > o.prec ? o.frac / ft_pow(10, o.length - o.prec) : o.frac;
  ull_to_p_base(p, o.whol, 10);
  if (o.dot)
    p->temp[p->ti++] = '.';
  if (o.frac != 0)
  {
    ull_to_p_base(p, o.frac, 10);
    o.prec -= o.length;
    while (o.prec-- > 0)
      p->temp[p->ti++] = '0';
  }
  while (o.prec-- > 0)
    p->temp[p->ti++] = '0';
  p->temp[p->ti++] = ('e' == p->format[p->fi]) ? 'e' : 'E';
  p->temp[p->ti++] = (1 == o.exp) ? '+' : '-';
  if (o.count <= 9)
    p->temp[p->ti++] = '0';
  ull_to_p_base(p, o.count, 10);
  while(p->f_minus && (o.width-- > 0))
    p->temp[p->ti++] = ' ';
  data_record(p);
}

void print_x(t_printf *p,  unsigned long long number)
{
  int  buf;
  int width;
  int prec;
  int length;
  int crutch;
  int lattice;

  p->f_zero = p->f_minus || p->f_prec ? false : p->f_zero;
  length = ft_count_p(number, 16);
  buf = p->f_zero ? '0' : ' ';
  lattice = p->f_lattice && number != 0 ? 2 : 0;
  prec = p->f_prec && (p->prec - length > 0) ? p->prec - length : 0;
  crutch = p->f_prec && 0 == number && 0 == p->prec ? 1 : 0;
  width = p->f_width ? p->width - (length + lattice) - prec + crutch : 0;
  while (!p->f_minus && !p->f_zero && (width-- > 0))
    p->temp[p->ti++] = buf;
  if (2 == lattice)
  {
    p->temp[p->ti++] = '0';
    p->temp[p->ti++] = ('x' == p->format[p->fi]) ? 'x' : 'X';
  }
  while (p->f_zero && (width-- > 0))
    p->temp[p->ti++] = buf;
  while (prec-- > 0)
    p->temp[p->ti++] = '0';
 if (!crutch)
    ull_to_p_base(p, number, 16);
  while (p->f_minus && (width-- > 0))
    p->temp[p->ti++] = ' ';
  data_record(p);
}

void print_o(t_printf *p, unsigned long long number)
{
  t_option o;

  p->f_zero = p->f_minus || p->f_prec ? false : p->f_zero;
  o.length =  ft_count_p(number, 8) ;
  o.buf = p->f_zero ? '0' : ' ';
  o.lattice = p->f_lattice && number != 0 ? 1 : 0;
  o.prec = p->f_prec ? p->prec - (o.length + o.lattice) : 0;
  o.prec = o.prec > 0 ? o.prec : 0;
  o.zero = p->f_prec && 0 == p->prec ? 1 : 0;
  o.crutch = p->f_lattice && o.zero ? 1 : 0;
  o.short_note = 0 == number && o.zero ? 1 : 0;
  o.width = p->f_width ? p->width - o.crutch + o.short_note -
                            (o.length + o.lattice) - o.prec: 0;
  while (!p->f_minus && (o.width-- > 0))
    p->temp[p->ti++] = o.buf;
  while (o.prec-- > 0)
    p->temp[p->ti++] = '0';
  if (o.lattice)
    p->temp[p->ti++] = '0';
  if (!o.short_note || o.crutch)
    ull_to_p_base(p, number, 8);
  while (p->f_minus && (o.width-- > 0))
    p->temp[p->ti++] = ' ';
  data_record(p);
}

void print_b(t_printf *p, unsigned long long number)
{
  int  buf;
  int width;
  int prec;
  int length;
  int crutch;

  p->f_zero = p->f_minus || p->f_prec ? false : p->f_zero;
  length = ft_count_p(number, 2);
  buf = p->f_zero ? '0' : ' ';
  prec = p->f_prec && (p->prec - length > 0) ? p->prec - length : 0;
  crutch = p->f_prec && 0 == number && 0 == p->prec ? 1 : 0;
  width = p->f_width ? p->width - length - prec + crutch : 0;
  while (!p->f_minus && !p->f_zero && (width-- > 0))
    p->temp[p->ti++] = buf;
  while (p->f_zero &&  (width-- > 0))
    p->temp[p->ti++] = buf;
  while (prec-- > 0)
    p->temp[p->ti++] = '0';
 if (!crutch)
    ull_to_p_base(p, number, 2);
  while (p->f_minus && (width-- > 0))
    p->temp[p->ti++] = ' ';
  data_record(p);
}

void print_p(t_printf *p, long long n)
{
  // long long n;
  int width;
  int space;

  // n = va_arg(p->argptr, long long);
  width = (0 == n) ? 3 : 11;
  space = p->f_width ? p->width - width : 0;
  while (!p->f_minus && (space-- > 0))
    p->temp[p->ti++] = ' ';
  p->temp[p->ti++] = '0';
  p->temp[p->ti++] = 'x';
  ull_to_p_base(p, n, 16);
  while (p->f_minus && (space-- > 0))
    p->temp[p->ti++] = ' ';
  data_record(p);
}

void print_per(t_printf *p)
{
  char  buf;
  int   width;

  buf = p->f_zero && !p->f_minus ? '0' : ' ';
  width = p->f_width ? p->width - 1 : 0;
  width = (width < 0) ? 0 : width;
  while (!p->f_minus && (width-- > 0))
    p->temp[p->ti++] = buf;
  p->temp[p->ti++] = '%';
  while (p->f_minus && (width-- > 0))
    p->temp[p->ti++] = buf;
  data_record(p);
}

void printf_init(t_printf *p, int start)
{
  if (start)
  {
    p->fi = 0;
    p->di = 0;
    p->print_size = 0;
    ft_bzero(p->data, BUFF);
  }
  p->f_minus = false;
  p->f_plus = false;
  p->f_space = false;
  p->f_lattice = false;
  p->f_zero = false;
  p->flag = false;
  p->f_width = false;
  p->f_prec = false;
  p->ti = 0;
  p->width = 0;
  p->prec = 0;
  ft_bzero(p->temp, BUFF);
  p->f_h = false;
  p->f_hh = false;
  p->f_l = false;
  p->f_ll = false;
  p->f_L = false;
}

void print_c(t_printf *p, char  c)
{
  // char  c;
  char  buf;
  int   width;

  // c = (char)va_arg(p->argptr, int);
  buf = p->f_zero && !p->f_minus ? '0' : ' ';
  width = p->f_width ? p->width - 1 : 0;
  width = width < 0 ? 0 : width;
  while (!p->f_minus && (width-- > 0))
    p->temp[p->ti++] = buf;
  p->temp[p->ti++] = c;
  while (p->f_minus && (width-- > 0))
    p->temp[p->ti++] = buf;
  data_record(p);
}

int print_ub(t_printf *p)
{
  if (('\0' == p->format[p->fi + 1]) ||
      !(ft_cinstr(&(p->format[p->fi + 1]), FLAGS)))
  {
    p->temp[p->ti++] = 'U';
    p->temp[p->ti++] = 'B';
    data_record(p);
    return (1);
  }
  return (0);
}


void modif_check(t_printf *p)
{
  if (('h' == p->format[p->fi]) && ('h' == p->format[p->fi + 1]))
  {
    p->f_hh = true;
    p->fi += 2;
  }
  else if ('h' == p->format[p->fi])
  {
    p->f_h = true;
    ++p->fi;
  }
  else if (('l' == p->format[p->fi]) && ('l' == p->format[p->fi + 1]))
  {
    p->f_ll = true;
    p->fi += 2;
  }
  else if ('l' == p->format[p->fi])
  {
    p->f_l = true;
    ++p->fi;
  }
  else if ('L' == p->format[p->fi])
  {
    p->f_L = true;
    ++p->fi;
  }
}

void flags_and_wid_check(t_printf *p)
{
  while (('-' == p->format[p->fi]) || ('+' == p->format[p->fi]) ||
    (' ' == p->format[p->fi]) || ('#' == p->format[p->fi]) || ('0' == p->format[p->fi]))
  {
    p->f_minus = ('-' == p->format[p->fi]) ? true : p->f_minus;
    p->f_plus = ('+' == p->format[p->fi]) ? true : p->f_plus;
    p->f_space = (' ' == p->format[p->fi]) ? true : p->f_space;
    p->f_lattice = ('#' == p->format[p->fi]) ? true : p->f_lattice;
    p->f_zero = ('0' == p->format[p->fi]) ? true : p->f_zero;
    ++p->fi;
  }
  if (('0' <= *(p->format + p->fi)) && (*(p->format + p->fi) <= '9'))
  {
    p->width = ft_atoi(p->format + p->fi); // как обработать?
    p->f_width = true;
    while (('0' <= p->format[p->fi]) && (p->format[p->fi] <= '9'))
      ++p->fi;
  }
  else if ('*' == *(p->format + p->fi))
  {
    p->f_width = true;
    p->width = va_arg(p->argptr, int);
    ++p->fi;
  }
}

void prec_check(t_printf *p)
{
  if ('.' == p->format[p->fi])
  {
    ++p->fi;
    p->f_prec = true;
    if ('*' == *(p->format + p->fi))
    {
      p->prec = va_arg(p->argptr, int);
      ++p->fi;
    }
    else
    {
      p->prec = ft_atoi(p->format + p->fi); // как обработать?
      while (('0' <= p->format[p->fi]) && (p->format[p->fi] <= '9'))
        ++p->fi;
    }
  }
}

int  distribution(t_printf *p, char c)
{
  if ('c' == c)
    print_c(p, va_arg(p->argptr, int));
  else if ('p' == c)
    print_p(p, va_arg(p->argptr, long long));
  else if ('%' == c)
    print_per(p);
  else if ('s' == c)
    print_s(p, va_arg(p->argptr, char *));
  else if (('d' == c) || ('i' == c))
  {
    if (p->f_l)
      print_d(p, va_arg(p->argptr, long ));
    else if (p->f_ll)
      print_d(p, va_arg(p->argptr, long long));
    else
      print_d(p, va_arg(p->argptr, int));
  }
  else if ('u' == c)
    print_u(p, (unsigned long)va_arg(p->argptr, unsigned long long));
  else if ('o' == c)
    print_o(p, (unsigned long)va_arg(p->argptr, unsigned long long));
  else if (('x' == c) || ('X' == c))
    print_x(p, (unsigned long)va_arg(p->argptr, unsigned long long));
  else if (('f' == c) || ('F' == c))
  {
    if (p->f_L)
      print_f(p, va_arg(p->argptr, long double));
    else
      print_f(p, va_arg(p->argptr, double));
  }
  else if (('e' == c) || ('E' == c))
  {
    if (p->f_L)
      print_e(p, va_arg(p->argptr, long double));
    else
      print_e(p, va_arg(p->argptr, double));
  }
  else if ('b' == c)
    print_b(p, (unsigned long)va_arg(p->argptr, unsigned long long));
  return 1;
}

void parser(t_printf *p)
{
  size_t i;

  while (p->format[p->fi])
  {
    if ('%' == p->format[p->fi])
    {
      if (1 == print_ub(p))
        return ;
      ++p->fi;
      flags_and_wid_check(p);
      prec_check(p);
      modif_check(p);
      p->flag = true;
      distribution(p, p->format[p->fi]);
      printf_init(p, 0);
    }
    else
    {
      p->temp[0] = p->format[p->fi];
      p->ti = 1;
      data_record(p);
    }
    ++p->fi;
  }
}

int ft_printf(char * format, ...)
{
  t_printf p;
  /* инициализация argptr */
  va_start (p.argptr, format);

  printf_init(&p, 1);
  ft_bzero(p.data, BUFF);
  p.format = format;
  parser(&p);
  data_release(&p);
  /* завершение */
  va_end(p.argptr);
  return (p.print_size);
}
