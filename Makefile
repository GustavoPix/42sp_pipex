# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/07 13:01:21 by glima-de          #+#    #+#              #
#    Updated: 2021/11/07 13:14:11 by glima-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_MANDATORY = ./main.c \

OBJS 		= ${SRCS:.c=.o}
OBJS_M		= ${SRCS_MANDATORY:.c=.o}



UNAME		:= $(shell uname)

PATH_LIBFT	= libft
CC 			= clang
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
NAME		= pipex

all: 		${NAME}

.c.o:
			${CC} -g ${CFLAGS} -Imlx -Ibass -c $< -o ${<:.c=.o}

$(NAME): 	gclone $(OBJS) ${OBJS_M}
			make -C $(PATH_LIBFT)
			${CC} -g $(CFLAGS) -o $(NAME) $(OBJS) ${OBJS_M}


clean:
			make -C $(PATH_LIBFT) clean
			${RM} ${OBJS} ${OBJS_M} ${OBJS_GNL} ${OBJS_SLG} ${OBJS_LIBFT}

fclean: 	clean
			make -C $(PATH_LIBFT) clean
			rm -rf mlx
			${RM} ${NAME}

re: 		fclean all

test:		all
			./so_long ./maps/pdf2.ber

val:		all
			valgrind --leak-check=full ./so_long ./maps/test_leak.ber

.PHONY:		all gclone clean fclean re test val
