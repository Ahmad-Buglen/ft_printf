
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

 void print_s(t_printf *p)
 {
  char *str;
  int length;
  int space;

  str = va_arg(p->argptr, char *);
  if (NULL == str)
    str = "(null)";
  length = ft_strlen(str);
  length = ((p->f_prec) && (p->prec < length)) ? p->prec : length;
  space = (p->f_width) ? p->width - length : 0;
  space = (space < 0) ? 0 : space;
  while ((!p->f_minus) && (space-- > 0))
    p->temp[p->ti++] = ' ';
  ft_strncpy(p->temp + p->ti, str, length);
  p->ti += length;
  while ((p->f_minus) && (space-- > 0))
    p->temp[p->ti++] = ' ';
  data_record(p);
 }

void print_d(t_printf *p,  long long number)
{
  int length;
  char buf;
  int  flag;
  int prec;
  int width;
  int sign;

  p->f_zero = ((p->f_minus) || (p->f_prec)) ? false : p->f_zero;
  flag = (number < 0) ? 1 : 0;
  number = (number < 0) ? -number : number;
  sign = (p->f_plus || flag) ? 1 : 0;
  p->f_space = sign ? false : p->f_space;
  length = ft_count_p(number, 10);
  length = ((0 == number) && p->f_prec && (0 == p->prec)) ? 0 : length;
  buf = (p->f_zero) ? '0' : ' ';
  prec = ((p->f_prec) && ((p->prec - length) > 0)) ?  p->prec - length : 0;
  width = (p->f_width) ? p->width - (length + sign + ((p->f_space) ? 1 : 0)): 0;
  width = ((prec > 0) && ((width - prec) > 0)) ? width - prec : width;
  if (sign && (p->f_minus || p->f_zero))
    p->temp[p->ti++] = flag ? '-' : '+';
  if (p->f_space)
    p->temp[p->ti++] = ' ';
  while (!(p->f_minus) && width-- > 0)
    p->temp[p->ti++] = buf;
  if (sign && !(p->f_minus || p->f_zero))
    p->temp[p->ti++] = flag ? '-' : '+';
  while (prec-- > 0)
    p->temp[p->ti++] = '0';
  if (length > 0)
    ull_to_p_base(p, number, 10);
  while(p->f_minus && (width-- > 0))
    p->temp[p->ti++] = ' ';
  data_record(p);
}

unsigned long long rounding(t_printf *p, unsigned long long frac, int prec,
                              unsigned long long *whol)
{
  int extra;
  int digit;
  int zero;

  prec = (prec >= PREC) ? PREC : prec + 1;
  zero = ft_abs(ft_count_p(frac, 10) - PREC);
  extra = ft_abs(prec - (zero + ft_count_p(frac, 10)));
  extra = ('f' == p->format[p->fi]) ? extra : extra - 1; 
  while (extra-- > 0)
    frac /= 10;
  digit = frac % 10;
  if (digit + 5 > 9)
  {
    frac -= digit;
    if ((ft_count_p(frac + 10, 10) > ft_count_p(frac, 10)) && (0 == zero))
    {
      *whol += 1;
      frac = 0;
    }
    else
      frac += 10;
  }
  return(frac);
}

