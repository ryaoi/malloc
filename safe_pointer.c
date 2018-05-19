/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_pointer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 13:20:45 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/19 14:10:54 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/malloc.h"

extern t_map g_map;

static int	pointer_check(int counter, void *ptr_malloc, void *ptr)
{
	while (counter > 0)
	{
		if (ptr_malloc + sizeof(t_blockheader) == ptr)
			return (1);
		ptr_malloc = next_block(ptr_malloc);
		counter--;
	}
	return (0);
}

int			safe_pointer(void *ptr)
{
	size_t	counter;
	void	*ptr_malloc;

	ptr_malloc = g_map.tiny + OVERHEAD;
	counter = g_map.tiny_count;
	if (pointer_check(counter, ptr_malloc, ptr))
		return (1);
	ptr_malloc = g_map.small + OVERHEAD;
	counter = g_map.small_count;
	if (pointer_check(counter, ptr_malloc, ptr))
		return (1);
	ptr_malloc = g_map.large;
	counter = g_map.large_count;
	if (pointer_check(counter, ptr_malloc, ptr))
		return (1);
	return (0);
}
