/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:12:55 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/11 16:53:20 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <stdio.h>

extern t_map g_map;

void		*next_block(void *ptr)
{
	size_t	get_size;
	
	get_size = ((t_blockheader *)(ptr))->size;
	// printf("[this_block]size:%d\t", get_size);
	if (get_size > SMALL)
	{
		get_size = (((get_size + OVERHEAD)\
				+ (g_map.page_size - 1)) & ~ (g_map.page_size - 1));
		return (ptr + get_size);
	}
	// printf("[next_block]size:%d\n", ((t_blockheader *)(ptr + get_size + OVERHEAD))->size);
	return (ptr + get_size + OVERHEAD);
}

void		*prev_block(void *ptr)
{
	size_t 	get_size;

	get_size = ((t_blockheader *)(ptr - sizeof(t_blockfooter)))->size;
	// printf("[this_block]size:%d\t", get_size);
	if (get_size > SMALL)
	{
		return (ptr - get_size);
	}
	// printf("[prev_block]size:%d\n", ((t_blockheader *)(ptr - get_size - OVERHEAD))->size);
	return (ptr - (get_size + OVERHEAD));
}

void		create_block(void *ptr, size_t size)
{
	size_t	old_size;
	size_t	left_size;
	
	old_size = ((t_blockheader *)(ptr))->size;
	left_size = old_size - size - OVERHEAD;
	printf("old_size:%zu\tsize:%zu\tOVERHEAD:%zu\n", old_size, size, OVERHEAD);
	printf("old_size:%zu -> new_size:%zu\n", old_size, left_size);
	((t_blockheader *)(ptr))->size = size;
	((t_blockheader *)(ptr))->allocated = 1;
	((t_blockfooter *)(ptr + sizeof(t_blockheader) + size))->size = size;
	if (old_size - size != 0)
	{
		((t_blockheader *)(ptr + OVERHEAD + size))->size = left_size;
		((t_blockheader *)(ptr + OVERHEAD + size))->allocated = 0;
		((t_blockfooter *)(ptr + OVERHEAD + size + left_size))->size = left_size;
	}
		
}