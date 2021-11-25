/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima-de <glima-de@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:08:44 by glima-de          #+#    #+#             */
/*   Updated: 2021/11/24 21:47:39 by glima-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

int test(t_data *data)
{
    int i;


    i = 0;
    data->fd = malloc(sizeof(int) * 2);
    while (i < 2)
    {
        data->fd[i] = malloc(sizeof(int) * 2);
        if (pipe(data->fd[i]) < 0)
            return (0);
        i++;
    }

    int pid1 = fork();
    if (pid1 < 0)
        return (0);

    if (pid1 == 0)
    {
        pipe_start(data);
        //printf("Pid1\n");
        //int fdFile;
//
        //fdFile = open("./test/start_file", O_RDONLY);
        //dup2(fdFile, STDIN_FILENO);
        //close(fdFile);
//
        //// Child process 1 (ping)
        //dup2(fd[1][1], STDOUT_FILENO);
//
        //close(fd[0][1]);
        //close(fd[2][0]);
        //close(fd[1][0]);
        //close(fd[2][1]);
        ////execlp("ping", "ping", "-c", "5", "google.com", NULL);
//
        //execlp("grep", "grep", "abc", NULL);
    }

    int pid2 = fork();
    if (pid2 < 0)
        return (0);
    if (pid2 == 0)
    {
            //Child process 2 (grep)
            pipe_middle(data,1);
            //printf("Pid2\n");
//
            ////fdFile = open("./test/outfile", O_WRONLY);
//
            //dup2(data->fd[1][0], STDIN_FILENO);
            //dup2(data->fd[2][1], STDOUT_FILENO);
            //close(data->fd[0][0]);
            //close(data->fd[1][1]);
            //close(data->fd[2][0]);
            //close(data->fd[0][1]);
//
            ////read(STDIN_FILENO,&aux,10);
            ////execlp("grep", "grep", "rtt", NULL);
            //execlp("wc", "wc", "-w", NULL);

    }





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

    close(data->fd[0][0]);
    close(data->fd[0][1]);
    close(data->fd[1][0]);
    close(data->fd[1][1]);
    //close(data->fd[2][0]);
    //close(data->fd[2][1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
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

    if (argc != 5)
    {
        printf("Pipex works using: pipex file_in cmd cmd file_out\n");
        return(0);
    }
    data.cmds = malloc(sizeof(t_commands) * 2);
    set_params(&data,argv[2],0);
    set_params(&data,argv[3],1);
    data.file_open = argv[1];
    data.file_exit = argv[4];
    data.qpipes = 2;
    test(&data);
    return (0);
}

