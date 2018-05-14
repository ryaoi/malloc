# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/14 18:49:54 by ryaoi             #+#    #+#              #
#    Updated: 2018/05/14 19:03:47 by ryaoi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

SRCS		= 	free.c \
				malloc.c \
				realloc.c \
				block.c \
				show_alloc_mem.c 

PATH_OBJ	= obj
PATH_SRC	= src
PATH_INC	= inc

PATH_LIB	= libft

LIBFT	= $(PATH_LIB)/libft.a

NAME		= libft_malloc_$(HOSTTYPE).so
CFLAGS		= 
OTHERFLAGS	= -shared -fPIC
OBJECTS		= $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRCS))


	
all: $(NAME)

$(LIBFT):
	make -C $(PATH_LIB)
	
$(NAME): $(LIBFT) $(OBJECTS)
	@gcc $(OTHERLFLAGS) -o $@ $(OBJECTS) ./libft/libft.a
	@rm -f libft_malloc.so
	@ln -s $(NAME) libft_malloc.so

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/,%.c)
	@mkdir -p $(PATH_OBJ)
	$(CC) -c -o $@ $(CFLAGS) $^  -I $(PATH_INC)/ $(PATH_LIB)/ ./libft/libft.a

clean:
	@rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)
	rm -f libft_malloc.so

re: fclean $(NAME)
