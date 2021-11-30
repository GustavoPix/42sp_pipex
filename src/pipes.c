/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:37:29 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/30 19:40:45 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	pipe_start(t_data *data)
{
	int		fdfile;
	char	*envvec[1];

	envvec[0] = NULL;
	fdfile = open(data->file_open, O_RDONLY);
	dup2(fdfile, STDIN_FILENO);
	close(fdfile);
	dup2(data->fd[1][1], STDOUT_FILENO);
	close(data->fd[0][1]);
	close(data->fd[data->qpipes - 1][0]);
	if (execve(data->cmds[0].command, data->cmds[0].parans, envvec) == -1)
		perror("Grep error");
}

void	pipe_middle(t_data *data, int i)
{
	char	*envvec[1];

	envvec[0] = NULL;
	dup2(data->fd[i][0], STDIN_FILENO);
	dup2(data->fd[i + 1][1], STDOUT_FILENO);
	close_fds(data, i);
	data->cmds[i].parans[0] = "";
	if (execve(data->cmds[i].command, data->cmds[i].parans, envvec) == -1)
		perror("WC error");
}

void	pipe_end(t_data *data)
{
	int		fdfile;
	int		pipe;
	char	*envvec[1];

	pipe = data->qpipes - 1;
	envvec[0] = NULL;
	fdfile = open(data->file_exit, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	dup2(data->fd[data->qpipes - 1][0], STDIN_FILENO);
	dup2(fdfile, STDOUT_FILENO);
	close_fds(data, data->qpipes - 1);
	close(fdfile);
	data->cmds[data->qpipes - 1].parans[0] = "";
	if (execve(data->cmds[pipe].command, data->cmds[pipe].parans, envvec) == -1)
		perror("WC error");
}

void	close_fds(t_data *data, int max)
{
	int	i;

	i = 0;
	while (i <= max)
	{
		close(data->fd[i][0]);
		close(data->fd[i][1]);
		i++;
	}
}
