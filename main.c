/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:08:44 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/25 20:32:32 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

int test(t_data *data)
{
    int i;

    i = 0;
    data->fd = malloc(sizeof(int *) * data->qpipes);
    while (i < data->qpipes)
    {
        data->fd[i] = malloc(sizeof(int) * 2);
        if (pipe(data->fd[i]) < 0)
            return (0);
        i++;
    }
    i = 0;
    while (i < data->qpipes)
    {
        data->pid[i] = fork();
        if (data->pid[i] < 0)
            return (0);
        if (data->pid[i] == 0)
        {
            if (i == 0)
            {
                printf("pipe start\n");
                pipe_start(data);
            }
            else if (i < data->qpipes - 1)
            {
                printf("pipe middle\n");
                pipe_middle(data, i);
            }
            else
            {
                printf("pipe end\n");
                pipe_end(data);
            }
        }
        i++;
    }
    i = 0;
    close_fds(data, data->qpipes - 1);
    while (i < data->qpipes)
    {
       waitpid(data->pid[i], NULL, 0);
       i++;
    }
    clear_data(data);
    return (0);
}
void set_params(t_data *data, char *argv, int index)
{
    char    **aux;
    int     args;

    args = 0;
    aux = ft_split(argv, ' ');
    while (aux[args])
        args++;
    data->cmds[index].command = ft_strjoin("/usr/bin/",aux[0]);
    data->cmds[index].parans = malloc((args + 1) * sizeof(char *));
    args = 1;
    while (aux[args])
    {
        data->cmds[index].parans[args] = aux[args];
        args++;
    }
    data->cmds[index].parans[args] = NULL;
    data->cmds[index].parans[0] = "";
}

int main(int argc, char **argv)
{
    t_data data;
    int     i;

    i = 0;

    if (argc != 5)
    {
        printf("Pipex works using: pipex file_in cmd cmd file_out\n");
        return(0);
    }
    data.qpipes = argc - 3;
    data.cmds = malloc(data.qpipes * sizeof(t_commands));
    while (i < data.qpipes)
    {
        set_params(&data,argv[i + 2],i);
        i++;
    }
    data.file_open = argv[1];
    data.file_exit = argv[argc - 1];
    data.pid = (int *)malloc(data.qpipes * sizeof(int));
    test(&data);
    return (0);
}

