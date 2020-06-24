/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dphyliss <dphyliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 13:41:06 by dphyliss          #+#    #+#             */
/*   Updated: 2020/06/24 16:46:33 by dphyliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			print_per(t_printf *const p)
{
	char		buf;
	int			width;

	buf = p->f_zero && !p->f_minus ? '0' : ' ';
	width = p->f_width ? p->width - 1 : 0;
	width = (width < 0) ? 0 : width;
	while (!p->f_minus && (width-- > 0))
		p->temp[p->ti++] = buf;
	p->temp[p->ti++] = '%';
	while (p->f_minus && (width-- > 0))
		p->temp[p->ti++] = buf;
	data_record(p);
}

void			print_c(t_printf *const p, const char c)
{
	char		buf;
	int			width;

	buf = p->f_zero && !p->f_minus ? '0' : ' ';
	width = p->f_width ? p->width - 1 : 0;
	width = width < 0 ? 0 : width;
	while (!p->f_minus && (width-- > 0))
		p->temp[p->ti++] = buf;
	p->temp[p->ti++] = c;
	while (p->f_minus && (width-- > 0))
		p->temp[p->ti++] = buf;
	data_record(p);
}

void			print_r(t_printf *const p, const char c)
{
	char		buf;
	int			width;
	const char	*mas[33] = {"nul", "soh", "stx", "etx", "eot", "enq", "ack",
					"bel", "bs", "ht", "nl", "vt", "np", "cr", "so", "si",
					"dle", "dc1", "dc2", "dc3", "dc4", "nak", "syn", "etb",
					"can", "em", "sub", "esc", "fs", "gs", "rs", "us", "sp"};

	buf = p->f_zero && !p->f_minus ? '0' : ' ';
	width = p->f_width ? p->width - 1 : 0;
	width = width < 0 ? 0 : width;
	while (!p->f_minus && (width-- > 0))
		p->temp[p->ti++] = buf;
	if (c >= 0 && c <= 32)
	{
		ft_strncpy(p->temp + p->ti, (char *)mas + c,
							ft_strlen((char *)mas + c));
		p->ti += ft_strlen((char *)mas + c);
	}
	while (p->f_minus && (width-- > 0))
		p->temp[p->ti++] = buf;
	data_record(p);
}

void			print_s(t_printf *const p, char const *str)
{
	int			length;
	int			space;

	if (NULL == str)
		str = "(null)";
	length = ft_strlen(str);
	length = p->f_prec && p->prec < length ? p->prec : length;
	space = p->f_width ? p->width - length : 0;
	space = space < 0 ? 0 : space;
	while (!p->f_minus && (space-- > 0))
		p->temp[p->ti++] = ' ';
	if (BUFF > length + p->ti)
	{
		ft_strncpy(p->temp + p->ti, str, length);
		p->ti += length;
	}
	else
	{
		data_release(p);
		write(1, str, length);
		p->print_size += length;
	}
	while (p->f_minus && (space-- > 0))
		p->temp[p->ti++] = ' ';
	data_record(p);
}
