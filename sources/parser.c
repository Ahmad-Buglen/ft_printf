/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:17:52 by dphyliss          #+#    #+#             */
/*   Updated: 2020/06/23 19:18:46 by dphyliss         ###   ########.fr       */
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
	p->f_L = false;
}


int print_ub(t_printf *const p)
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


void modif_check(t_printf *const p)
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

void flags_and_wid_check(t_printf *const p)
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
		if (p->width < 0)
		{
			p->f_minus = true;
			p->width = ft_abs(p->width);
		}
		++p->fi;
	}
}

void prec_check(t_printf *const p)
{
	if ('.' == p->format[p->fi])
	{
		++p->fi;
		p->f_prec = true;
		if ('*' == *(p->format + p->fi))
		{
			p->prec = va_arg(p->argptr, int);
			if (p->prec < 0)
				p->f_prec = false;
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