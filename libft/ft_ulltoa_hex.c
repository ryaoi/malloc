/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 17:04:38 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/08 16:56:01 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int				count_digit(unsigned long long nbr, int base)
{
	int					i;
	unsigned long long	copy;
	unsigned long long	base1;

	base1 = base;
	i = 1;
	copy = nbr;
	while (copy > base1 - 1)
	{
		i++;
		copy /= base1;
	}
	return (i);
}

#include <stdio.h>

void					ft_ulltoa_hex(unsigned long long nbr)
{
	int					size;
	char				*array;
	char				ret[30];

	array = "0123456789ABCDEF";
	size = count_digit(nbr, 16);
	ft_bzero(ret, 30);
	while (size > 0)
	{
		ret[size - 1] = array[nbr % 16];
		nbr /= 16;
		size--;
	}
	ft_putstr("0x");
	ft_putstr(ret);
}
