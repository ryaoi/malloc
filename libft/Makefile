# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 14:11:33 by ryaoi             #+#    #+#              #
#    Updated: 2018/05/08 15:38:11 by ryaoi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRC		= ./ft_bzero.c \
			./ft_memset.c \
			./ft_ulltoa_hex.c \
			./ft_putchar.c \
			./ft_putstr.c \
			./ft_putnbr.c \
			./ft_putchar_fd.c \
			./ft_putstr_fd.c \
			./ft_putnbr.c \
			./ft_strlen.c

OBJ		= $(SRC:.c=.o)

INCLUDE = libft.h

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

%.o:%.c 
	$(CC) $(CFLAGS) -I./$(INCLUDE) -o $@ -c $< 

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
