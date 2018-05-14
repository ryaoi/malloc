/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:14:00 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/14 18:57:27 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <pthread.h>
# include "../libft/libft.h"

# define TINY 128
# define SMALL 4096
# define FLAG_PROT PROT_READ | PROT_WRITE
# define FLAG_MAP  MAP_ANON | MAP_PRIVATE
# define OVERHEAD (sizeof(t_blockheader) + sizeof(t_blockfooter))
# define OVER		0x12345678

typedef struct	s_blockheader
{
    size_t		size;
	char		allocated;
}				t_blockheader;

typedef struct	s_blockfooter
{
	size_t		size;
	int			filler;
}				t_blockfooter;

typedef struct 	map_s
{
	void		*tiny;
	void		*small;
	void		*large;
	void		*extend_tiny;
	void		*extend_small;
	void		*extend_large;
	size_t		tiny_size;
	size_t		small_size;
	size_t		page_size;
	size_t		tiny_count;
	size_t		small_count;
	size_t		large_count;
}				t_map;

void		ft_free(void *ptr);
void		*ft_malloc(size_t size);
void        *ft_realloc(void *ptr, size_t size);
void		show_alloc_mem(void);
void 		show_alloc_mem_ex(void);
int			mm_init(void);
void		*next_block(void *ptr);
void		*prev_block(void *ptr);
void		create_block(void *ptr, size_t size);
void		*extend(size_t new_size, void *block_ptr, char size_flag);
void		*find_non_allocated_space(size_t size);

#endif