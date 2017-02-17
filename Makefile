# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/14 17:16:56 by mhaziza           #+#    #+#              #
#    Updated: 2017/02/16 17:13:28 by mhaziza          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	lem-in
CC		=   gcc
CFLAGS	= 	-Wall -Wextra -Werror -I.
RM		=   rm -f
LIBFT	=	 -L./libft -lft
SRCS	=	lem_in.c \
			anthill.c \
			adjacency.c \
			bfs.c \
			debug.c \
			anthill_utils.c \
			flow.c \

OBJS	=   $(SRCS:.c=.o)

LIBFT_PATH	= ./libft

all:	$(NAME)

$(NAME):$(OBJS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAG) $(SRCS) $(LIBFT) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_PATH) clean

fclean:	clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean

re:		fclean all

.PHONY:		all clean fclean re
