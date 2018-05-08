/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:06:25 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/08 16:01:49 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>

void				*ft_memset(void *b, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				ft_ulltoa_hex(unsigned long long nbr);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
size_t				ft_strlen(const char *s);

#endif
