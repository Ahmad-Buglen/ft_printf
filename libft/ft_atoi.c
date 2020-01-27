/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 11:55:05 by dphyliss          #+#    #+#             */
/*   Updated: 2019/05/04 12:07:47 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	while ((*str == ' ') || (*str == '\n') || (*str == '\t')
			|| (*str == '\f') || (*str == '\r') || (*str == '\v'))
		++str;
	sign = (*str == '-') ? -1 : 1;
	((*str == '-') || (*str == '+')) ? ++str : 0;
	while ((*str >= '0') && (*str <= '9'))
	{
		if (((n * 10) / 10) != n)
			return ((sign == -1) ? 0 : -1);
		n = 10 * n + (*str - '0');
		++str;
	}
	n = (-1 == sign) ? -n : n;
	return (n);
}