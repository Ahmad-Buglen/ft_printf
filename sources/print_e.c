/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_e.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:05:46 by dphyliss          #+#    #+#             */
/*   Updated: 2020/06/24 16:41:59 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		init_e_options(t_printf *const p, long double number,
									t_option *const o)
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

static void		fract_conv_two(const long double number, t_option *const o)
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

static void		fract_conv(t_printf *const p, const long double number,
								t_option *const o)
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
		fract_conv_two(number, o);
	o->len = ft_count_p(o->frac, 10);
	o->frac = o->len > o->prec ? o->frac /
				ft_pow(10, o->len - o->prec) : o->frac;
	ull_to_p_base(p, o->whol, 10);
	if (o->dot)
		p->temp[p->ti++] = '.';
}

void			print_e(t_printf *const p, const long double number)
{
	t_option	o;

	init_e_options(p, number, &o);
	fract_conv(p, number, &o);
	if (o.frac != 0)
	{
		ull_to_p_base(p, o.frac, 10);
		o.prec -= o.len;
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
	while (p->f_minus && (o.width-- > 0))
		p->temp[p->ti++] = ' ';
	data_record(p);
}
