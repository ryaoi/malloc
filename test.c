/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 16:32:31 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/12 18:57:34 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>  
#include <unistd.h>
#include <stdlib.h>

// extern t_map g_map;

int main()
{   
    char *test = NULL;
    char *test1 = ft_malloc(84);
    printf("test1 address:%llx\n", test1);
    for(int i = 0;i < 9;i++)
        test1[i] = 'A';
    test1[9] = '\0';
    char *test2 = ft_malloc(20);

    show_alloc_mem_ex();
    // test1 = ft_realloc(test1, 30);
    ft_malloc(50);
    char *test3 = ft_malloc(120);
    ft_free(test3);
    char *test4 = ft_malloc(10);
    // ft_free(test2);
    // ft_free(test2);
    ft_malloc(128);
    ft_malloc(11);
    show_alloc_mem();
    show_alloc_mem_ex();
    return (0);
}