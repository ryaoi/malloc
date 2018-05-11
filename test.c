/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 16:32:31 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/11 19:03:25 by ryaoi            ###   ########.fr       */
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
    char *test1 = ft_malloc(10);
    printf("test1 address:%llx\n", test1);
    for(int i = 0;i < 9;i++)
        test1[i] = 'A';
    test1[9] = '\0';
    // char *test2 = ft_malloc(20);
    show_alloc_mem();
    test1 = ft_realloc(test1, 30);
    // ft_free(test2);
    // ft_free(test2);
    show_alloc_mem();
    return (0);
}