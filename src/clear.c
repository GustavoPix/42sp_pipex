/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 20:00:38 by glima-de          #+#    #+#             */
/*   Updated: 2022/01/12 18:53:27 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	clear_cmds(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->qpipes)
	{
		j = 0;
		while (data->cmds[i].parans[j])
		{
			if (j > 0 && data->cmds[i].parans[j])
				free(data->cmds[i].parans[j]);
			j++;
		}
		if (data->cmds[i].parans)
			free(data->cmds[i].parans);
		if (data->cmds[i].command)
			free(data->cmds[i].command);
		i++;
	}
	free(data->cmds);
}

void	clear_path(t_data *data)
{
	int	i;

	i = 0;
	while (data->path[i])
	{
		free(data->path[i]);
		i++;
	}
	free(data->path);
}

void	clear_data(t_data *data)
{
	int	i;

	i = 0;
	clear_cmds(data);
	while (i < data->qpipes)
	{
		free(data->fd[i]);
		data->pid[i] = 0;
		i++;
	}
	clear_path(data);
	free(data->fd);
	free(data->pid);
}

void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	close_fds(data, data->qpipes - 1);
	while (i < data->qpipes)
	{
		waitpid(data->pid[i], &data->status, 0);
		i++;
	}
}
