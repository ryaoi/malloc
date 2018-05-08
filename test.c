/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 16:32:31 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/08 21:13:12 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>  
#include <unistd.h>

extern t_map g_map;

int main()
{   
    int test = 0;

    printf("---------------------\n");
    test = 1;
    printf("map.tiny:%p\n", g_map.tiny);
    printf("map.small:%p\n", g_map.small);
	printf("map.tiny_size:%d\n", g_map.tiny_size);
    printf("map.small_size:%d\n", g_map.small_size);
    printf("---------------------\n");
    ft_malloc(10);
    ft_malloc(20);
    ft_malloc(30);
    ft_malloc(40);
    ft_malloc(50);
    ft_malloc(60);
    ft_malloc(140);

    ft_malloc(8000);
    ft_malloc(10000);
    ft_malloc(16000);
    show_alloc_mem();
    return (0);
}