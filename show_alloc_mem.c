/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:26:06 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/08 21:31:20 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_map g_map;

static void ft_print_address(void *ptr, int newline)
{
	if (ptr == NULL)
		ft_putstr("0x0\n");
	else
	{
		ft_ulltoa_hex((unsigned long long)ptr);
		if (newline == 1)
			ft_putchar('\n');
	}
}

static void ft_show_block(void *start_ptr, int mode, size_t counter)
{
	void *ptr;
	
	ptr = start_ptr;
	if (mode == 1)
	{
		while (counter > 0)
		{
			ft_print_address(ptr + sizeof(t_blockheader), 0);
			ft_putstr_fd(" - ", 1);
			ft_print_address(ptr + sizeof(t_blockheader) + ((t_blockheader *)(ptr))->size, 0);
			ft_putstr(" : ");
			ft_putnbr(((t_blockheader *)(ptr))->size);
			ft_putstr(" Bytes\n");
			ptr += ((t_blockheader *)(ptr))->size + OVERHEAD;
			counter--;
		}
	}
}

void show_alloc_mem()
{
	ft_putstr("TINY : ");
	ft_print_address(g_map.tiny, 1);
	ft_show_block(g_map.tiny, 1, g_map.tiny_count);
	ft_putstr("SMALL : ");
	ft_print_address(g_map.small, 1);
	ft_show_block(g_map.small, 1, g_map.small_count);
	ft_putstr("LARGE : ");
	ft_print_address(g_map.large, 1);
}