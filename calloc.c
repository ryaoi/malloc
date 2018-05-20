/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 14:50:38 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/20 15:01:09 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/malloc.h"

extern t_map g_map;
extern pthread_mutex_t g_lock;

void		*calloc(size_t count, size_t size)
{
	void	*ret_ptr;

	pthread_mutex_lock(&g_lock);
	ret_ptr = NULL;
	if (g_map.page_size == 0)
	{
		if (mm_init() == -1)
		{
			pthread_mutex_unlock(&g_lock);
			return (NULL);
		}
	}
	pthread_mutex_unlock(&g_lock);
	ret_ptr = malloc(count * size);
	pthread_mutex_lock(&g_lock);
	if (ret_ptr != NULL)
		ft_bzero(ret_ptr, count * size);
	pthread_mutex_unlock(&g_lock);
	return (ret_ptr);
}
