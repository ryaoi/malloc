# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/14 18:49:54 by ryaoi             #+#    #+#              #
#    Updated: 2018/05/19 14:05:18 by ryaoi            ###   ########.fr        #
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
				find_non_allocated_space.c

OBJ		= $(SRCS:.c=.o)

INCLUDE	= -I./inc/filler.h \
		  -I./libft/libft.h

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -lpthread

all: $(NAME)

%.o:%.c
	$(CC) -I./$(INCLUDE) -o $@ -c $<

$(LIBFT):
	make -C $(DIR_LIB)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) -shared -o $(NAME) ./libft/libft.a $(OBJ) $(INCLUDE) 
	@rm -f $(LINK)
	@ln -s  $(NAME) $(LINK)

clean:
	make clean -C $(DIR_LIB)
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(DIR_LIB)
	rm -rf $(NAME)

re: fclean all
