/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:26:06 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/11 18:22:10 by ryaoi            ###   ########.fr       */
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
	void 	*ptr;
	size_t	align;

	if (mode == 1)
		ptr = start_ptr + OVERHEAD; // cest pour sauter le 0 (le debut de malloc)
	else
		ptr = start_ptr;
	while (counter > 0)
	{
		if (((t_blockheader *)(ptr))->allocated == 1)
		{
			ft_print_address(ptr + sizeof(t_blockheader), 0);
			ft_putstr_fd(" - ", 1);
			ft_print_address(ptr + ((t_blockheader *)(ptr))->size + sizeof(t_blockheader), 0);
			ft_putstr(" : ");
			ft_putnbr(((t_blockheader *)(ptr))->size);
			ft_putstr(" Bytes\n");
		}
		if (mode == 1)
			ptr += ((t_blockheader *)(ptr))->size + OVERHEAD;
		else
		{
			align = (((((t_blockheader *)(ptr))->size + OVERHEAD)\
				+ (g_map.page_size - 1)) & ~ (g_map.page_size - 1));
			ptr += align;
		}
		counter--;
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
	ft_show_block(g_map.large, 2, g_map.large_count);
}