void print_f(t_printf *p, long double number)
 {
  int whole_l;
  int fract_l;
  unsigned long long whol;
  unsigned long long frac;
  char buf;
  char  flag;
  char  sign;
  int zero;
  int prec;
  int width;
  int i;
  int dot;

  p->f_zero = (p->f_minus) ? false : p->f_zero;
  flag = number < 0 ? 1 : 0;
  number = (number < 0) ? -number : number;
  p->f_space = (p->f_plus || flag) ? false : p->f_space;
    prec = (p->f_prec) ?  p->prec : 6;
  prec = (prec > 0) ? prec : 0;
  
  unsigned long long temp = number;
  // i = PREC;
  // while ()
    frac = (number - temp) * ft_pow(10, PREC);
    // zero = ft_abs(ft_count_p(frac, 10) - PREC);
    whol = number;

  frac = (prec >= PREC) ? frac : rounding(p, frac, prec, &whol);
  frac = (prec >= PREC) ? frac : frac / 10;
  zero = ft_abs(ft_count_p(frac, 10) - ((prec > PREC) ? PREC : prec));
  // zero = (prec >= PREC) ? zero - 1: zero; 
  whole_l = ft_count_p(whol, 10);
  dot = (((p->f_prec) && (prec != 0)) || !(p->f_prec) || p->f_lattice) ? 1 : 0;
  sign = (flag || p->f_plus) ? 1 : 0;
  buf = (p->f_zero) ? '0' : ' ';

  width = (p->f_width) ? p->width - (dot + sign + whole_l + 
                        ((p->f_space) ? 1 : 0)) : 0 ;
              
                // ((p->f_space) ? 1 : 0): 0;
  width = (prec > 0) ? width - prec : width;
  width = !(p->f_minus) ? width : 0;
  width = (width > 0) ? width : 0;
  if (sign && (p->f_zero))
    p->temp[p->ti++] = flag ? '-' : '+';
  if (p->f_space)
    p->temp[p->ti++] = ' ';
  i = width;
  while (i-- > 0)
  p->temp[p->ti++] = buf;

  if (sign && (!p->f_zero))
    p->temp[p->ti++] = flag ? '-' : '+';

  ull_to_p_base(p, whol, 10);
  if (dot)
    p->temp[p->ti++] = '.';
  if (frac != 0)
  {
    // zero = ft_count_p(frac, 10) - 19;
    //zero = ft_abs(ft_count_p(frac, 10) - prec);
     int z; // = prec - (ft_count_p(frac, 10) - 1);
    z = zero;
    while (z-- > 0)
     p->temp[p->ti++] = '0';

    ull_to_p_base(p, frac, 10);
    i = ((prec > PREC) ? prec - PREC : 0);
    // i = (prec >= PREC) ? i + 1 : i;

    while (i--)
      p->temp[p->ti++] = '0';
  }
  else
  {
    i = prec;
    while (i--)
    {
      ft_strncpy(p->temp + p->ti, "0", 1);
      p->ti += 1;
    }
  }
  // else
  //   p->temp[p->ti++] = ' ';
  if ((p->f_width) && (p->width > whole_l) && (p->f_minus)) //ti
    while(p->width > p->ti)
     p->temp[p->ti++] = ' ';
  data_record(p);
}


