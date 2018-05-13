/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 16:32:31 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/13 19:38:31 by ryaoi            ###   ########.fr       */
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
    char *test1 = ft_malloc(1000);
    printf("test1 address:%llx\n", test1);
    for(int i = 0;i < 400;i++)
        test1[i] = 'B';
    test1[20] = '\0';
    char *test2 = ft_malloc(20);
    printf("test1:[%s]\n", test1);
    printf("test2:[%s]\n", test2);
    // show_alloc_mem_ex();
    // // test1 = ft_realloc(test1, 30);
    // ft_malloc(500);
    // char *test3 = ft_malloc(120);
    // ft_free(test3);
    // char *test4 = ft_malloc(10);
    // // ft_free(test2);
    // // ft_free(test2);
    // ft_malloc(128);
    // ft_malloc(11);
    show_alloc_mem();
    show_alloc_mem_ex();
    return (0);
}