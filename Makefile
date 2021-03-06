# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/14 18:49:54 by ryaoi             #+#    #+#              #
#    Updated: 2018/05/26 16:04:52 by ryaoi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		= 	libft_malloc_$(HOSTTYPE).so

LINK		=	libft_malloc.so

DIR_LIB	= libft

LIBFT	= $(DIR_LIB)/libft.a

SRCS		= 	free.c \
				malloc.c \
				realloc.c \
				block.c \
				show_alloc_mem.c \
				safe_pointer.c \
				find_non_allocated_space.c \
				defragmentation.c \
				calloc.c \
				ft_print_address.c

OBJ		= $(SRCS:.c=.o)

INCLUDE	= -I./inc/malloc.h \
		  -I./libft/libft.h

HEADER  = ./inc/malloc.h \
		  ./libft/libft.h

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -lpthread

all: $(NAME)

%.o:%.c $(HEADER)
	$(CC) -I./$(INCLUDE) -o $@ -c $< 

$(LIBFT):
	make -C $(DIR_LIB)

$(NAME): $(LIBFT) $(OBJ) $(HEADER) 
	$(CC) -shared -o $(NAME) ./libft/libft.a $(OBJ) $(INCLUDE) 
	@ln -sf  $(NAME) $(LINK)

clean:
	make clean -C $(DIR_LIB)
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(DIR_LIB)
	rm -rf $(NAME)

re: fclean all
