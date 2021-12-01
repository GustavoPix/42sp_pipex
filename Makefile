# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/07 13:01:21 by glima-de          #+#    #+#              #
#    Updated: 2021/12/01 19:44:34 by glima-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_MANDATORY = ./main.c \
				 ./src/pipes.c \
				 ./src/clear.c \
				 ./src/checkers.c

GNL = 			 ./gnl/get_next_line.c

OBJS 		= ${SRCS:.c=.o}
OBJS_M		= ${SRCS_MANDATORY:.c=.o}

OBJS_GNL	= ${GNL:.c=.o}

UNAME		:= $(shell uname)

PATH_LIBFT	= libft
CC 			= clang
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
NAME		= pipex

all: 		${NAME}

.c.o:
			${CC} -g ${CFLAGS} -I libft -c $< -o ${<:.c=.o}

$(NAME): 	${OBJS_GNL} $(OBJS) ${OBJS_M}
			echo x > ./test/outfile
			make -C $(PATH_LIBFT)
			${CC} -g $(CFLAGS) -o $(NAME) $(OBJS) ${OBJS_M} ${OBJS_GNL} -L $(PATH_LIBFT) -lft

clean:
			make -C $(PATH_LIBFT) clean
			${RM} ${OBJS} ${OBJS_M} ${OBJS_GNL} ${OBJS_SLG} ${OBJS_GNL}

fclean: 	clean
			make -C $(PATH_LIBFT) fclean
			${RM} ${NAME}

re: 		fclean all

test:		all
			./so_long ./maps/pdf2.ber

val:		all
			valgrind --leak-check=full ./so_long ./maps/test_leak.ber

.PHONY:		all clean fclean re test val
