/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 20:00:38 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/30 18:49:27 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	clear_data(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->qpipes)
	{
		j = 0;
		while (data->cmds[i].parans[j])
		{
			if (j > 0)
				free(data->cmds[i].parans[1]);
			j++;
		}
		free(data->cmds[i].parans);
		free(data->cmds[i].command);
		free(data->fd[i]);
		data->pid[i] = 0;
		i++;
	}
	free(data->cmds);
	free(data->fd);
	free(data->pid);
}
