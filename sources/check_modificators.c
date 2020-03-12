/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_modificators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vletterp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 07:55:25 by vletterp          #+#    #+#             */
/*   Updated: 2020/03/06 08:02:52 by vletterp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	check_hh(t_ptintf *p)
{
    if (('h' == p->format[p->fi]) && ('h' == p->format[p->fi + 1]) && (p->format[p->fi - 1] == 'd' 
				|| p->format[p->fi - 1] == 'i' || p->format[p->fi - 1] == 'o' || p->format[p->fi - 1] == 'u')
				|| p->format[p->fi - 1] == 'x' || p->format[p->fi - 1] == 'X' || p->format[p->fi - 1] == 'n')
	{
        p->f_hh = true;
        p->fi += 2;
    }
}

void	check_h(t_ptintf *p)
{
    if ('h' == p->format[p->fi] && (p->format[p->fi - 1] == 'd' 
				|| p->format[p->fi - 1] == 'i' || p->format[p->fi - 1] == 'o' || p->format[p->fi - 1] == 'u')
				|| p->format[p->fi - 1] == 'x' || p->format[p->fi - 1] == 'X' || p->format[p->fi - 1] == 'n')
    {
        p->f_h = true;
        ++p->fi;
    }
}

void	check_ll(t_ptintf *p)
{
    if (('l' == p->format[p->fi]) && ('l' == p->format[p->fi + 1]) && (p->format[p->fi - 1] == 'd' 
				|| p->format[p->fi - 1] == 'i' || p->format[p->fi - 1] == 'o' || p->format[p->fi - 1] == 'u')
				|| p->format[p->fi - 1] == 'x' || p->format[p->fi - 1] == 'X' || p->format[p->fi - 1] == 'n')
    {
        p->f_ll = true;
        p->fi += 2;
    }
}

void	check_l(t_ptintf *p)
{
    if ('l' == p->format[p->fi] && (p->format[p->fi - 1] == 'd' 
				|| p->format[p->fi - 1] == 'i' || p->format[p->fi - 1] == 'o' || p->format[p->fi - 1] == 'u')
				|| p->format[p->fi - 1] == 'x' || p->format[p->fi - 1] == 'X' || p->format[p->fi - 1] == 'n')
    {
        p->f_l = true;
        ++p->fi;
    }
}

void	check_largel(t_ptintf *p)
{
    if ('L' == p->format[p->fi] && (p->format[p->fi - 1] == 'e' 
				|| p->format[p->fi - 1] == 'E' || p->format[p->fi - 1] == 'f' || p->format[p->fi - 1] == 'g')
				|| p->format[p->fi - 1] == 'G')
    {
        p->f_largel = true;
        ++p->fi;
    }
}
