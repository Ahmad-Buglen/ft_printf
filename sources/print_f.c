/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:12:02 by dphyliss          #+#    #+#             */
/*   Updated: 2020/06/23 19:12:45 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

unsigned long long rounding(t_printf *const p, t_option *const o)
{
	int		extra;
	int		digit;
	int		zero;

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
		if ((ft_count_p(o->frac + 10, 10) >
					ft_count_p(o->frac, 10)) && (0 == zero))
		{
			o->whol += 1;
			o->frac = 0;
		}
		else
			o->frac += 10;
	}
	return(o->frac);
}

static void init_f_options(t_printf *const p, long double number, t_option *const o)
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
	o->zero = ft_abs(ft_count_p(o->frac, 10) -
										((o->prec > PREC) ? PREC : o->prec));
	o->dot = ((p->f_prec && o->prec != 0) || !p->f_prec || p->f_lattice) ?
																	1 : 0;
	o->sign = o->flag || p->f_plus ? 1 : 0;
	o->buf = p->f_zero ? '0' : ' ';
	o->width = p->width - (o->dot + o->sign +
							ft_count_p(o->whol, 10) + p->f_space + o->prec);
	if (o->sign && p->f_zero)
	p->temp[p->ti++] = o->flag ? '-' : '+';
	if (p->f_space)
	p->temp[p->ti++] = ' ';
	while (!p->f_minus && (o->width-- > 0))
	p->temp[p->ti++] = o->buf;
}

void print_f(t_printf *const p, const long double number)
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