/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_man.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:43:40 by dphyliss          #+#    #+#             */
/*   Updated: 2020/06/24 17:10:49 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	printf_init(t_printf *const p, const int start)
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
	p->f_lbig = false;
}

void	ull_to_p_base(t_printf *const p, unsigned long long number,
														const int base)
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

void	data_release(t_printf *const p)
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
