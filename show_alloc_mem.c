/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:26:06 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/13 19:05:00 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_map g_map;

static void ft_print_address(void *ptr, int newline)
{
	if (ptr == NULL)
		ft_putstr_fd("0\n", 1);
	else
	{
		ft_ulltoa_hex((unsigned long long)ptr);
		if (newline == 1)
			ft_putchar_fd('\n', 1);
	}
}
static void	ft_print_range(void *ptr, int ex)
{
	if (ex)
	{
		if (((t_blockheader *)(ptr))->allocated == 1)
			ft_putstr_fd("[USED]", 1);
		else
			ft_putstr_fd("[FREE]", 1);
	}
	if (ex == 1 || ((t_blockheader *)(ptr))->allocated == 1)
	{
		ft_print_address(ptr + sizeof(t_blockheader), 0);
		ft_putstr_fd(" - ", 1);
		ft_print_address(ptr + ((t_blockheader *)(ptr))->size + sizeof(t_blockheader), 0);
		ft_putstr_fd(" : ", 1);
		ft_putnbr(((t_blockheader *)(ptr))->size);
		ft_putstr_fd(" Bytes\n", 1);	
	}
	if (ex)
		ft_hexdump(ptr + sizeof(t_blockheader), ((t_blockheader *)(ptr))->size);
}
static void ft_show_block(void *start_ptr, int mode, size_t counter, int ex)
{
	void 	*ptr;
	size_t	align;

	if (mode == 1)
		ptr = start_ptr + OVERHEAD;
	else
		ptr = start_ptr;
	while (counter > 0)
	{
		ft_print_range(ptr, ex);
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

void 		show_alloc_mem()
{
	ft_putstr_fd("TINY : 0x", 1);
	ft_print_address(g_map.tiny, 1);
	ft_show_block(g_map.tiny, 1, g_map.tiny_count, 0);
	ft_putstr_fd("SMALL : 0x", 1);
	ft_print_address(g_map.small, 1);
	ft_show_block(g_map.small, 1, g_map.small_count, 0);
	ft_putstr_fd("LARGE : 0x", 1);
	ft_print_address(g_map.large, 1);
	ft_show_block(g_map.large, 2, g_map.large_count, 0);
}

void		show_alloc_mem_ex()
{
	ft_putstr_fd("TINY : 0x", 1);
	ft_print_address(g_map.tiny, 1);
	ft_show_block(g_map.tiny, 1, g_map.tiny_count, 1);
	ft_putstr_fd("SMALL : 0x", 1);
	ft_print_address(g_map.small, 1);
	ft_show_block(g_map.small, 1, g_map.small_count, 1);
	ft_putstr_fd("LARGE : 0x", 1);
	ft_print_address(g_map.large, 1);
	ft_show_block(g_map.large, 2, g_map.large_count, 1);
}