void print_e(t_printf *p)
 {
  int whole_l;
  int fract_l;
  unsigned long long whol;
  unsigned long long frac;
  long double n;
  char buf;
  char  flag;
  char  sign;
  int exp;
  int zero;
  int prec;
  int width;
  int i;
  int dot;
  int count;
  int length;

  p->f_zero = (p->f_minus) ? false : p->f_zero;
  n = (long double)va_arg(p->argptr,   double);
  flag = n < 0 ? 1 : 0;
  n = (n < 0) ? -n : n;
  p->f_space = (p->f_plus || flag) ? false : p->f_space;
  prec = (p->f_prec) ?  p->prec : 6;
  prec = (prec > 0) ? prec : 0;

  unsigned long long temp = n;
  frac = (n - temp) * ft_pow(10, PREC);
  whol = n;

  count = 0;
  exp = 1;
  zero = (frac > 0) ? ft_abs(ft_count_p(frac, 10) - PREC) : 0;
  frac = (frac > 0) ? rounding(p, frac, prec, &whol) : 0;
  if (whol > 9)
    {
      count += (ft_count_p(whol, 10) - 1);
      temp = whol % ft_pow(10, ft_count_p(whol, 10) - 1);
      whol = whol / ft_pow(10, ft_count_p(whol, 10) - 1);
      i = ft_count_p(temp, 10);
      while (i < PREC)
      {
        temp = (temp * 10) + (frac / ft_pow(ft_count_p(frac, 10), 10));
        frac /= 10;
        ++i;
      }
      frac = temp;

    }
  else if (0 == whol)
  { 
    count += ((n != 0) && !(zero > 0)) ? 1 : 0;
    while (zero > 0)
    {
      frac *= 10;
      ++count;
      --zero;
    }
    whol = frac / ft_pow(10, ft_count_p(frac, 10) - 1);
    frac = frac % ft_pow(10, ft_count_p(frac, 10) - 1);

    exp = (n != 0) ? 0 : 1;
  }
  //zero = ft_abs(ft_count_p(frac, 10) - ((prec > 19) ? 19 : prec + 1));
  
  fract_l = ft_count_p(frac, 10);
  whole_l = ft_count_p(whol, 10);

  dot = (((p->f_prec) && (prec != 0)) || !(p->f_prec) || p->f_lattice) ? 1 : 0;
  sign = (flag || p->f_plus) ? 1 : 0;
  buf = (p->f_zero) ? '0' : ' ';

  width = (p->f_width) ? p->width - (dot + sign + whole_l + 
                    ((p->f_space) ? 1 : 0)) : 0 ;
  width = (prec > 0) ? width - prec : width;
  width = !(p->f_minus) ? width : 0;
  width = (width > 0) ? width : 0;
  if (sign && (p->f_zero))
    p->temp[p->ti++] = flag ? '-' : '+';
  if (p->f_space)
    p->temp[p->ti++] = ' ';
  i = width;
  while (i-- > 0)
  p->temp[p->ti++] = buf;

  if (sign && (!p->f_zero))
    p->temp[p->ti++] = flag ? '-' : '+';

  ull_to_p_base(p, whol, 10);
  if (dot)
    p->temp[p->ti++] = '.';

  if (frac != 0)
  {
    length = (prec > PREC) ? PREC : prec;
    length = (prec > fract_l) ? fract_l : prec;

    ull_to_p_base(p, frac, 10);
    i = prec - length;
    while (i-- > 0)
      p->temp[p->ti++] = '0';
  }
  else
  {
    i = prec;
    while (i--)
      p->temp[p->ti++] = '0';
  }
  p->temp[p->ti++] = ('e' == p->format[p->fi]) ? 'e' : 'E';
  p->temp[p->ti++] =  (1 == exp) ? '+' : '-';
  if (count > 9)
  {
    ull_to_p_base(p, count, 10);
  }
  else 
  {
    p->temp[p->ti++] = '0';
    ull_to_p_base(p, count, 10);
  }
  if ((p->f_width) && (p->width > whole_l) && (p->f_minus)) //ti
    while(p->width > p->ti)
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

  p->f_zero = ((p->f_minus) || (p->f_prec)) ? false : p->f_zero;
  length = ft_count_p(number, 16);
  buf = (p->f_zero) ? '0' : ' ';
  lattice = (p->f_lattice && number != 0) ? 2 : 0;
  prec = ((p->f_prec) && ((p->prec - length) > 0)) ? p->prec - length : 0;
  crutch = (p->f_prec && (0 == number) && (0 == p->prec) ) ? 1 : 0;
  width = (p->f_width) ? p->width - (length + lattice) - prec + crutch : 0;
  while (!p->f_minus && !p->f_zero && (width-- > 0))
    p->temp[p->ti++] = buf;
  if (2 == lattice)
  {
    p->temp[p->ti++] = '0';
    p->temp[p->ti++] = ('x' == p->format[p->fi]) ? 'x' : 'X';
  }
  while (p->f_zero &&  (width-- > 0))
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
  int  buf;
  int width;
  int prec;
  int length;
  int lattice;
  int crutch;
  int crutch1;
  int prec_nul;

  p->f_zero = ((p->f_minus) || (p->f_prec)) ? false : p->f_zero;
  length =  ft_count_p(number, 8) ;
  buf = (p->f_zero) ? '0' : ' ';
  lattice = (p->f_lattice && (number != 0)) ? 1 : 0;
  prec = (p->f_prec) ? p->prec - (length + lattice) : 0;
  prec = (prec > 0) ? prec : 0;
  prec_nul = (p->f_prec && (0 == p->prec)) ? 1 : 0;
  crutch = (p->f_lattice && prec_nul) ? 1 : 0;
  crutch1 = ((0 == number) && prec_nul ) ? 1 : 0;
  width = (p->f_width) ? p->width - crutch + crutch1 - (length + lattice) - prec: 0;
  while (!p->f_minus && (width-- > 0))
    p->temp[p->ti++] = buf;
  while (prec-- > 0)
    p->temp[p->ti++] = '0';
  if (lattice )
    p->temp[p->ti++] = '0';
  if (!(crutch1) || crutch)
    ull_to_p_base(p, number, 8);
  while ( p->f_minus && (width-- > 0))
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

  p->f_zero = ((p->f_minus) || (p->f_prec)) ? false : p->f_zero;
  length = ft_count_p(number, 2);
  buf = (p->f_zero) ? '0' : ' ';
  prec = ((p->f_prec) && ((p->prec - length) > 0)) ? p->prec - length : 0;
  crutch = (p->f_prec && (0 == number) && (0 == p->prec) ) ? 1 : 0;
  width = (p->f_width) ? p->width - length - prec + crutch : 0;
  while (!p->f_minus && !p->f_zero && (width-- > 0))
    p->temp[p->ti++] = buf;
  while ((p->f_zero) &&  (width-- > 0))
    p->temp[p->ti++] = buf;
  while (prec-- > 0)
    p->temp[p->ti++] = '0';
 if (!crutch)
    ull_to_p_base(p, number, 2);
  while (p->f_minus && (width-- > 0))
    p->temp[p->ti++] = ' ';
  data_record(p);
}

