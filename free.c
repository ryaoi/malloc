/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:36:04 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/20 16:39:15 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/malloc.h"

extern t_map g_map;
extern pthread_mutex_t g_lock;

static void	link_large(void *large_ptr, void *header_ptr, int size, \
						int large_counter)
{
	while (large_counter)
	{
		if (next_block(large_ptr) == header_ptr)
		{
			size = ((((t_blockfooter *)\
					(large_ptr))->size + (g_map.page_size - 1))\
					& ~(g_map.page_size - 1));
			if (large_counter > 2)
			{
				((t_blockfooter *)\
				(large_ptr + size - sizeof(t_blockfooter)))->size = \
				(unsigned long long)next_block(next_block(large_ptr));
				break ;
			}
			else
			{
				((t_blockfooter *)\
				(large_ptr + size - sizeof(t_blockfooter)))->size = 0;
				break ;
			}
		}
		large_ptr = next_block(large_ptr);
		large_counter--;
	}
}

static void	free_large(void *ptr, void *header_ptr)
{
	void	*large_ptr;
	int		munmap_size;

	munmap_size = ((t_blockheader *)(header_ptr))->size;
	large_ptr = g_map.large;
	if (large_ptr == header_ptr && g_map.large_count > 1)
		g_map.large = next_block(g_map.large);
	else if (large_ptr == header_ptr && g_map.large_count == 1)
		g_map.large = NULL;
	else
		link_large(large_ptr, header_ptr, 0, g_map.large_count);
	if (munmap(header_ptr, munmap_size) != -1)
		g_map.large_count--;
}

void		free(void *ptr)
{
	void	*header_ptr;

	pthread_mutex_lock(&g_lock);
	if (ptr == NULL || safe_pointer(ptr) == 0)
	{
		pthread_mutex_unlock(&g_lock);
		return ;
	}
	header_ptr = ptr - sizeof(t_blockheader);
	((t_blockheader *)(header_ptr))->allocated = 0;
	if (((t_blockheader *)(header_ptr))->size <= SMALL)
		defragmentation(header_ptr);
	else
		free_large(ptr, header_ptr);
	pthread_mutex_unlock(&g_lock);
}
