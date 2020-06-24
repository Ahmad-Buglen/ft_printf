/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:12:34 by dphyliss          #+#    #+#             */
/*   Updated: 2020/06/24 16:38:57 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		init_d_options(t_printf *const p, long long *const number,
								t_option *const o)
{
	p->f_zero = p->f_minus || p->f_prec ? false : p->f_zero;
	o->flag = *number < 0 ? 1 : 0;
	*number = *number < 0 ? -(*number) : *number;
	o->sign = p->f_plus || o->flag ? 1 : 0;
	p->f_space = o->sign ? false : p->f_space;
	o->len = ft_count_p(*number, 10);
	o->len = 0 == *number && p->f_prec && 0 == p->prec ? 0 : o->len;
	o->buf = p->f_zero ? '0' : ' ';
	o->prec = (p->f_prec && (p->prec - o->len > 0)) ?
												p->prec - o->len : 0;
	o->width = p->f_width ?
			p->width - (o->len + o->sign + p->f_space + o->prec) : 0;
	o->width = o->width > 0 ? o->width : 0;
}

void			print_d(t_printf *const p, long long number)
{
	t_option	o;

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
	if (o.len > 0)
		ull_to_p_base(p, number, 10);
	while (p->f_minus && (o.width-- > 0))
		p->temp[p->ti++] = ' ';
	data_record(p);
}

static void		distribution_float(t_printf *const p, const char c)
{
	if (('f' == c) || ('F' == c))
	{
		if (p->f_lbig)
			print_f(p, va_arg(p->argptr, long double));
		else
			print_f(p, va_arg(p->argptr, double));
	}
	else if (('e' == c) || ('E' == c))
	{
		if (p->f_lbig)
			print_e(p, va_arg(p->argptr, long double));
		else
			print_e(p, va_arg(p->argptr, double));
	}
	else if ('b' == c)
		print_b(p, (unsigned long)va_arg(p->argptr, unsigned long long));
	else if ('r' == c)
		print_r(p, va_arg(p->argptr, int));
}

int				distribution(t_printf *const p, const char c)
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
			print_d(p, va_arg(p->argptr, long));
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
	distribution_float(p, c);
	return (1);
}

int				ft_printf(char *const format, ...)
{
	t_printf	p;

	va_start(p.argptr, format);
	printf_init(&p, 1);
	ft_bzero(p.data, BUFF);
	p.format = format;
	parser(&p);
	data_release(&p);
	va_end(p.argptr);
	return (p.print_size);
}
