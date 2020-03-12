/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modficate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vletterp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 16:13:56 by vletterp          #+#    #+#             */
/*   Updated: 2020/03/06 08:33:15 by vletterp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void modif_check(t_printf *p)
{
	check_hh(t_printf *p);
	check_h(t_printf *p);
	check_ll(t_printf *p);
	check_l(t_printf *p);
	check_largel(t_printf *p);
}

char	modificate(va_list *arg, t_printf *p)
{
	char *modificated;
	intmax_t tmp;

	modificated = ft_strnew(1);
	tmp = va_arg(*arg, uintmax_t);

	if (p->f_l == true) // используется с			d, i, o, u, x и X, n.
		tmp = (long int)tmp;
	else if (p->f_ll == true) // используется с		d, i, o, u, x и X, n.	
		tmp = (long long)tmp;
	else if (p->f_h == true) // используется с      d, i, o, u, x и X, n.
		tmp = (short int)tmp;
	else if (p->f_hh == true) // используется с     d, i, o, u, x и X, n
		tmp = (char)tmp;
	else if (p->f_largel == true)
		tmp = (long double)tmp;  // используется с	e, E, f, g и G.
	modificated = ft_itoa_base(tmp, 8);
	return (modificated);
}