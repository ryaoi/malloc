/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 21:05:49 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/19 13:15:00 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					ft_hexdump(void *ptr, size_t size)
{
	int					align;
	unsigned int		content;

	while (size > 0)
	{
		ft_putstr("[0x");
		ft_ulltoa_hex(((unsigned long long)(ptr)));
		ft_putstr("]\t");
		align = 16;
		while (align > 0 && size > 0)
		{
			content = *((unsigned char *)ptr);
			ft_ulltoa_hex(((unsigned long long)(content)));
			if (align != 1)
				ft_putstr(" ");
			else
				ft_putstr("\n");
			ptr += 1;
			align--;
			size--;
		}
	}
	ft_putstr("\n");
}
