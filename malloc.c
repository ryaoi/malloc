/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:00:13 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/20 14:24:34 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/malloc.h"

t_map			g_map = {NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0};
pthread_mutex_t g_lock;

static void	set_new_value(size_t new_size, char size_flag)
{
	if (size_flag == 1)
	{
		g_map.tiny_size -= (new_size + (size_t)OVERHEAD);
		g_map.extend_tiny += new_size + (size_t)OVERHEAD;
		g_map.tiny_count += 1;
	}
	else
	{
		g_map.small_size -= (new_size + (size_t)OVERHEAD);
		g_map.extend_small += new_size + (size_t)OVERHEAD;
		g_map.small_count += 1;
	}
}

void		*extend(size_t new_size, void *block_ptr, char size_flag)
{
	void	*ret_addr;

	if (((t_blockfooter *)(block_ptr - sizeof(t_blockfooter)))->filler != OVER)
	{
		ft_putstr_fd("Your program got an overflow...\n", 2);
		return (NULL);
	}
	ret_addr = block_ptr + sizeof(t_blockheader);
	((t_blockheader *)(block_ptr))->size = new_size;
	((t_blockheader *)(block_ptr))->allocated = 1;
	((t_blockfooter *)\
	(block_ptr + sizeof(t_blockheader) + new_size))->size = new_size;
	((t_blockfooter *)\
	(block_ptr + sizeof(t_blockheader) + new_size))->filler = OVER;
	set_new_value(new_size, size_flag);
	return (ret_addr);
}

void		*largalloc(size_t new_size)
{
	size_t	align;
	void	*ret_addr;

	align = (((new_size + OVERHEAD) + (g_map.page_size - 1))\
			& ~(g_map.page_size - 1));
	ret_addr = mmap(g_map.extend_large, align, FLAG_PROT, FLAG_MAP, -1, 0);
	if (ret_addr == MAP_FAILED)
		return (NULL);
	if (g_map.large != NULL)
		((t_blockfooter *)\
		(g_map.extend_large - sizeof(t_blockfooter)))->size = (size_t)ret_addr;
	g_map.extend_large = ret_addr;
	ret_addr = g_map.extend_large + sizeof(t_blockheader);
	((t_blockheader *)(g_map.extend_large))->size = new_size;
	((t_blockheader *)(g_map.extend_large))->allocated = 1;
	if (g_map.large == NULL)
		g_map.large = g_map.extend_large;
	g_map.extend_large = g_map.extend_large + align;
	g_map.large_count += 1;
	return (ret_addr);
}

void		*malloc(size_t size)
{
	void	*ret_ptr;

	pthread_mutex_lock(&g_lock);
	ret_ptr = NULL;
	if (g_map.page_size == 0)
	{
		if (mm_init() == -1)
			return (NULL);
	}
	if (size == 0)
		return (NULL);
	if ((ret_ptr = find_non_allocated_space(size)))
	{
		pthread_mutex_unlock(&g_lock);
		return (ret_ptr);
	}
	if (size <= TINY && g_map.small_size > size)
		ret_ptr = extend(size, g_map.extend_tiny, 1);
	else if (size <= SMALL && g_map.tiny_size > size)
		ret_ptr = extend(size, g_map.extend_small, 2);
	else
		ret_ptr = largalloc(size);
	pthread_mutex_unlock(&g_lock);
	return (ret_ptr);
}
