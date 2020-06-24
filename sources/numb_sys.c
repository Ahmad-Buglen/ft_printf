/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numb_sys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:15:30 by dphyliss          #+#    #+#             */
/*   Updated: 2020/06/24 14:29:35 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			print_u(t_printf *const p, const unsigned long long number)
{
	int			length;
	char		buf;
	int			prec;
	int			width;

	p->f_zero = p->f_minus || p->f_prec ? false : p->f_zero;
	length = ft_count_p(number, 10);
	length = p->f_prec && 0 == p->prec ? 0 : length;
	buf = p->f_zero ? '0' : ' ';
	prec = (p->f_prec && (p->prec - length > 0)) ? p->prec - length : 0;
	width = p->f_width ? p->width - (length + p->f_space + prec) : 0;
	width = width > 0 ? width : 0;
	while (!(p->f_minus) && width-- > 0)
		p->temp[p->ti++] = buf;
	while (prec-- > 0)
		p->temp[p->ti++] = '0';
	if (length > 0)
		ull_to_p_base(p, number, 10);
	while (p->f_minus && (width-- > 0))
		p->temp[p->ti++] = ' ';
	data_record(p);
}

void			print_x(t_printf *const p, const unsigned long long number)
{
	t_option	o;

	p->f_zero = p->f_minus || p->f_prec ? false : p->f_zero;
	o.len = ft_count_p(number, 16);
	o.lattice = p->f_lattice && number != 0 ? 2 : 0;
	o.prec = p->f_prec && (p->prec - o.len > 0) ? p->prec - o.len : 0;
	o.crutch = p->f_prec && 0 == number && 0 == p->prec ? 1 : 0;
	o.width = p->f_width ? p->width - (o.len + o.lattice) -
												o.prec + o.crutch : 0;
	while (!p->f_minus && !p->f_zero && (o.width-- > 0))
		p->temp[p->ti++] = p->f_zero ? '0' : ' ';
	if (2 == o.lattice)
	{
		p->temp[p->ti++] = '0';
		p->temp[p->ti++] = ('x' == p->format[p->fi]) ? 'x' : 'X';
	}
	while (p->f_zero && (o.width-- > 0))
		p->temp[p->ti++] = p->f_zero ? '0' : ' ';
	while (o.prec-- > 0)
		p->temp[p->ti++] = '0';
	if (!o.crutch)
		ull_to_p_base(p, number, 16);
	while (p->f_minus && (o.width-- > 0))
		p->temp[p->ti++] = ' ';
	data_record(p);
}

void			print_o(t_printf *const p, const unsigned long long number)
{
	t_option	o;

	p->f_zero = p->f_minus || p->f_prec ? false : p->f_zero;
	o.len = ft_count_p(number, 8);
	o.buf = p->f_zero ? '0' : ' ';
	o.lattice = p->f_lattice && number != 0 ? 1 : 0;
	o.prec = p->f_prec ? p->prec - (o.len + o.lattice) : 0;
	o.prec = o.prec > 0 ? o.prec : 0;
	o.zero = p->f_prec && 0 == p->prec ? 1 : 0;
	o.crutch = p->f_lattice && o.zero ? 1 : 0;
	o.short_note = 0 == number && o.zero ? 1 : 0;
	o.width = p->f_width ? p->width - o.crutch + o.short_note -
							(o.len + o.lattice) - o.prec : 0;
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

void			print_b(t_printf *const p, const unsigned long long number)
{
	t_option	o;

	p->f_zero = p->f_minus || p->f_prec ? false : p->f_zero;
	o.len = ft_count_p(number, 2);
	o.buf = p->f_zero ? '0' : ' ';
	o.prec = p->f_prec && (p->prec - o.len > 0) ? p->prec - o.len : 0;
	o.crutch = p->f_prec && 0 == number && 0 == p->prec ? 1 : 0;
	o.width = p->f_width ? p->width - o.len - o.prec + o.crutch : 0;
	while (!p->f_minus && !p->f_zero && (o.width-- > 0))
		p->temp[p->ti++] = o.buf;
	while (p->f_zero && (o.width-- > 0))
		p->temp[p->ti++] = o.buf;
	while (o.prec-- > 0)
		p->temp[p->ti++] = '0';
	if (!o.crutch)
		ull_to_p_base(p, number, 2);
	while (p->f_minus && (o.width-- > 0))
		p->temp[p->ti++] = ' ';
	data_record(p);
}

void			print_p(t_printf *const p, const long long n)
{
	int			width;
	int			space;

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
