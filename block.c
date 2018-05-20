/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:12:55 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/20 16:40:02 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/malloc.h"

extern t_map g_map;

int			mm_init(void)
{
	size_t	page_size;

	page_size = getpagesize();
	g_map.page_size = page_size;
	g_map.tiny = mmap(0, TINY * OVERHEAD * page_size, \
					FLAG_PROT, FLAG_MAP, -1, 0);
	g_map.small = mmap(0, SMALL * OVERHEAD * page_size, \
					FLAG_PROT, FLAG_MAP, -1, 0);
	if (g_map.small == MAP_FAILED || g_map.tiny == MAP_FAILED)
		return (-1);
	((t_blockheader *)(g_map.tiny))->size = 0;
	((t_blockheader *)(g_map.tiny))->allocated = 1;
	((t_blockfooter *)(g_map.tiny + sizeof(t_blockheader)))->size = 0;
	((t_blockfooter *)(g_map.tiny + sizeof(t_blockheader)))->filler = OVER;
	((t_blockheader *)(g_map.small))->size = 0;
	((t_blockheader *)(g_map.small))->allocated = 1;
	((t_blockfooter *)(g_map.small + sizeof(t_blockheader)))->size = 0;
	((t_blockfooter *)(g_map.small + sizeof(t_blockheader)))->filler = OVER;
	g_map.tiny_size = TINY * OVERHEAD * page_size - OVERHEAD;
	g_map.small_size = SMALL * OVERHEAD * page_size - OVERHEAD;
	g_map.extend_tiny = OVERHEAD + g_map.tiny;
	g_map.extend_small = OVERHEAD + g_map.small;
	return (0);
}

void		*next_block(void *ptr)
{
	size_t	get_size;

	get_size = ((t_blockheader *)(ptr))->size;
	if (get_size > SMALL)
	{
		get_size = (((get_size + OVERHEAD)\
				+ (g_map.page_size - 1)) & ~(g_map.page_size - 1));
		return ((void *)(((t_blockfooter *)\
		(ptr + get_size - sizeof(t_blockfooter)))->size));
	}
	return (ptr + get_size + OVERHEAD);
}

void		*prev_block(void *ptr)
{
	size_t	get_size;

	get_size = ((t_blockfooter *)(ptr - sizeof(t_blockfooter)))->size;
	if (get_size > SMALL)
	{
		return (ptr - get_size);
	}
	return (ptr - (get_size + OVERHEAD));
}

void		create_block(void *ptr, size_t size)
{
	size_t	old_size;
	size_t	left_size;

	old_size = ((t_blockheader *)(ptr))->size;
	left_size = old_size - size - OVERHEAD;
	((t_blockheader *)(ptr))->size = size;
	((t_blockheader *)(ptr))->allocated = 1;
	((t_blockfooter *)(ptr + sizeof(t_blockheader) + size))->size = size;
	((t_blockfooter *)(ptr + sizeof(t_blockheader) + size))->filler = OVER;
	if (old_size != size)
	{
		((t_blockheader *)(ptr + OVERHEAD + size))->size = left_size;
		((t_blockheader *)(ptr + OVERHEAD + size))->allocated = 0;
		((t_blockfooter *)\
		(ptr + OVERHEAD + size + left_size))->size = left_size;
		if (size <= TINY)
			g_map.tiny_count += 1;
		else if (size <= SMALL)
			g_map.small_count += 1;
		else
			g_map.large_count += 1;
	}
}
