/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:37:29 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/25 20:00:17 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void pipe_start(t_data *data)
{
    int fdFile;
    fdFile = open(data->file_open, O_RDONLY);
    dup2(fdFile, STDIN_FILENO);
    close(fdFile);
    dup2(data->fd[1][1], STDOUT_FILENO);
    close(data->fd[0][1]);
    close(data->fd[data->qpipes - 1][0]);
    char * envVec[] = {NULL};
    if(execve(data->cmds[0].command, data->cmds[0].parans, envVec) == -1)
        perror("Grep error");
}

void pipe_middle(t_data *data, int i)
{
    dup2(data->fd[i][0], STDIN_FILENO);
    dup2(data->fd[i + 1][1], STDOUT_FILENO);
    close_fds(data, i);
    char * envVec[] = {NULL};
    data->cmds[i].parans[0] = "";
    if(execve(data->cmds[i].command, data->cmds[i].parans, envVec) == -1)
        perror("WC error");
}

void pipe_end(t_data *data)
{
    int fdFile;

    fdFile = open(data->file_exit, O_WRONLY);
    dup2(data->fd[data->qpipes - 1][0], STDIN_FILENO);
    dup2(fdFile, STDOUT_FILENO);
    close_fds(data, data->qpipes - 1);
    close(fdFile);
    char * envVec[] = {NULL};
    data->cmds[data->qpipes - 1].parans[0] = "";
    if(execve(data->cmds[data->qpipes - 1].command, data->cmds[data->qpipes - 1].parans, envVec) == -1)
        perror("WC error");
}

void close_fds(t_data *data, int max)
{
    int i;

    i = 0;
    while (i <= max)
    {
        close(data->fd[i][0]);
        close(data->fd[i][1]);
        i++;
    }
}
