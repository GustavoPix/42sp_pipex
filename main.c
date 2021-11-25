/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:08:44 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/25 18:45:22 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

int test(t_data *data)
{
    int i;


    i = 0;
    data->fd = malloc(sizeof(int) * data->qpipes);
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
    //data->pid[0] = fork();
    //if (data->pid[0] < 0)
    //    return (0);
    //if (data->pid[0] == 0)
    //{
    //    pipe_start(data);
    //}
//
    //data->pid[1] = fork();
    //if (data->pid[1] < 0)
    //    return (0);
    //if (data->pid[1] == 0)
    //{
    //        pipe_middle(data,1);
    //}





    //int pid3 = fork();
    //if (pid3 < 0)
    //    return (0);
    //if (pid3 == 0)
    //{
    //        //Child process 2 (grep)
    //        //printf("Pid3\n");
    //        pipe_end(data);
    //        //int fdFile;
    //        //char *aux;
    //        //aux = ft_calloc(2, sizeof(char));
////
    //        //dup2(data->fd[2][0], STDIN_FILENO);
////
    //        //close(data->fd[1][0]);
    //        //close(data->fd[2][1]);
    //        //close(data->fd[0][0]);
    //        //close(data->fd[1][1]);
////
    //        //fdFile = open("./test/outfile", O_WRONLY);
    //        //read(STDIN_FILENO,&aux,2);
    //        //write(fdFile,&aux,2);
    //}

    while (i < data->qpipes)
    {
        close(data->fd[i][0]);
        close(data->fd[i][1]);
        i++;
    }
    i = 0;
    while (i < data->qpipes)
    {
       waitpid(data->pid[i], NULL, 0);
       i++;
    }

    //close(data->fd[0][1]);
    //close(data->fd[1][0]);
    //close(data->fd[1][1]);
    //close(data->fd[2][0]);
    //close(data->fd[2][1]);
    //waitpid(data->pid[0], NULL, 0);
    //waitpid(data->pid[1], NULL, 0);
    //waitpid(pid3, NULL, 0);
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
        //return(0);
    }
    data.qpipes = argc - 3;
    data.cmds = malloc(data.qpipes * sizeof(t_commands));
    while (i < data.qpipes)
    {
        set_params(&data,argv[i + 2],i);
        i++;
    }
    //set_params(&data,argv[3],1);
    data.file_open = argv[1];
    data.file_exit = argv[argc - 1];
    data.pid = malloc(data.qpipes * sizeof(int));
    test(&data);
    return (0);
}

