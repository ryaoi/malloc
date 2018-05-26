/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 16:04:11 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/26 16:27:10 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/malloc.h"

extern t_map g_map;
extern pthread_mutex_t g_lock;

void		ft_print_address(void *ptr, int newline)
{
	if (ptr == NULL)
		ft_putstr_fd("0x0\n", 1);
	else
	{
		ft_putstr_fd("0x", 1);
		ft_ulltoa_hex((unsigned long long)ptr);
		if (newline == 1)
			ft_putchar_fd('\n', 1);
	}
}
