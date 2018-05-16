/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:36:04 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/13 19:37:23 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_map g_map;

void		ft_merge_double(void *header_ptr)
{
	void	*next_b;
	void	*prev_b;
	size_t	new_size;
	
	next_b = next_block(header_ptr);
	prev_b = prev_block(header_ptr);
	new_size = OVERHEAD*2 + \
	((t_blockheader *)(next_b))->size +((t_blockheader *)(header_ptr))->size;
	((t_blockheader *)(prev_b))->size += new_size;
	((t_blockfooter *)(next_b + ((t_blockheader *)(next_b))->size + \
	sizeof(t_blockheader)))->size = new_size;
}

void		ft_merge_next(void *header_ptr)
{
	void	*next_b;
	size_t	new_size;
	
	next_b = next_block(header_ptr);
	new_size = OVERHEAD + ((t_blockheader *)(next_b))->size;
	((t_blockheader *)(header_ptr))->size += new_size;
	((t_blockfooter *)(next_b + ((t_blockheader *)(next_b))->size + \
	sizeof(t_blockheader)))->size = new_size;
}

void		ft_merge_prev(void *header_ptr)
{
	void	*prev_b;
	size_t	new_size;
	
	prev_b = prev_block(header_ptr);
	new_size = OVERHEAD + ((t_blockheader *)(header_ptr))->size;
	((t_blockheader *)(prev_b))->size += new_size;
	((t_blockfooter *)(header_ptr + ((t_blockheader *)(header_ptr))->size + \
	sizeof(t_blockheader)))->size = new_size;
}

int			safe_pointer(void *ptr)
{
	size_t	counter;
	void	*ptr_malloc;


	ptr_malloc = g_map.tiny + OVERHEAD;
	counter = g_map.tiny_count;
	while(counter > 0)
	{
		if (ptr_malloc == ptr)
			return(1);
		ptr_malloc = next_block(ptr_malloc);
		counter--;
	}
	ptr = g_map.small + OVERHEAD;
	counter = g_map.small_count;
	while(counter > 0)
	{
		if (ptr_malloc == ptr)
			return(1);
		ptr_malloc = next_block(ptr_malloc);
		counter--;
	}
	ptr = g_map.large;
	counter = g_map.large_count;
	while(counter > 0)
	{
		if (ptr_malloc == ptr)
			return(1);
		ptr_malloc = next_block(ptr_malloc);
		counter--;
	}
	return (0);
}

void		free(void *ptr)
{
	void	*next_b;
	void	*prev_b;
	void	*header_ptr;

	if (ptr == NULL || safe_pointer(ptr) == 0)
		return ;
	header_ptr = ptr - sizeof(t_blockheader);
	((t_blockheader *)(header_ptr))->allocated = 0;
	next_b = next_block(header_ptr);
	prev_b = prev_block(header_ptr);
	if (((t_blockheader *)(prev_b))->allocated == 0 \
	&& ((t_blockheader *)(next_b))->allocated == 0)
		ft_merge_double(header_ptr);
	else if (((t_blockheader *)(prev_b))->allocated == 1 \
	&& ((t_blockheader *)(next_b))->allocated == 0 && ((t_blockheader *)(next_b))->size != 0)
		ft_merge_next(header_ptr);
	else if (((t_blockheader *)(prev_b))->allocated == 0 \
	&& ((t_blockheader *)(next_b))->allocated == 1  && ((t_blockheader *)(prev_b))->size != 0)
		ft_merge_prev(header_ptr);
}
