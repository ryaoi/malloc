/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_non_allocated_space.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 14:04:40 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/19 14:12:30 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/malloc.h"

extern t_map g_map;

static void	set_variables(size_t size, size_t *counter, void **ptr)
{
	if (size <= TINY)
	{
		*ptr = g_map.tiny + OVERHEAD;
		*counter = g_map.tiny_count;
	}
	else if (size <= SMALL)
	{
		*ptr = g_map.small + OVERHEAD;
		*counter = g_map.small_count;
	}
	else
	{
		*ptr = g_map.large;
		*counter = g_map.large_count;
	}
}

void		*find_non_allocated_space(size_t size)
{
	size_t	counter;
	void	*ptr;

	set_variables(size, &counter, &ptr);
	while (counter)
	{
		if (size <= SMALL && ((t_blockfooter *)\
			(ptr - sizeof(t_blockheader)))->filler != OVER)
		{
			ft_putstr_fd("Your program got an overflow...\n", 2);
			return (NULL);
		}
		if (((t_blockheader *)(ptr))->allocated == 0 \
			&& (size == ((t_blockheader *)(ptr))->size \
			|| ((size < ((t_blockheader *)(ptr))->size - OVERHEAD * 2)\
			&& (size <= SMALL))))
		{
			create_block(ptr, size);
			return (ptr + sizeof(t_blockheader));
		}
		ptr = next_block(ptr);
		counter--;
	}
	return (NULL);
}
