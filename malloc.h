/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:14:00 by ryaoi             #+#    #+#             */
/*   Updated: 2018/05/11 18:05:38 by ryaoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include "./libft/libft.h"

# define TINY 128
# define SMALL 4096
# define FLAG_PROT PROT_READ | PROT_WRITE
# define FLAG_MAP  MAP_ANON | MAP_PRIVATE
# define OVERHEAD (sizeof(t_blockheader) + sizeof(t_blockfooter))
# define HDRP(block_ptr) ((char *)block_ptr - OVERHEAD)
# define GET_HSIZE(ptr) ((t_blockheader *)(ptr))->size
# define GET_HALLOC(ptr) ((t_blockheader *)(ptr))->allocated
# define GET_FSIZE(ptr) ((t_blockfooter *)(ptr))->size
# define NEXT_BLKP(block_ptr) ((char *)block_ptr + GET_SIZE(HDRP(block_ptr))) 
# define PREV_BLKP(block_ptr) ((char *)(block_ptr) - \
					GET_SIZE((char *)(block_ptr) - OVERHEAD))
# define FTRP(block_ptr) ((char *)(block_ptr) + GET_SIZE(HDRP(block_ptr)) - OVERHEAD)


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
int			mm_init(void);
void		*next_block(void *ptr);
void		*prev_block(void *ptr);
void		create_block(void *ptr, size_t size);

#endif