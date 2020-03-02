
#include "../includes/ft_printf.h"
#include <stdio.h>
#include <math.h>

void		ft_putnstr(char const *s, size_t n)
{
	if (s)
    write(1, s, n);
    // if n == 0 ?
}


int ft_power(int n, int power)
{
	int rez;

	rez = n;
	if (0 == power)
		return (1);
	else if (1 == power)
		return (rez);
	else
		while (power > 1 )
		{
			rez *= n;
			--power;
		}
	return (rez);
}

int ft_ret(char c)
{
	if ((c >= '0') && ('9' >= c))
		return (c - 48);
	else if ((c >= 'a') && ('f' >= c))
		return (c - 87);
	else if ((c >= 'A') && ('F' >= c))
		return (c - 55);
	return(0);
}

static int			ft_count_p(unsigned long long c, int base)
{
	int				q;

	q = 1;
	while (c / base)
	{
		c = c / base;
		q++;
	}
	return (q);
}

void ft_itoa_base(t_printf *p, long long n, int base)
{
  char *a;
  char *A;
  int length;
  int buf;
 // char *A;

  a = "0123456789abcdef";
  A = "0123456789ABCDEF";

 // if (n < 0)
  //  p->temp[p->ti++] = '-';
  length = ft_count_p(n, base);
  buf = length--;
  while (length >= 0)
	{
		p->temp[p->ti + length--] = ('X' == p->format[p->fi]) ? A[(n % base)] : a[(n % base)];
		n /= base;
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
  if (BUFF > p->di + p->ti) // ?
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
    else // maybe ? (BUFF <= p->ti)
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

void print_d(t_printf *p)
 {
  char *str;
  int length;
  int n;
  char buf;
  int  flag;
  int prec;
  int width;
  int sign;
  int i;
  p->f_zero = ((p->f_minus) || (p->f_prec)) ? false : p->f_zero;
  
  n = va_arg(p->argptr, long long);
  flag = (n < 0) ? 1 : 0;
  n = (n < 0) ? -n : n;
  sign = (p->f_plus || flag) ? 1 : 0;
  p->f_space = sign ? false : p->f_space;
  str = ft_itoa(n);
  length = ft_strlen(str);
  length = ((0 == n) && p->f_prec && (0 == p->prec)) ? 0 : length;
  buf = (p->f_zero) ? '0' : ' ';
  prec = (p->f_prec) ?  p->prec - length : 0;
  prec = (prec > 0) ? prec : 0;
  width = (p->f_width) ? p->width - (length + sign + ((p->f_space) ? 1 : 0)): 0;
  width = (prec > 0) ? width - prec : width;
  // width = !(p->f_minus) ? width : 0;
  width = (width > 0) ? width : 0;

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

  ft_strncpy(p->temp + p->ti, str, length);
  p->ti += length;

  //if ((p->f_width) && (p->width > length) && (p->f_minus)) //ti
  while(p->f_minus && (width-- > 0))
    p->temp[p->ti++] = ' ';
  free(str);
  data_record(p);
}

char				*ft_ulltoa(unsigned long long n)
{
	int				len;
	unsigned long long	q;
	char			*res;

	len = ft_count_p(n, 10);
//	len = (n < 0 ? len + 1 : len);
//	q = (n < 0 ? -n : n);
  q = n;
	if (!(res = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	res[len--] = '\0';
	while (len >= 0)
	{
		res[len--] = (q % 10) + '0';
		q /= 10;
	}
	// if (res[0] == '0' && res[1] != '\0')
	// 	res[0] = '-';
	return (res);
}

int				ft_atoull(const char *str)
{
	unsigned long long	n;
	int			sign;

	n = 0;
	while ((*str == ' ') || (*str == '\n') || (*str == '\t')
			|| (*str == '\f') || (*str == '\r') || (*str == '\v'))
		++str;
//	sign = (*str == '-') ? -1 : 1;
//	((*str == '-') || (*str == '+')) ? ++str : 0;
	while ((*str >= '0') && (*str <= '9'))
	{
		if (((n * 10) / 10) != n)
			return ((sign == -1) ? 0 : -1);
		n = 10 * n + (*str - '0');
		++str;
	}
//	n = (-1 == sign) ? -n : n;
	return (n);
}

unsigned long long rounding(unsigned long long frac, int prec,
                              unsigned long long *whol)
{
  int i;
  int j;
  int width;
  int digit;
  int zero;
  
  if (prec >= 19)
    prec = 19;
  else 
    prec += 1;

    zero = ft_abs(ft_count_p(frac, 10) - 19);
    width = prec - zero;
    frac = frac / pow(10, ft_abs(width - (19 - zero)));

  // width = ft_count_p(fract)  - prec
  // fract = fract / pow(10, );
  // j = 1;
  // while ((i > 0) && !remainder)
  // {
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
  //   ++j;
  //   --i;
  // }
  return(frac);
}

void print_f(t_printf *p)
 {
  char *whole;
  char *fract;
  int whole_l;
  int fract_l;
  unsigned long long whol;
  unsigned long long frac;
  long double n;
  char buf;
  char  flag;
  char  sign;
  int zero;
  int prec;
  int width;
  int i;
  int dot;

  p->f_zero = (p->f_minus) ? false : p->f_zero;
  n = va_arg(p->argptr,   double);
  flag = n < 0 ? 1 : 0;
  n = (n < 0) ? -n : n;
  p->f_space = (p->f_plus || flag) ? false : p->f_space;
    prec = (p->f_prec) ?  p->prec : 6;
  prec = (prec > 0) ? prec : 0;
  
  unsigned long long temp = n;
    frac = (n - temp) * pow(10.0, 19);
    whol = n;
  frac = rounding(frac, prec, &whol);

fract = ft_ulltoa(frac);
  // printf("fract = %s\n", fract);
  fract_l = ft_strlen(fract);

  whole = ft_ulltoa(whol);
  
  // printf("whole = %s\n", whole);
   whole_l = ft_strlen(whole);

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

  // i = prec;
  // while (i-- > 0)
  // p->temp[p->ti++] = '0';
  // if (!(p->f_prec) ||
  // (!((0 == n) && p->f_prec && (0 == prec))))
  // {
    ft_strncpy(p->temp + p->ti, whole, whole_l);
    p->ti += whole_l;
  // }
  if (dot)
    p->temp[p->ti++] = '.';

  
  if (ft_atoull(fract) != 0)
  {
    // zero = ft_count_p(frac, 10) - 19;
    int z = prec - (ft_count_p(frac, 10) - 1);
    zero = z;
    while (z-- > 0)
     p->temp[p->ti++] = '0';
    ft_strncpy(p->temp + p->ti, fract, prec - zero);
    p->ti += prec - zero;
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


void print_x(t_printf *p)
{
  unsigned long long n;
  int  buf;
  int width;
  int prec;
  int length;
  char  flag;
  int i;
  int sign;
  int lattice;

  p->f_zero = ((p->f_minus) || (p->f_prec)) ? false : p->f_zero;
  p->f_space = (p->f_plus) ? false : p->f_space;

  n = va_arg(p->argptr, unsigned long long);
  length = ft_count_p(n, 16);
  buf = (p->f_zero) ? '0' : ' ';
  lattice = (p->f_lattice && n != 0) ? 2 : 0;
  prec = (p->f_prec) ? p->prec - length : 0;
  prec = (prec > 0) ? prec : 0;

  width = (p->f_width) ? p->width - (length + lattice) : 0;
  width = ((p->f_prec) && (0 == n) && (0 == p->prec) && (p->f_width)) ? width + 1 : width;
  width = (prec > 0) ? width - prec : width;
  width = !(p->f_minus) ? width : 0;


  i = width;
  while (!(p->f_zero) &&  (i-- > 0))
    p->temp[p->ti++] = buf;

   if (2 == lattice)
   {
    p->temp[p->ti++] = '0';
    p->temp[p->ti++] = ('x' == p->format[p->fi]) ? 'x' : 'X';
   }

  while ((p->f_zero) &&  (i-- > 0))
    p->temp[p->ti++] = buf;

     i = prec;
  while (i-- > 0)
    p->temp[p->ti++] = '0';

 if (!((0 == n) && p->f_prec && (0 == p->prec)))
    ft_itoa_base(p, n, 16);
 

  if ((p->f_width) && (p->width > p->ti) && p->f_minus) //ti
      while(p->width > p->ti)
        p->temp[p->ti++] = ' ';

  data_record(p);
}



void print_o(t_printf *p)
{
  long long n;
  int  buf;
  int width;
  int prec;
  int length;
  char  flag;
  int i;
  int sign;
  int lattice;

  p->f_zero = ((p->f_minus) || (p->f_prec)) ? false : p->f_zero;

  n = va_arg(p->argptr, long long);
  length = (n > 0) ? ft_count_p(n, 8) : 0 ;
   
  buf = (p->f_zero) ? '0' : ' ';
  lattice = (p->f_lattice ) ? 1 : 0;
  prec = (p->f_prec) ? p->prec - length - ((lattice || (0 == n)) ? 1 : 0) : 0;
  prec = (prec > 0) ? prec : 0;

  width = (p->f_width) ? p->width - length - ((lattice || (0 == n)) ? 1 : 0) : 0;
  // width = (0 == n) ? width + 1:   width;
 // width = (p->f_prec && (0 == n) && (0 == p->prec) && p->f_width) ? width + 1 : width;
  width = (prec > 0) ? width - prec : width;
  width = !(p->f_minus) ? width : 0;

  i = width;
  while (i-- > 0)
    p->temp[p->ti++] = buf;
  
  i = prec;
  while (i-- > 0)
    p->temp[p->ti++] = '0';

   if (lattice )
    p->temp[p->ti++] = '0';

//  if ((0 != n) || (p->f_prec && (0 != p->prec)) ||  (!p->f_prec || (0 == n) && (lattice != 1)))
    if ((0 != n) || (p->f_prec && (0 != p->prec)) || (!p->f_prec && (0 == n) && !lattice ) ) 
      ft_itoa_base(p, n, 8);
    
  if ((p->f_width) && (p->width > p->ti) && p->f_minus) //ti
      while(p->width > p->ti)
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
  ft_itoa_base(p, n, 16);
  while(p->f_minus && (space-- > 0))
    p->temp[p->ti++] = ' ';
  data_record(p);
}

void print_per(t_printf *p)
{
  // char  buf;

  // buf = (p->f_zero && !p->f_minus) ? '0' : ' ';
  // p->width = (p->f_width) ? p->width : 1;
  // if (1 == p->width)
  //   p->temp[p->ti++] = c;
  // else
  //   p->temp[p->ti++] = (p->f_minus) ? c : buf;
  // if (p->width > 1)
  // {
  //   --p->width;
  //   while (--p->width)
  //     p->temp[p->ti++] = buf;
  //   p->temp[p->ti++] = (p->f_minus) ? buf : c;
  // }

  char  buf;
  int   custom;

  buf = (p->f_zero && !p->f_minus) ? '0' : ' ';
  custom = (p->f_width) ? p->width - 1 : 0;
  custom = (custom < 0) ? 0 : custom;
  while ((!p->f_minus) && (custom-- > 0))
    p->temp[p->ti++] = buf;
  p->temp[p->ti++] = '%';
  while ((p->f_minus) && (custom-- > 0))
    p->temp[p->ti++] = buf;
  data_record(p);
}

// char				*ft_itoa_p(int n)
// {
// 	int				len;
// 	unsigned int	q;
// 	char			*res;

// 	len = ft_count_p(n);
// 	len = (n < 0 ? len + 1 : len);
// 	q = (n < 0 ? -n : n);
// 	if (!(res = (char *)malloc(sizeof(char) * len + 1)))
// 		return (NULL);
// 	res[len--] = '\0';
// 	while (len >= 0)
// 	{
// 		res[len--] = (q % 10) + '0';
// 		q /= 10;
// 	}
// 	if (res[0] == '0' && res[1] != '\0')
// 		res[0] = '-';
// 	return (res);
// }


int	ft_atoi_base(const char *nbr, unsigned int base)
{
	int		n;
	int 	i;
	int 	length;
	int 	sign;

	length = 0;
	while (nbr[length])
		++length;
	sign = ('-' == nbr[0]) ? 1 : 0;
	i = ('-' == nbr[0]) ? 1 : 0;
	n = 0;
	while (i < length)
	{
		n += ft_ret(nbr[i]) * ft_power(base, length - i - 1);
		++i;
	}
	n = (1 == sign) ? -n : n;
	return (n);
}



void printf_init(t_printf *p)
{
  p->f_minus = false;
  p->f_plus = false;
  p->f_space = false;
  p->f_lattice = false;
  p->f_zero = false;
  p->flag = false;
  p->f_width = false;
  p->f_prec = false;
  p->ti = 0;
  ft_bzero(p->temp, BUFF);

  //      format;
  p->f_h = false;
  p->f_hh = false;
  p->f_l = false;
  p->f_ll = false;
}

void print_c(t_printf *p)
{
  char  c;
  char  buf;
  int   custom;

  c = (char)va_arg(p->argptr, int);
  buf = (p->f_zero && !p->f_minus) ? '0' : ' ';
  custom = (p->f_width) ? p->width -1 : 0;
  custom = (custom < 0) ? 0 : custom;
  while ((!p->f_minus) && (custom-- > 0))
    p->temp[p->ti++] = buf;
  p->temp[p->ti++] = c;
  while ((p->f_minus) && (custom-- > 0))
    p->temp[p->ti++] = buf;
  data_record(p);
}

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
int print_ub(t_printf *p)
{
  // char *conversions; // cp%sdioxXfF
  // p->temp[p->ti++] = 'U';
  // p->temp[p->ti++] = 'B';

  if (('\0' == p->format[p->fi + 1]) ||
      !(ft_cinstr(&(p->format[p->fi + 1]), "cp%sdioxXfF")))
  {
    //ft_strncpy(p->temp, p->format[p->fi + 1], ft_strlen(&(p->format[p->fi + 1])));
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
}

void flags_check(t_printf *p)
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
}

void wid_and_prec_check(t_printf *p)
{
  if (('0' <= *(p->format + p->fi)) && (*(p->format + p->fi) <= '9'))
  {
    p->width = ft_atoi(p->format + p->fi); // как обработать? 
    p->f_width = true;
    while (('0' <= p->format[p->fi]) && (p->format[p->fi] <= '9'))
      ++p->fi;
  }
  if ('.' == p->format[p->fi])
  {
    ++p->fi;
    p->prec = ft_atoi(p->format + p->fi); // как обработать?
    p->f_prec = true;
    while (('0' <= p->format[p->fi]) && (p->format[p->fi] <= '9'))
      ++p->fi;
  }
}

int  distribution(t_printf *p, char c)
{
  // c = \0 ? cp%sdioxXfF
  if ('c' == c)
    print_c(p);
  else if ('p' == c)
    print_p(p);
  else if ('%' == c)
    print_per(p);
  else if ('s' == c)
    print_s(p);
  else if (('d' == c) || ('i' == c))
    print_d(p);
  else if ('o' == c)
    print_o(p);
  else if (('x' == c) || ('X' == c))
    print_x(p);
  else if (('f' == c) || ('F' == c))
    print_f(p);
  // else
  //   print_ub(p);
  return 1;
}

void parser(t_printf *p)
{
  size_t i;

  p->fi = 0;
  p->di = 0;
  while (p->format[p->fi])
  {
    if ('%' == p->format[p->fi])
    {
      if (1 == print_ub(p))
        return ;
      ++p->fi;
      flags_check(p);
      wid_and_prec_check(p);
      modif_check(p);
      p->flag = true;
      distribution(p, p->format[p->fi]);
      printf_init(p);
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
  printf_init(&p);
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
