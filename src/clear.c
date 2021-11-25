/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 20:00:38 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/25 20:35:46 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void clear_data(t_data *data)
{
    int i;
    int j;

    i = 0;
    //free(&data->file_open);
    //free(data->file_exit);
    while(i < data->qpipes)
    {
        //free(data->cmds[i].command);
        j = 0;
        while (data->cmds[i].parans[j])
        {
            //free(data->cmds[i].parans[j]);
            //free(data->fd[j]);
            j++;
        }
        //free(data->cmds[i].parans);
        //free(data->fd);
        data->pid[i] = 0;
        i++;
    }
    free(data->pid);
}
