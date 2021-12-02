# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/07 13:01:21 by glima-de          #+#    #+#              #
#    Updated: 2021/12/02 19:04:51 by glima-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_MANDATORY = ./main.c \
				 ./src/pipes.c \
				 ./src/clear.c \
				 ./src/checkers.c

SRCS_LIBFT	=	 ./libft/ft_strjoin.c \
				 ./libft/ft_strdup.c \
				 ./libft/ft_putstr_fd.c \
				 ./libft/ft_split.c \
				 ./libft/ft_strncmp.c \
				 ./libft/ft_strlen.c

OBJS_M		= ${SRCS_MANDATORY:.c=.o}
OBJS_LIBFT	= ${SRCS_LIBFT:.c=.o}

UNAME		:= $(shell uname)

PATH_LIBFT	= libft
CC 			= clang
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
NAME		= pipex

all: 		${NAME}

.c.o:
			${CC} -g ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): 	${OBJS_M} ${OBJS_LIBFT}
			echo x > ./test/outfile
			${CC} -g $(CFLAGS) -o $(NAME) ${OBJS_M} ${OBJS_LIBFT}

clean:
			${RM} ${OBJS_M} ${OBJS_LIBFT}

fclean: 	clean
			${RM} ${NAME}

re: 		fclean all

test:		all
			./so_long ./maps/pdf2.ber

val:		all
			valgrind --leak-check=full ./so_long ./maps/test_leak.ber

.PHONY:		all clean fclean re test val
