/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:26:06 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/19 13:12:23 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/malloc.h"

extern t_map g_map;
extern pthread_mutex_t g_lock;

static	void		ft_print_address(void *ptr, int newline)
{
	if (ptr == NULL)
		ft_putstr_fd("0\n", 1);
	else
	{
		ft_putstr_fd("0x", 1);
		ft_ulltoa_hex((unsigned long long)ptr);
		if (newline == 1)
			ft_putchar_fd('\n', 1);
	}
}

static void			ft_print_range(void *ptr, int ex)
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
		ft_print_address(ptr + ((t_blockheader *)\
		(ptr))->size + sizeof(t_blockheader), 0);
		ft_putstr_fd(" : ", 1);
		ft_putnbr(((t_blockheader *)(ptr))->size);
		ft_putstr_fd(" Bytes\n", 1);
	}
	if (ex)
		ft_hexdump(ptr + sizeof(t_blockheader), ((t_blockheader *)(ptr))->size);
}

static	void		ft_show_block(void *start_ptr, \
								int mode, size_t counter, int ex)
{
	void			*ptr;
	unsigned long	align;

	if (mode == 1)
		ptr = start_ptr + OVERHEAD;
	else
		ptr = start_ptr;
	while (counter > 0)
	{
		ft_print_range(ptr, ex);
		ptr = next_block(ptr);
		counter--;
	}
}

void				show_alloc_mem(void)
{
	pthread_mutex_lock(&g_lock);
	ft_putstr_fd("TINY : 0x", 1);
	ft_print_address(g_map.tiny, 1);
	ft_show_block(g_map.tiny, 1, g_map.tiny_count, 0);
	ft_putstr_fd("SMALL : 0x", 1);
	ft_print_address(g_map.small, 1);
	ft_show_block(g_map.small, 1, g_map.small_count, 0);
	ft_putstr_fd("LARGE : 0x", 1);
	ft_print_address(g_map.large, 1);
	ft_show_block(g_map.large, 2, g_map.large_count, 0);
	pthread_mutex_unlock(&g_lock);
}

void				show_alloc_mem_ex(void)
{
	pthread_mutex_lock(&g_lock);
	ft_putstr_fd("TINY : 0x", 1);
	ft_print_address(g_map.tiny, 1);
	ft_show_block(g_map.tiny, 1, g_map.tiny_count, 1);
	ft_putstr_fd("SMALL : 0x", 1);
	ft_print_address(g_map.small, 1);
	ft_show_block(g_map.small, 1, g_map.small_count, 1);
	ft_putstr_fd("LARGE : 0x", 1);
	ft_print_address(g_map.large, 1);
	ft_show_block(g_map.large, 2, g_map.large_count, 1);
	pthread_mutex_unlock(&g_lock);
}
