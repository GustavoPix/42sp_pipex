/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:44:14 by glima-de          #+#    #+#             */
/*   Updated: 2021/12/01 20:59:10 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "./libft/libft.h"

/*=============*/
/*  structs    */
/*=============*/
typedef struct s_commands
{
	char	*command;
	char	**parans;
}	t_commands;

typedef struct s_data
{
	char		*file_open;
	char		*file_exit;
	char		**path;
	int			**fd;
	int			qpipes;
	int			*pid;
	t_commands	*cmds;
}	t_data;

/*=============*/
/*  pipes      */
/*=============*/
void	pipe_start(t_data *data);
void	pipe_middle(t_data *data, int i);
void	pipe_end(t_data *data);
void	close_fds(t_data *data, int max);

/*=============*/
/*  clear      */
/*=============*/
void	clear_data(t_data *data);
void	clear_cmds(t_data *data);
void	clear_path(t_data *data);

/*=============*/
/*  checkers   */
/*=============*/
int		check_parans(int argc, char **argv);
int		check_valid_cmds(t_data *data);

#endif
