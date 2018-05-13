/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:00:13 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/13 19:39:08 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_map 			g_map = {NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0};
pthread_mutex_t lock;

void		*extend(size_t new_size, void *block_ptr, char size_flag)
{
	void	*ret_addr;

	if (((t_blockfooter *)(block_ptr - sizeof(t_blockfooter)))->filler != OVER)
	{
		ft_putstr_fd("Your program got an overflow...\n", 2);
		return(NULL);
	}
	else
		printf("euh:%d - MAIGC:%d\n", ((t_blockfooter *)(block_ptr - sizeof(t_blockfooter)))->filler, OVER);
	ret_addr = block_ptr + sizeof(t_blockheader);
	((t_blockheader *)(block_ptr))->size = new_size;
    ((t_blockheader *)(block_ptr))->allocated = 1;
    ((t_blockfooter *)(block_ptr + sizeof(t_blockheader) + new_size))->size = new_size;
	((t_blockfooter *)(block_ptr + sizeof(t_blockheader) + new_size))->filler = OVER;
    if (size_flag == 1)
    {
		    // printf("[TINY/%llx]:size:%zu\tallocated:%hhd\tfooter:%zu\n", block_ptr, ((t_blockheader*)(block_ptr))->size, \
    ((t_blockheader*)(block_ptr))->allocated, ((t_blockfooter *)(block_ptr + new_size + sizeof(t_blockheader)))->size);
        g_map.tiny_size -= (new_size + (size_t)OVERHEAD);
        // printf("new place:%llx\n", new_size + (size_t)OVERHEAD);
        g_map.extend_tiny += new_size + (size_t)OVERHEAD;
		g_map.tiny_count += 1;
    }
    else
    {
		// printf("[SMALL/%llx]:size:%zu\tallocated:%hhd\tfooter:%zu\n", block_ptr, ((t_blockheader*)(block_ptr))->size, \
    ((t_blockheader*)(block_ptr))->allocated, ((t_blockfooter *)(block_ptr + new_size + sizeof(t_blockheader)))->size);
        g_map.small_size -= (new_size + (size_t)OVERHEAD);
        // printf("new place:%llx\n", g_map.extend_tiny - new_size + (size_t)OVERHEAD);
        g_map.extend_small += new_size + (size_t)OVERHEAD;
		// printf("new place:%llu\n", g_map.extend_small);
		g_map.small_count += 1;
    }
	printf("ret_addr:%llx\n", ret_addr);
    return (ret_addr);
}

void        *largalloc(size_t new_size)
{
	size_t	align;
	void	*ret_addr;

	align = (((new_size + OVERHEAD) + (g_map.page_size - 1)) & ~ (g_map.page_size - 1));
	if (g_map.large == NULL)
	{
		g_map.large = mmap(0, align, FLAG_PROT, FLAG_MAP,-1, 0);
		if (g_map.large == MAP_FAILED)
			return(NULL);
		ret_addr = g_map.large + sizeof(t_blockheader);
		((t_blockheader *)(g_map.large))->size = new_size;
		((t_blockheader *)(g_map.large))->allocated = 1;
		((t_blockfooter *)(g_map.large + align - sizeof(t_blockfooter)))->size = align;
		printf("[ADDD]:size:%zu\tallocated:%hhd\tfooter:%zu\n", ((t_blockheader*)(g_map.large))->size, \
		((t_blockheader*)(g_map.large))->allocated, ((t_blockfooter*)(g_map.large + align - sizeof(t_blockfooter)))->size);
		g_map.extend_large = g_map.large + align;
	}
	else
	{
		g_map.extend_large = mmap(g_map.extend_large, align, FLAG_PROT, FLAG_MAP,-1, 0);
		// printf("map.large:%llx\n", g_map.extend_large);
		if (g_map.extend_large == MAP_FAILED)
			return(NULL);
		ret_addr = g_map.extend_large + sizeof(t_blockheader);
		((t_blockheader *)(g_map.extend_large))->size = new_size;
		((t_blockheader *)(g_map.extend_large))->allocated = 1;
		((t_blockfooter *)(g_map.extend_large + align - sizeof(t_blockfooter)))->size = align;
		printf("[ADDD]:size:%zu\tallocated:%hhd\tfooter:%zu\n", ((t_blockheader*)(g_map.extend_large))->size, \
		((t_blockheader*)(g_map.extend_large))->allocated, ((t_blockfooter*)(g_map.extend_large + align - sizeof(t_blockfooter)))->size);
		// printf("check upper footer!:%zu\n", ((t_blockfooter*)(g_map.extend_large - sizeof(t_blockfooter)))->size);
		g_map.extend_large = g_map.extend_large + align;
	}
	g_map.large_count += 1;
	return (ret_addr);
}

void		*find_non_allocated_space(size_t size)
{
	size_t	counter;
	void	*ptr;

	if (size <= TINY)
	{
		ptr = g_map.tiny + OVERHEAD;
		counter = g_map.tiny_count;
	}
	else if (size <= SMALL)
	{
		ptr = g_map.small + OVERHEAD;
		counter = g_map.small_count;
	}
	else
	{
		ptr = g_map.large;
		counter = g_map.large_count;
	}
	while (counter)
	{
		if (((t_blockfooter *)(ptr - sizeof(t_blockheader)))->filler != OVER)
		{
			ft_putstr_fd("Your program got an overflow...\n", 2);
			return(NULL);
		}
		if (((t_blockheader *)(ptr))->allocated == 0 \
			&& (size == ((t_blockheader *)(ptr))->size \
			|| (size < ((t_blockheader *)(ptr))->size - OVERHEAD*2)))
		{
			create_block(ptr, size);
			return (ptr + sizeof(t_blockheader));
		}
		ptr = next_block(ptr);
		counter--;
	}
	return(NULL);
}


void		*ft_malloc(size_t size)
{
	void	*ret_ptr;

	pthread_mutex_lock(&lock);
	ret_ptr = NULL;
	if (g_map.page_size == 0)
    {
		if (mm_init() == -1)
			return (NULL);
    }
    if ((ret_ptr = find_non_allocated_space(size)))
	{
		pthread_mutex_unlock(&lock);
        return(ret_ptr);
	}
	if (size <= TINY && g_map.small_size > size)
        ret_ptr = extend(size, g_map.extend_tiny, 1);
    else if (size <= SMALL && g_map.tiny_size > size)
        ret_ptr = extend(size, g_map.extend_small, 2);
    else
        ret_ptr = largalloc(size);
	pthread_mutex_unlock(&lock);
	return (ret_ptr);	
}