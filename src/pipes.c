/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:37:29 by glima-de          #+#    #+#             */
/*   Updated: 2022/01/15 10:21:50 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	create_pipes(t_data *data)
{
	int	i;

	i = 0;
	data->fd = malloc(sizeof(int *) * data->qpipes);
	while (i < data->qpipes)
	{
		data->fd[i] = malloc(sizeof(int) * 2);
		if (pipe(data->fd[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

void	pipe_choose(t_data *data, int index)
{
	if (index == 0)
		pipe_start(data);
	else if (index < data->qpipes - 1)
		pipe_middle(data, index);
	else
		pipe_end(data);
}

void	pipe_start(t_data *data)
{
	int		fdfile;
	int		prfile;
	char	*envvec[1];

	prfile = check_read_file(data->file_open);
	if (prfile < 0)
	{
		ft_putstr_fd(data->file_open, 1);
		if (prfile == -2)
			ft_putstr_fd(": No such file or directory\n", 1);
		else
			ft_putstr_fd(": Permission denied\n", 1);
	}
	else
	{
		envvec[0] = NULL;
		fdfile = open(data->file_open, O_RDONLY);
		dup2(fdfile, STDIN_FILENO);
		close(fdfile);
		dup2(data->fd[1][1], STDOUT_FILENO);
		close_fd(data, data->qpipes - 1, 0);
		if (execve(data->cmds[0].command, data->cmds[0].parans, envvec) == -1)
			perror("Pipe start error");
	}
}

void	pipe_middle(t_data *data, int i)
{
	char	*envvec[1];

	envvec[0] = NULL;
	dup2(data->fd[i][0], STDIN_FILENO);
	dup2(data->fd[i + 1][1], STDOUT_FILENO);
	close_fd(data, i - 1, i);
	data->cmds[i].parans[0] = "";
	if (execve(data->cmds[i].command, data->cmds[i].parans, envvec) == -1)
		perror("Pipe middle error");
}

void	pipe_end(t_data *data)
{
	int		fdfile;
	int		pipe;
	char	*envvec[1];

	if (check_write_file(data->file_exit) == 0)
	{
		ft_putstr_fd(data->file_exit, 1);
		ft_putstr_fd(": Permission denied\n", 1);
	}
	else
	{
		pipe = data->qpipes - 1;
		envvec[0] = NULL;
		fdfile = open(data->file_exit, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		dup2(data->fd[data->qpipes - 1][0], STDIN_FILENO);
		dup2(fdfile, STDOUT_FILENO);
		close(data->fd[0][0]);
		close(data->fd[1][1]);
		close_fd(data, data->qpipes - 2, data->qpipes - 1);
		close(fdfile);
		data->cmds[data->qpipes - 1].parans[0] = "";
		if (execve(data->cmds[pipe].command,
				data->cmds[pipe].parans, envvec) == -1)
			perror("Pipe end error");
	}
}
