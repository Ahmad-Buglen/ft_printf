/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:17:52 by dphyliss          #+#    #+#             */
/*   Updated: 2020/06/24 16:42:23 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		print_ub(t_printf *const p)
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

void	modif_check(t_printf *const p)
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
		p->f_lbig = true;
		++p->fi;
	}
}

void	flags_and_wid_check(t_printf *const p)
{
	while (('-' == p->format[p->fi]) || ('+' == p->format[p->fi]) || (' ' ==
p->format[p->fi]) || ('#' == p->format[p->fi]) || ('0' == p->format[p->fi]))
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
		p->width = ft_atoi(p->format + p->fi);
		p->f_width = true;
		while (('0' <= p->format[p->fi]) && (p->format[p->fi] <= '9'))
			++p->fi;
	}
	else if ('*' == *(p->format + p->fi))
	{
		p->f_width = true;
		p->width = va_arg(p->argptr, int);
		p->f_minus = p->width < 0 ? true : p->f_minus;
		p->width = p->width < 0 ? ft_abs(p->width) : p->width;
		++p->fi;
	}
}

void	prec_check(t_printf *const p)
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
			p->prec = ft_atoi(p->format + p->fi);
			while (('0' <= p->format[p->fi]) && (p->format[p->fi] <= '9'))
				++p->fi;
		}
	}
}

void	parser(t_printf *const p)
{
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
