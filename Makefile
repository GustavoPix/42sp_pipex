# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/07 13:01:21 by glima-de          #+#    #+#              #
#    Updated: 2022/01/12 20:10:59 by glima-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=./main.c \
				 ./src/pipes.c \
				 ./src/treatments.c \
				 ./src/clear.c

SRCS_MANDATORY	=./src/checkers.c

SRCS_BONUS		=./src/checkers_bonus.c

SRCS_LIBFT		=./libft/ft_strjoin.c \
				 ./libft/ft_strdup.c \
				 ./libft/ft_putstr_fd.c \
				 ./libft/ft_split.c \
				 ./libft/ft_strncmp.c \
				 ./libft/ft_strlen.c

OBJS		= ${SRCS:.c=.o}
OBJS_M		= ${SRCS_MANDATORY:.c=.o}
OBJS_B		= ${SRCS_BONUS:.c=.o}
OBJS_LIBFT	= ${SRCS_LIBFT:.c=.o}

PATH_LIBFT	= libft
CC 			= clang
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
NAME		= pipex

all: 		${NAME}

.c.o:
			${CC} -g ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): 	${OBJS} ${OBJS_M} ${OBJS_LIBFT}
			${CC} -g $(CFLAGS) -o $(NAME) ${OBJS} ${OBJS_M} ${OBJS_LIBFT}

clean:
			${RM} ${OBJS} ${OBJS_M} ${OBJS_B} ${OBJS_LIBFT}

fclean: 	clean
			${RM} ${NAME}

re: 		fclean all

bonus:		${OBJS} ${OBJS_B} ${OBJS_LIBFT}
			${CC} -g $(CFLAGS) -o $(NAME) ${OBJS} ${OBJS_B} ${OBJS_LIBFT}

.PHONY:		all clean fclean re bonus
