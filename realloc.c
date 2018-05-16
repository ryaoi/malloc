/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 17:16:01 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/12 19:42:21 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/malloc.h"

extern	t_map			g_map;
extern	pthread_mutex_t	lock;

void					*realloc(void *ptr, size_t size)
{
	void				*header_ptr;
	void				*ret_ptr;

	// pthread_mutex_lock(&lock);
	// ft_putstr_fd("[REALLOC]entered\n", 1);
	// ft_putstr_fd("[REALLOC]size:0x", 1);
	// ft_ulltoa_hex(size);
	// ft_putstr_fd("\n[REALLOC]ptr:", 1);
	// ft_ulltoa_hex((unsigned long long)ptr);
	// ft_putstr_fd("\n", 1);
	if (g_map.page_size == 0)
	{
		if (mm_init() == -1)
			return (NULL);
	}
	if (ptr == NULL)
		return (malloc(size));
	if (safe_pointer(ptr) == 0)
		return (NULL);
	header_ptr = ptr - sizeof(t_blockheader);
	((t_blockheader *)(header_ptr))->allocated = 0;
	if ((ret_ptr = find_non_allocated_space(size)))
	{
		// pthread_mutex_unlock(&lock);
		ft_memcpy(ret_ptr, ptr, ((t_blockheader *)(header_ptr))->size);
		return (ret_ptr);
	}
	if (size <= TINY && g_map.small_size > size)
		ret_ptr = (void *)extend(size, g_map.extend_tiny, 1);
	else if (size <= SMALL && g_map.tiny_size > size)
		ret_ptr = (void *)extend(size, g_map.extend_small, 2);
	else
		ret_ptr = (void *)largalloc(size);
	ret_ptr = ft_memcpy(ret_ptr, ptr, ((t_blockheader *)(header_ptr))->size);
	// pthread_mutex_unlock(&lock);
	return (ret_ptr);
}
