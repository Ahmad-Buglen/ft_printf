
#include "../includes/ft_printf.h"

void		ft_putnstr(char const *s, size_t n)
{
	if (s)
    write(1, s, n);
    // if n == 0 ?
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
  int  buf;
  int length;

  str = va_arg(p->argptr, char *);
  length = ft_strlen(str);
  p->width = (p->f_width) ? p->width : length ;
  if ((p->f_prec) && (p->precision) && (p->f_width) && (p->precision > p->f_width))
  {
    p->width = length;
    p->f_prec = false;
  }
  else if ((p->f_prec) && (p->precision))
    length = p->precision;


  if ((p->f_width) && (p->width > length) && (!p->f_minus))
    while(p->width - (length + p->ti))
      p->temp[p->ti++] = ' ';

  ft_strncpy(p->temp + p->ti, str, length);
  p->ti += length;

  if ((p->f_width) && (p->width > length) && (p->f_minus)) //ti
    while(p->width < p->ti)
      p->temp[p->ti++] = ' ';
  data_record(p);
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

static int			ft_count_p(long long c, int base)
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
  int length;
  int buf;
 // char *A;

  a = "0123456789abcdef";
 // A = "0123456789ABCDEF";

  if (n < 0)
    p->temp[p->ti++] = '-';
  length = ft_count_p(n, base);
  buf = length--;
  while (length >= 0)
	{
		p->temp[p->ti + length--] = a[(n % base)];
		n /= base;
	}
  p->ti += buf;
}


void print_p(t_printf *p)
{
  long long n;
  int  buf;
  int width;

  n = va_arg(p->argptr, long long);
  width = (0 == n) ? 3 : 12;
  if ((p->f_width) && (p->width > width) && (!p->f_minus))
    while(p->width - (width + p->ti))
      p->temp[p->ti++] = ' ';
  p->temp[p->ti++] = '0';
  p->temp[p->ti++] = 'x';
  ft_itoa_base(p, n, 16);
  if ((p->f_width) && (p->width > 12) && (p->f_minus))
    while(p->width < p->ti)
      p->temp[p->ti++] = ' ';
  data_record(p);
}

void print_per(t_printf *p)
{
  char  c;
  char  buf;

  c = '%';
  buf = (p->f_zero && !p->f_minus) ? '0' : ' ';
  p->width = (p->f_width) ? p->width : 1;
  if (1 == p->width)
    p->temp[p->ti++] = c;
  else
    p->temp[p->ti++] = (p->f_minus) ? c : buf;
  if (p->width > 1)
  {
    --p->width;
    while (--p->width)
      p->temp[p->ti++] = buf;
    p->temp[p->ti++] = (p->f_minus) ? buf : c;
  }
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
  p->format = false;
  p->f_width = false;
  p->f_prec = false;
  p->ti = 0;
  ft_bzero(p->temp, BUFF);
}

void print_c(t_printf *p)
{
  char  c;
  char  buf;

  c = (char)va_arg(p->argptr, int);
  buf = (p->f_zero && !p->f_minus) ? '0' : ' ';
  p->width = (p->f_width) ? p->width : 1;
  if (1 == p->width)
    p->temp[p->ti++] = c;
  else
    p->temp[p->ti++] = (p->f_minus) ? c : buf;
  if (p->width > 1)
  {
    --p->width;
    if (BUFF >= p->width)
    {
      while (--p->width)
        p->temp[p->ti++] = buf;
    }
    // else
    // { // ? 
    //   data_release(p);
    //   while (--p->width)
    //   {
    //     p->data[p->di++] = buf;
    //     if (BUFF == p->di)
    //       data_release(p);
    //   }
    // }
    p->temp[p->ti++] = (p->f_minus) ? buf : c;
  }
 // p->temp[p->ti] = '\0';
  data_record(p);
}





void flags_check(t_printf *p, char *str)
{
  while (('-' == str[p->fi]) || ('+' == str[p->fi]) ||
    (' ' == str[p->fi]) || ('#' == str[p->fi]) || ('0' == str[p->fi]))
  {
    p->f_minus = ('-' == str[p->fi]) ? true : p->f_minus; 
    p->f_plus = ('+' == str[p->fi]) ? true : p->f_plus;
    p->f_space = (' ' == str[p->fi]) ? true : p->f_space;
    p->f_lattice = ('#' == str[p->fi]) ? true : p->f_lattice;
    p->f_zero = ('0' == str[p->fi]) ? true : p->f_zero;
    ++p->fi;
  }
  // ft_putstr("flags_check\n");
  // ft_putnbr(p->fi);
  // write(1, "\n", 1);
}

void wid_and_prec_check(t_printf *p, char *str)
{
  if (('0' <= *(str + p->fi)) && (*(str + p->fi) <= '9'))
  {
    p->width = ft_atoi(str + p->fi); // как обработать? 
    p->f_width = true;
    while (('0' <= str[p->fi]) && (str[p->fi] <= '9'))
      ++p->fi;
  }
  if ('.' == str[p->fi])
  {
    ++p->fi;
    p->precision = ft_atoi(str + p->fi); // как обработать?
    p->f_prec = true;
    while (('0' <= str[p->fi]) && (str[p->fi] <= '9'))
      ++p->fi;
  }
}

int  distribution(t_printf *p, char c)
{
  // c = \0 ?
  if ('c' == c)
    print_c(p);
  else if ('p' == c)
    print_p(p);
  else if ('%' == c)
    print_per(p);
  else if ('s' == c)
    print_s(p);
  return 1;
}

void parser(char *str, t_printf *p)
{
  size_t i;

  p->fi = 0;
  p->di = 0;
  while (str[p->fi])
  {
    if ('%' == str[p->fi])
    {
      ++p->fi;
      flags_check(p, str);
      wid_and_prec_check(p, str);
      p->format = true;
      distribution(p, (str[p->fi]));
      printf_init(p);
    }
    else
    {
      p->temp[0] = str[p->fi];
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
  parser(format, &p);
  //va_arg(argptr, int);
  data_release(&p);
  /* завершение */
  va_end(p.argptr);
  return (p.print_size);
}
