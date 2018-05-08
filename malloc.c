/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:00:13 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/08 21:30:10 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_map 		g_map = {NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0}; 

int mm_init()
{
    size_t page_size;

    page_size = getpagesize();
    g_map.page_size = page_size;
    g_map.tiny = mmap(0, TINY*OVERHEAD*page_size,FLAG_PROT, FLAG_MAP,-1, 0);
    g_map.small = mmap(0, SMALL*OVERHEAD*page_size,FLAG_PROT, FLAG_MAP,-1, 0);
    if (g_map.small == MAP_FAILED || g_map.tiny == MAP_FAILED)
        return (-1);
    printf("map.tiny:%p\n", g_map.tiny);
    printf("map.small:%p\n", g_map.small);
    ((t_blockheader *)(g_map.tiny))->size = 0;
    ((t_blockheader *)(g_map.tiny))->allocated = 1;
    ((t_blockfooter *)(g_map.tiny + sizeof(t_blockheader)))->size = 0;
    ((t_blockheader *)(g_map.small))->size = 0;
    ((t_blockheader *)(g_map.small))->allocated = 1;
    ((t_blockfooter *)(g_map.small + sizeof(t_blockheader)))->size = 0;
    printf("finished initializing the head!\n");
    g_map.tiny_size = TINY*OVERHEAD*page_size - OVERHEAD;
    g_map.small_size = SMALL*OVERHEAD*page_size - OVERHEAD;
    g_map.extend_tiny = sizeof(t_blockheader) + &g_map.tiny;
    g_map.extend_small = sizeof(t_blockheader) + &g_map.small;
    printf("TINY:size:%zu\tallocated:%hhd\tfooter:%zu\n", ((t_blockheader*)(g_map.tiny))->size, \
    ((t_blockheader*)(g_map.tiny))->allocated, ((t_blockfooter*)(g_map.tiny + sizeof(t_blockheader)))->size);
    printf("SMALL:size:%zu\tallocated:%hhd\tfooter:%zu\n", ((t_blockheader*)(g_map.small))->size, \
    ((t_blockheader*)(g_map.small))->allocated, ((t_blockfooter*)(g_map.tiny + sizeof(t_blockheader)))->size);
    printf("tiny was :%zu il reste:%zu\n", TINY*OVERHEAD*page_size, g_map.tiny_size);
    printf("small was :%zu il reste:%zu\n", SMALL*OVERHEAD*page_size, g_map.small_size);
    return (0);
}

void		*extend(size_t new_size, void *block_ptr, char size)
{
	void	*ret_addr;

	ret_addr = block_ptr;
	((t_blockheader *)(block_ptr))->size = new_size;
    ((t_blockheader *)(block_ptr))->allocated = 1;
    ((t_blockfooter *)(block_ptr + sizeof(t_blockheader) + new_size))->size = new_size;
    if (size == 1)
    {
		    printf("[TINY/%p]:size:%zu\tallocated:%hhd\tfooter:%zu\n", block_ptr, ((t_blockheader*)(block_ptr))->size, \
    ((t_blockheader*)(block_ptr))->allocated, ((t_blockfooter *)(block_ptr + new_size + sizeof(t_blockheader)))->size);
        g_map.tiny_size -= (new_size + (size_t)OVERHEAD);
        g_map.extend_tiny = (&g_map.extend_tiny + new_size + (size_t)OVERHEAD);
		// printf("new place:%llu\n", g_map.extend_tiny);
		g_map.tiny_count += 1;
    }
    else
    {
		printf("[SMALL/%p]:size:%zu\tallocated:%hhd\tfooter:%zu\n", block_ptr, ((t_blockheader*)(block_ptr))->size, \
    ((t_blockheader*)(block_ptr))->allocated, ((t_blockfooter *)(block_ptr + new_size + sizeof(t_blockheader)))->size);
        g_map.small_size -= (new_size + (size_t)OVERHEAD);
        g_map.extend_small = (&g_map.extend_small + new_size + (size_t)OVERHEAD);
		// printf("new place:%llu\n", g_map.extend_small);
		g_map.small_count += 1;
    }
    return (ret_addr);
}

void        *largalloc(size_t new_size)
{
	size_t	align;
	void	*ret_addr;

	align = (((new_size + OVERHEAD) + (g_map.page_size - 1)) & ~ (g_map.page_size - 1));
	printf("align?:%d\n", align);
	if (g_map.large == NULL)
	{
		g_map.large = mmap(0, align, FLAG_PROT, FLAG_MAP,-1, 0);
		printf("map.large:%p\n", g_map.large);
		if (g_map.large == MAP_FAILED)
			return(NULL);
		ret_addr = g_map.large + sizeof(t_blockheader);
		((t_blockheader *)(g_map.large))->size = new_size;
		((t_blockheader *)(g_map.large))->allocated = 1;
		((t_blockfooter *)(g_map.large + align - sizeof(t_blockfooter)))->size = align;
		printf("[ADDD]:size:%zu\tallocated:%hhd\tfooter:%zu\n", ((t_blockheader*)(g_map.large))->size, \
		((t_blockheader*)(g_map.large))->allocated, ((t_blockfooter*)(g_map.large + align - sizeof(t_blockfooter)))->size);
		g_map.extend_large = &g_map.large + align;
	}
	else
	{
		g_map.extend_large = mmap(g_map.extend_large, align, FLAG_PROT, FLAG_MAP,-1, 0);
		printf("map.large:%p\n", g_map.extend_large);
		if (g_map.extend_large == MAP_FAILED)
			return(NULL);
		ret_addr = g_map.extend_large + sizeof(t_blockheader);
		((t_blockheader *)(g_map.extend_large))->size = new_size;
		((t_blockheader *)(g_map.extend_large))->allocated = 1;
		((t_blockfooter *)(g_map.extend_large + align - sizeof(t_blockfooter)))->size = align;
		printf("[ADDD]:size:%zu\tallocated:%hhd\tfooter:%zu\n", ((t_blockheader*)(g_map.extend_large))->size, \
		((t_blockheader*)(g_map.extend_large))->allocated, ((t_blockfooter*)(g_map.extend_large + align - sizeof(t_blockfooter)))->size);
		printf("check upper footer!:%zu\n", ((t_blockfooter*)(g_map.extend_large - sizeof(t_blockfooter)))->size);
		g_map.extend_large = &g_map.extend_large + align;
	}
	g_map.large_count += 1;
	return (ret_addr);
}
void		*ft_malloc(size_t size)
{
	if (g_map.page_size == 0)
    {
		if (mm_init() == -1)
			return (NULL);
    }
	if (size <= TINY && g_map.small_size > size)
        return((void *)extend(size, g_map.extend_tiny, 1));
    else if (size <= SMALL && g_map.tiny_size > size)
        return((void *)extend(size, g_map.extend_small, 2));
    else
        return(largalloc(size));
}