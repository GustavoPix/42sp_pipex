/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:37:29 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/24 22:13:27 by glima-de         ###   ########.fr       */
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
    //close(data->fd[1][0]);
    //close(data->fd[2][1]);
    char * envVec[] = {NULL};
    if(execve(data->cmds[0].command, data->cmds[0].parans, envVec) == -1)
        perror("Grep error");
}

void pipe_middle(t_data *data, int i)
{
    int fdFile;
    fdFile = open(data->file_exit, O_WRONLY);
    dup2(data->fd[i][0], STDIN_FILENO);
    //dup2(data->fd[i + 1][1], STDOUT_FILENO);
    dup2(fdFile, STDOUT_FILENO);
    close(data->fd[i - 1][0]);
    close(data->fd[i - 1][1]);
    close(data->fd[i][1]);
    close(fdFile);
    //close(data->fd[2][0]);
    //close(data->fd[0][1]);
    //close(data->fd[0][0]);
    //close(data->fd[0][1]);
    //close(data->fd[1][0]);
    //close(data->fd[1][1]);
    //close(data->fd[2][0]);
    //close(data->fd[2][1]);
    char * envVec[] = {NULL};
    data->cmds[i].parans[0] = "";
    if(execve(data->cmds[i].command, data->cmds[i].parans, envVec) == -1)
        perror("WC error");
}

void pipe_end(t_data *data)
{
    int fdFile;
    char *aux;
    aux = ft_calloc(2, sizeof(char));
    dup2(data->fd[data->qpipes - 1][0], STDIN_FILENO);
    close(data->fd[0][0]);
    close(data->fd[1][1]);
    //close(data->fd[1][0]);
    //close(data->fd[2][1]);
    fdFile = open(data->file_exit, O_WRONLY);
    read(STDIN_FILENO,&aux,1);
    //write(fdFile,&aux,1);

}
