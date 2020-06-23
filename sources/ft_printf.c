/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:12:34 by dphyliss          #+#    #+#             */
/*   Updated: 2020/06/23 19:18:41 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ull_to_p_base(t_printf *const p, unsigned long long number,
														const int base)
{
	int	 length;
	int	 buf;

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

void data_release(t_printf *const p)
{
	if (p->di)
	{
		p->print_size += p->di;
		ft_putnstr(p->data, p->di);
		p->di = 0;
	}
}

void	data_record(t_printf *const p)
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

 void	 print_s(t_printf *const p, char const *str)
 {
	int	 length;
	int	 space;

	if (NULL == str)
	str = "(null)";
	length = ft_strlen(str);
	length = p->f_prec && p->prec < length ? p->prec : length;
	space = p->f_width ? p->width - length : 0;
	space = space < 0 ? 0 : space;
	while (!p->f_minus && (space-- > 0))
		p->temp[p->ti++] = ' ';
	if (BUFF > length + p->ti)
	{
		ft_strncpy(p->temp + p->ti, str, length);
		p->ti += length;
	}
	else
	{
		data_release(p);
		write(1, str, length);
		p->print_size += length;
	}
	while (p->f_minus && (space-- > 0))
		p->temp[p->ti++] = ' ';
	data_record(p);
 }

void	init_d_options(t_printf *const p, long long *const number, t_option *const o)
{
	p->f_zero = p->f_minus || p->f_prec ? false : p->f_zero;
	o->flag = *number < 0 ? 1 : 0;
	*number = *number < 0 ? -(*number) : *number;
	o->sign = p->f_plus || o->flag ? 1 : 0;
	p->f_space = o->sign ? false : p->f_space;
	o->length = ft_count_p(*number, 10);
	o->length = 0 == *number && p->f_prec && 0 == p->prec ? 0 : o->length;
	o->buf = p->f_zero ? '0' : ' ';
	o->prec = (p->f_prec && (p->prec - o->length > 0)) ?
												p->prec - o->length : 0;
	o->width = p->f_width ?
			p->width - (o->length + o->sign + p->f_space + o->prec) : 0;
	o->width = o->width > 0 ? o->width : 0;
}

void print_d(t_printf *const p, long long number)
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

void		print_u(t_printf *const p, const unsigned long long number)
{
	int		length;
	char	buf;
	int		prec;
	int		width;

	p->f_zero = p->f_minus || p->f_prec ? false : p->f_zero;
	length = ft_count_p(number, 10);
	length = p->f_prec && 0 == p->prec ? 0 : length;
	buf = p->f_zero ? '0' : ' ';
	prec = (p->f_prec && (p->prec - length > 0)) ?	p->prec - length : 0;
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

void print_x(t_printf *const p, const unsigned long long number)
{
	t_option	o;

	p->f_zero = p->f_minus || p->f_prec ? false : p->f_zero;
	o.length = ft_count_p(number, 16);
	o.lattice = p->f_lattice && number != 0 ? 2 : 0;
	o.prec = p->f_prec && (p->prec - o.length > 0) ? p->prec - o.length : 0;
	o.crutch = p->f_prec && 0 == number && 0 == p->prec ? 1 : 0;
	o.width = p->f_width ? p->width - (o.length + o.lattice) -
												o.prec + o.crutch : 0;
	while (!p->f_minus && !p->f_zero && (o.width-- > 0))
		p->temp[p->ti++] = p->f_zero ? '0' : ' ';;
	if (2 == o.lattice)
	{
		p->temp[p->ti++] = '0';
		p->temp[p->ti++] = ('x' == p->format[p->fi]) ? 'x' : 'X';
	}
	while (p->f_zero && (o.width-- > 0))
		p->temp[p->ti++] = p->f_zero ? '0' : ' ';;
	while (o.prec-- > 0)
		p->temp[p->ti++] = '0';
 	if (!o.crutch)
		ull_to_p_base(p, number, 16);
	while (p->f_minus && (o.width-- > 0))
		p->temp[p->ti++] = ' ';
	data_record(p);
}

void print_o(t_printf *const p, const unsigned long long number)
{
	t_option o;

	p->f_zero = p->f_minus || p->f_prec ? false : p->f_zero;
	o.length =	ft_count_p(number, 8) ;
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

void print_b(t_printf *const p, const unsigned long long number)
{
	t_option o;

	p->f_zero = p->f_minus || p->f_prec ? false : p->f_zero;
	o.length = ft_count_p(number, 2);
	o.buf = p->f_zero ? '0' : ' ';
	o.prec = p->f_prec && (p->prec - o.length > 0) ? p->prec - o.length : 0;
	o.crutch = p->f_prec && 0 == number && 0 == p->prec ? 1 : 0;
	o.width = p->f_width ? p->width - o.length - o.prec + o.crutch : 0;
	while (!p->f_minus && !p->f_zero && (o.width-- > 0))
		p->temp[p->ti++] = o.buf;
	while (p->f_zero &&	(o.width-- > 0))
		p->temp[p->ti++] = o.buf;
	while (o.prec-- > 0)
		p->temp[p->ti++] = '0';
 	if (!o.crutch)
		ull_to_p_base(p, number, 2);
	while (p->f_minus && (o.width-- > 0))
		p->temp[p->ti++] = ' ';
	data_record(p);
}

void	print_p(t_printf *const p, const long long n)
{
	int	 width;
	int	 space;

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

void	print_per(t_printf *const p)
{
	char	buf;
	int	 width;

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

void print_c(t_printf *const p, const char c)
{
	char	buf;
	int	 width;

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

void print_r(t_printf *const p, const char c)
{
	char	buf;
	int	 width;
	const char *mas[33] = {"nul", "soh", "stx", "etx", "eot", "enq", "ack",
					"bel", "bs", "ht", "nl", "vt", "np", "cr", "so", "si",
					"dle", "dc1", "dc2", "dc3", "dc4", "nak", "syn", "etb",
					"can", "em", "sub", "esc", "fs", "gs", "rs", "us", "sp"};

	buf = p->f_zero && !p->f_minus ? '0' : ' ';
	width = p->f_width ? p->width - 1 : 0;
	width = width < 0 ? 0 : width;
	while (!p->f_minus && (width-- > 0))
		p->temp[p->ti++] = buf;
	if (c >= 0 && c <= 32)
	{
		ft_strncpy(p->temp + p->ti, mas[c], ft_strlen(mas[c]));
		p->ti += ft_strlen(mas[c]);
	}
	while (p->f_minus && (width-- > 0))
		p->temp[p->ti++] = buf;
	data_record(p);
}


int	distribution(t_printf *const p, const char c)
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
	else if ('r' == c)
		print_r(p, va_arg(p->argptr, int));
	return 1;
}

void		parser(t_printf *const p)
{
	size_t	i;

	while (p->format[p->fi])
	{
	if ('%' == p->format[p->fi])
	{
		if (1 == print_ub(p))
		return ;
		// if ('\0' == p->format[p->fi + 1])
		//	 print_ub(p);
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

int ft_printf(char *const format, ...)
{
	t_printf p;

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
