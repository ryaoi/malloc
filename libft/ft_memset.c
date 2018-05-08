/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:39:14 by ryaoi             #+#    #+#             */
/*   Updated: 2016/11/03 14:39:16 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char *new;

	new = b;
	while (n > 0 && new != '\0')
	{
		*new = (unsigned char)c;
		new++;
		n--;
	}
	return (b);
}
