/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:11:01 by dphyliss          #+#    #+#             */
/*   Updated: 2019/04/25 14:30:08 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr(int n)
{
	char	*s;
	int		sign;
	char	mas[12];

	s = &mas[11];
	if (n == 0)
		ft_putstr("0");
	else if (n == -2147483648)
		ft_putstr("-2147483648");
	else
	{
		*s = '\0';
		sign = (n < 0) ? 1 : 0;
		n = (n < 0) ? -n : n;
		while (n)
		{
			*(--s) = ('0' + (n % 10));
			n /= 10;
		}
		(sign == 1) ? *(--s) = '-' : 0;
		ft_putstr(s);
	}
}