void print_p(t_printf *p)
{
  long long n;
  int width;
  int space;

  n = va_arg(p->argptr, long long);
  width = (0 == n) ? 3 : 11;
  space = (p->f_width) ? ((p->width) - width) : 0;
  while((!p->f_minus) && (space-- > 0))
    p->temp[p->ti++] = ' ';
  p->temp[p->ti++] = '0';
  p->temp[p->ti++] = 'x';
  ull_to_p_base(p, n, 16);
  while(p->f_minus && (space-- > 0))
    p->temp[p->ti++] = ' ';
  data_record(p);
}

void print_per(t_printf *p)
{
  char  buf;
  int   width;

  buf = (p->f_zero && !p->f_minus) ? '0' : ' ';
  width = (p->f_width) ? p->width - 1 : 0;
  width = (width < 0) ? 0 : width;
  while ((!p->f_minus) && (width-- > 0))
    p->temp[p->ti++] = buf;
  p->temp[p->ti++] = '%';
  while ((p->f_minus) && (width-- > 0))
    p->temp[p->ti++] = buf;
  data_record(p);
}

void printf_init(t_printf *p, int start)
{
  if (start)
  {
    p->fi = 0;
    p->di = 0;
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

void print_c(t_printf *p)
{
  char  c;
  char  buf;
  int   custom;

  c = (char)va_arg(p->argptr, int);
  buf = (p->f_zero && !p->f_minus) ? '0' : 32;
  custom = (p->f_width) ? p->width -1 : 0;
  custom = (custom < 0) ? 0 : custom;
  while ((!p->f_minus) && (custom-- > 0))
    p->temp[p->ti++] = buf;
  p->temp[p->ti++] = c;
  while ((p->f_minus) && (custom-- > 0))
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
    if ('*' == *(p->format + p->fi))
    {
      p->f_prec = true;
      p->prec = va_arg(p->argptr, int);
      ++p->fi;
    }
    else 
    {
      p->prec = ft_atoi(p->format + p->fi); // как обработать?
      p->f_prec = true;
      while (('0' <= p->format[p->fi]) && (p->format[p->fi] <= '9'))
        ++p->fi;
    }
  }
}

int  distribution(t_printf *p, char c)
{
  if ('c' == c)
    print_c(p);
  else if ('p' == c)
    print_p(p);
  else if ('%' == c)
    print_per(p);
  else if ('s' == c)
    print_s(p);
  else if (('d' == c) || ('i' == c) || ('u' == c))
  {
    if (p->f_l)
      print_d(p, va_arg(p->argptr, long ));
    else if ((p->f_ll) || ('u' == c))
      print_d(p, va_arg(p->argptr, long long));
    else
      print_d(p, va_arg(p->argptr, int));
  }
  else if ('o' == c)
    print_o(p, (unsigned long)va_arg(p->argptr, unsigned long long));
  else if (('x' == c) || ('X' == c))
    print_x(p, (unsigned long)va_arg(p->argptr, unsigned long long));
  else if (('f' == c) || ('F' == c))
  {
    if (p->f_L)
      print_f(p, (long double)va_arg(p->argptr, long double));
    else
      print_f(p, va_arg(p->argptr, double));
  }
  else if (('e' == c) || ('E' == c))
    print_e(p);
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

  p.print_size = 0;
  printf_init(&p, 1);
  ft_bzero(p.data, BUFF);
  p.di = 0;
  p.format = format;
  parser(&p);
  //va_arg(argptr, int);
  data_release(&p);
  /* завершение */
  va_end(p.argptr);
  return (p.print_size);
}
